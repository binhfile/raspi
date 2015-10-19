#define USE_BINDINGS
#define I_AM_LIGHT
#define I_AM_SWITCH

#include <lib_debug.h>
#include <lib_time.h>
#include <mrf24j40/mrf24j40.h>

#include <stdio.h>
#include <string.h>
#include <signal.h>

#include <zZDO.h>
#include <Compiler.h>
#include <zAPL.h>
#ifdef I_SUPPORT_SECURITY
#include <zSecurity.h>
#endif

#define BIND_STATE_BOUND            0
#define BIND_STATE_TOGGLE           1
#define BIND_STATE_UNBOUND          1
#define BIND_WAIT_DURATION          (5*ONE_SECOND)

#define LIGHT_OFF                   0x00
#define LIGHT_ON                    0xFF
#define LIGHT_TOGGLE                0xF0

ZIGBEE_PRIMITIVE    currentPrimitive;
SHORT_ADDR          destinationAddress;
#ifdef I_SUPPORT_SECURITY
	extern KEY_VAL	KeyVal;
	#ifdef USE_EXTERNAL_NVM
		extern WORD trustCenterLongAddr;
		extern NETWORK_KEY_INFO plainSecurityKey[2];
	#else
		extern ROM LONG_ADDR trustCenterLongAddr;
	#endif
#endif


static union
{
    struct
    {
        BYTE    bBroadcastSwitchToggled    : 1;
        BYTE    bLightSwitchToggled        : 1;
        BYTE    bTryingToBind              : 1;
        BYTE    bIsBound                   : 1;
        BYTE    bDestinationAddressKnown   : 1;
    } bits;
    BYTE Val;
} myStatusFlags;
#define STATUS_FLAGS_INIT       0x00
#define TOGGLE_BOUND_FLAG       0x08
#define bBindSwitchToggled      bBroadcastSwitchToggled

volatile int 	s_optMode = 0;	// none
void* 			s_semTx = 0;
unsigned char	s_txBuffer[512];
int  			s_txLength = 0;
unsigned short  s_txDestId = 0;

void*			s_semRx;
unsigned char  	s_rxBuffer[512];
unsigned char   s_rxLength = 0;

MRF24J40		*g_rfDevice = 0;
volatile int g_terminate = 0;
void     ISR_INT(int iSig)
{
    printf("\nQuit signal\n");
    g_terminate = 1;
    signal(SIGINT, SIG_DFL);    /*^C*/
}
int mac_callback(int type, void* param, void* obj);
void tx_thread(void* obj, int* terminate);
FILE* g_eepromFs = 0;
void eepromMemoryInit(){
	if(g_eepromFs == 0){
		g_eepromFs = fopen("coordinator.dat", "w+b");
		char buffer[EXTERNAL_NVM_BYTES];
		memset(buffer, 0, EXTERNAL_NVM_BYTES);
		if(g_eepromFs){
			if(fread(buffer, 1, 1, g_eepromFs) <= 0){
				fwrite(buffer, 1, EXTERNAL_NVM_BYTES, g_eepromFs);
			}
		}else{
			LREP("open '%d' failed.\r\n", "data");
		}
	}
}
void eepromMemoryDestroy(){
	if(g_eepromFs){
		fclose(g_eepromFs);
		g_eepromFs = 0;
	}
}
int eepromMemoryRead(void* data, int address, int count){
	if(g_eepromFs){
		fseek(g_eepromFs, address, SEEK_SET);
		return fread(data, 1, count, g_eepromFs);
	}
	return 0;
}
int eepromMemoryWrite(void* data, int address, int count){
	if(g_eepromFs){
		fseek(g_eepromFs, address, SEEK_SET);
		fwrite(data, 1, count, g_eepromFs);
		fflush(g_eepromFs);
		return 0;
	}
	return 0;
}
int main(int argc, char** argv){
	void		*txThread = 0;
	const char 	*portName 	= argv[1];
	int 		resetPin 	= atoi(argv[2]);
	int 		intrPin 	= atoi(argv[3]);
	unsigned short id  		= atoi(argv[4]);
	unsigned short channel  = atoi(argv[5]);
	char 		szInput[32];
	int j, i;
	unsigned short destid;
	unsigned char cnt = 0;
	int ret;
	int failedCnt = 0;
	int passedCnt = 0;
	int totalBytes = 0;
	unsigned int timeNow, timeEnd;
	int retries = 0;
	int passed;
	unsigned int timeDiff;
	float speed;
	unsigned char *tx, *rx;

	signal(SIGINT, ISR_INT);

	if(argc < 6){
		LREP("usage: %s /dev/spidevX.Y resetPin intrPin id channel\n", argv[0]);
		return 0;
	}

	LREP("cmd='%s'\nreset=%d\nintr=%d id=0x%04X channel=%d\n", portName, resetPin, intrPin, id, channel);

	s_semTx = lib_semAlloc(0);
	s_semRx = lib_semAlloc(0);
	txThread = lib_threadAlloc(tx_thread);
	eepromMemoryInit();

	g_rfDevice = mrf24j40_allocDevice(
			portName,
			resetPin,
			intrPin);
	if(mrf24j40_openDevice(g_rfDevice) != 0){
		LREP("open device failed.\n");
		mrf24j40_freeDevice(g_rfDevice);
		return 0;
	}
	LREP("open done\n");
//	mrf24j40_setCallback(g_rfDevice, mac_callback, g_rfDevice);
//	mrf24j40_setPan(g_rfDevice, 0xcafe);
//	mrf24j40_setAddress16(g_rfDevice, 0xffff);
//	mrf24j40_setAddress32(g_rfDevice, id);
//	mrf24j40_setChannel(g_rfDevice, channel);
//	mrf24j40_setTurboMode(g_rfDevice, 1);
//	mrf24j40_initDevice(g_rfDevice);

    currentPrimitive = NO_PRIMITIVE;

    // If you are going to send data to a terminal, initialize the UART.

    LREP( (ROM char *)"\r\n\r\n\r\n*************************************\r\n" );
    LREP( (ROM char *)"Microchip ZigBee(TM) Stack - v1.0-3.8.1\r\n\r\n" );
    LREP( (ROM char *)"ZigBee Coordinator\r\n\r\n" );
    #if (RF_CHIP == RF_MRF24J40)
        LREP( (ROM char *)"Transceiver-MRF24J40\r\n\r\n" );
    #elif (RF_CHIP==UZ2400)
        LREP( (ROM char *)"Transceiver-UZ2400\r\n\r\n" );
    #elif (RF_CHIP==CC2420)
        LREP( (ROM char *)"Transceiver-CC2420\r\n\r\n" );
    #else
        LREP( (ROM char *)"Transceiver-Unknown\r\n\r\n" );
    #endif
	// Initialize the ZigBee Stack.
	ZigBeeInit();
//    if (LIGHT_SWITCH == 0)
//    {
//        NWKClearNeighborTable();
//        LREP( (ROM char *)"Neighbor table \r\n" );
//        #if defined (USE_EXTERNAL_NVM)
////        ClearNVM( 0, 0x500 );
////        LREP( (ROM char *)"Cleared NVM\r\n\r\n" );
//        #endif
//    }
    // *************************************************************************
    // Perform any other initialization here
    // *************************************************************************

    myStatusFlags.Val = STATUS_FLAGS_INIT;
    destinationAddress.Val = 0x796F;    // Default to first RFD

//    BIND_INDICATION = !myStatusFlags.bits.bIsBound;
//    LATAbits.LATA4 = 0;
    // Enable interrupts to get everything going.
//    RFIE = 1;
//    #if !defined(__C30__)
//        RCONbits.IPEN = 1;
//        INTCONbits.GIEH = 1;
//    #endif
	lib_threadStart(txThread, g_rfDevice);

    while (!g_terminate)
    {
    	lib_sleepMs(10);
        ZigBeeTasks( &currentPrimitive );

        switch (currentPrimitive)
        {
            case NLME_NETWORK_FORMATION_confirm:
                if (!params.NLME_NETWORK_FORMATION_confirm.Status)
                {
                    LREP( (ROM char *)"PAN " );
                    LREP("%02X",  macPIB.macPANId.byte.MSB );
                    LREP("%02X",  macPIB.macPANId.byte.LSB );
                    LREP( (ROM char *)" started successfully.\r\n" );
                    params.NLME_PERMIT_JOINING_request.PermitDuration = 0xFF;   // No Timeout
                    currentPrimitive = NLME_PERMIT_JOINING_request;
                }
                else
                {
                    LREP("%02X",  params.NLME_NETWORK_FORMATION_confirm.Status );
                    LREP( (ROM char *)" Error forming network.  Trying again...\r\n" );
                    currentPrimitive = NO_PRIMITIVE;
                }
                break;

            case NLME_PERMIT_JOINING_confirm:
                if (!params.NLME_PERMIT_JOINING_confirm.Status)
                {
                    LREP( (ROM char *)"Joining permitted.\r\n" );
                    currentPrimitive = NO_PRIMITIVE;
                }
                else
                {
                    LREP("%02X",  params.NLME_PERMIT_JOINING_confirm.Status );
                    LREP( (ROM char *)" Join permission unsuccessful. We cannot allow joins.\r\n" );
                    currentPrimitive = NO_PRIMITIVE;
                }
                break;

            case NLME_JOIN_indication:
                LREP( (ROM char *)"Node " );
                LREP("%02X",  params.NLME_JOIN_indication.ShortAddress.byte.MSB );
                LREP("%02X",  params.NLME_JOIN_indication.ShortAddress.byte.LSB );
                LREP( (ROM char *)" just joined.\r\n" );

                #ifdef I_SUPPORT_SECURITY

                    #ifdef I_AM_TRUST_CENTER
                  		{
                  		  	BOOL AllowJoin = TRUE;
                			// decide if you allow this device to join
                  		  	if( !AllowJoin )
                  		  	{
                  		  		// no need to set deviceAddress, since it is overlap with NLME_JOIN_indication
                		  		//params.NLME_LEAVE_request.DeviceAddress = params.NLME_JOIN_indication.ExtendedAddress;
                		  		params.NLME_LEAVE_request.RemoveChildren = TRUE;
                  		  		currentPrimitive = NLME_LEAVE_request;
                				break;
                  		  	}
      						#ifdef I_SUPPORT_SECURITY_SPEC
      						    if( params.NLME_JOIN_indication.secureJoin )
      						    {
      							    BYTE i;
      			    //				LREP((ROM char *)"secure join\r\n");
      				    			for(i = 0; i < 16; i++)
      					    		{
      						    		KeyVal.v[i] = 0;
      							    }
      							    params.APSME_TRANSPORT_KEY_request.Key = &KeyVal;
      							    params.APSME_TRANSPORT_KEY_request.TransportKeyData.NetworkKey.KeySeqNumber = 0;

      						    }
      						    else
      						    {
      							    BYTE i;
      							    GetNwkActiveKeyNumber(&i);
      							    #ifdef USE_EXTERNAL_NVM
      								    currentNetworkKeyInfo = plainSecurityKey[i-1];
      							    #else
      								    GetNwkKeyInfo(&currentNetworkKeyInfo, (ROM void *)&(networkKeyInfo[i-1]));
      							    #endif
      							    params.APSME_TRANSPORT_KEY_request.Key = &(currentNetworkKeyInfo.NetKey);
      							    params.APSME_TRANSPORT_KEY_request.TransportKeyData.NetworkKey.KeySeqNumber = currentNetworkKeyInfo.SeqNumber.v[0];

      						    }
      						#else
      							#ifdef PRECONFIGURE_KEY
      							    {
      								    BYTE i;
      				    				for(i = 0; i < 16; i++)
      					    			{
      						    			KeyVal.v[i] = 0;
      							    	}
      								    params.APSME_TRANSPORT_KEY_request.Key = &KeyVal;
      								    params.APSME_TRANSPORT_KEY_request.TransportKeyData.NetworkKey.KeySeqNumber = 0;
      								    params.APSME_TRANSPORT_KEY_request._UseSecurity = TRUE;
      							    }
      							#else
      							    {
      								    BYTE i;
      								    GetNwkActiveKeyNumber(&i);
      								    #ifdef USE_EXTERNAL_NVM
      									    currentNetworkKeyInfo = plainSecurityKey[i-1];
      								    #else
      									    GetNwkKeyInfo(&currentNetworkKeyInfo, (ROM void *)&(networkKeyInfo[i-1]));
      								    #endif
      								    params.APSME_TRANSPORT_KEY_request.Key = &(currentNetworkKeyInfo.NetKey);
      								    params.APSME_TRANSPORT_KEY_request.TransportKeyData.NetworkKey.KeySeqNumber = currentNetworkKeyInfo.SeqNumber.v[0];
      								    params.APSME_TRANSPORT_KEY_request._UseSecurity = FALSE;
      							    }
      							#endif

      						#endif
                			params.APSME_TRANSPORT_KEY_request.KeyType = ID_NetworkKey;
                			params.APSME_TRANSPORT_KEY_request.DestinationAddress = params.NLME_JOIN_indication.ExtendedAddress;
                			params.APSME_TRANSPORT_KEY_request.TransportKeyData.NetworkKey.UseParent = FALSE;
                			currentPrimitive = APSME_TRANSPORT_KEY_request;
                  		}
                    #else
            		    params.APSME_UPDATE_DEVICE_request.Status = (params.NLME_JOIN_indication.secureJoin ) ? 0x00 : 0x01;
            		    params.APSME_UPDATE_DEVICE_request.DeviceShortAddress = params.NLME_JOIN_indication.ShortAddress;
            		    params.APSME_UPDATE_DEVICE_request.DeviceAddress = params.NLME_JOIN_indication.ExtendedAddress;
            		    GetTrustCenterAddress(&params.APSME_UPDATE_DEVICE_request.DestAddress);
            		    currentPrimitive = APSME_UPDATE_DEVICE_request;
                    #endif
                #else
                    currentPrimitive = NO_PRIMITIVE;
                #endif
                break;

            case NLME_LEAVE_indication:
                if (!memcmppgm2ram( &params.NLME_LEAVE_indication.DeviceAddress, (ROM void *)&macLongAddr, 8 ))
                {
                    LREP( (ROM char *)"We have left the network.\r\n" );
                }
                else
                {
                    LREP( (ROM char *)"Another node has left the network.\r\n" );
                }
                #ifdef I_SUPPORT_SECURITY
        			{
            			SHORT_ADDR		LeavingChildShortAddress;
            			if( !APSFromLongToShort(&params.NLME_LEAVE_indication.DeviceAddress) )
            			{
            				currentPrimitive = NO_PRIMITIVE;
            				break;
            			}
            			LeavingChildShortAddress = currentAPSAddress.shortAddr;

                        #ifdef I_AM_TRUST_CENTER
                			params.APSME_UPDATE_DEVICE_indication.Status = 0x02;
                			params.APSME_UPDATE_DEVICE_indication.DeviceAddress = params.NLME_LEAVE_indication.DeviceAddress;
                			GetMACAddress(&params.APSME_UPDATE_DEVICE_indication.SrcAddress);
                			params.APSME_UPDATE_DEVICE_indication.DeviceShortAddress = LeavingChildShortAddress;
                			currentPrimitive = APSME_UPDATE_DEVICE_indication;
                			break;
                        #else
                			params.APSME_UPDATE_DEVICE_request.Status = 0x02;
                			// omit to do this since the address overlap
                			//params.APSME_UPDATE_DEVICE_request.DeviceAddress = params.NLME_LEAVE_indication.DeviceAddress;
                			GetTrustCenterAddress(&params.APSME_UPDATE_DEVICE_request.DestAddress);
                			params.APSME_UPDATE_DEVICE_request.DeviceShortAddress = LeavingChildShortAddress;
                			currentPrimitive = APSME_UPDATE_DEVICE_request;
                			break;
                        #endif
			        }

                #else
                    currentPrimitive = NO_PRIMITIVE;
                #endif
                break;

            case NLME_RESET_confirm:
                LREP( (ROM char *)"ZigBee Stack has been reset.\r\n" );
                currentPrimitive = NO_PRIMITIVE;
                break;

            case APSDE_DATA_confirm:
                if (params.APSDE_DATA_confirm.Status)
                {
                    LREP( (ROM char *)"Error " );
                    LREP("%02X",  params.APSDE_DATA_confirm.Status );
                    LREP( (ROM char *)" sending message.\r\n" );
                }
                else
                {
                    LREP( (ROM char *)" Message sent successfully.\r\n" );
                }
                currentPrimitive = NO_PRIMITIVE;
                break;

            case APSDE_DATA_indication:
                {
                    WORD_VAL    attributeId;
                    BYTE        command;
                    BYTE        data;
                    BYTE        dataLength;
                    BYTE        frameHeader;
                    BYTE        sequenceNumber;
                    BYTE        transaction;
                    BYTE        transByte;

                    currentPrimitive = NO_PRIMITIVE;
                    frameHeader = APLGet();

                    switch (params.APSDE_DATA_indication.DstEndpoint)
                    {
                        case EP_ZDO:

                            // Put code here to handle any ZDO responses that we requested
                            if ((frameHeader & APL_FRAME_TYPE_MASK) == APL_FRAME_TYPE_MSG)
                            {
                                frameHeader &= APL_FRAME_COUNT_MASK;
                                for (transaction=0; transaction<frameHeader; transaction++)
                                {
                                    sequenceNumber          = APLGet();
                                    dataLength              = APLGet();
                                    transByte               = 1;    // Account for status byte

                                    switch( params.APSDE_DATA_indication.ClusterId )
                                    {

                                        // ********************************************************
                                        // Put a case here to handle each ZDO response that we requested.
                                        // ********************************************************

                                        #ifndef USE_BINDINGS
                                        case NWK_ADDR_rsp:
                                            if (APLGet() == SUCCESS)
                                            {
                                                LREP( (ROM char *)"Receiving NWK_ADDR_rsp.\r\n" );

                                                // Skip over the IEEE address of the responder.
                                                for (data=0; data<8; data++)
                                                {
                                                    APLGet();
                                                    transByte++;
                                                }
                                                destinationAddress.byte.LSB = APLGet();
                                                destinationAddress.byte.MSB = APLGet();
                                                transByte += 2;
                                                myStatusFlags.bits.bDestinationAddressKnown = 1;
                                            }
                                            break;
                                        #endif

                                        #ifdef USE_BINDINGS
                                        case END_DEVICE_BIND_rsp:
                                            switch( APLGet() )
                                            {
                                                case SUCCESS:
                                                    LREP( (ROM char *)"End device bind/unbind successful!\r\n" );
                                                    myStatusFlags.bits.bIsBound ^= 1;
//                                                    BIND_INDICATION = !myStatusFlags.bits.bIsBound;
                                                    break;
                                                case ZDO_NOT_SUPPORTED:
                                                    LREP( (ROM char *)"End device bind/unbind not supported.\r\n" );
                                                    break;
                                                case END_DEVICE_BIND_TIMEOUT:
                                                    LREP( (ROM char *)"End device bind/unbind time out.\r\n" );
                                                    break;
                                                case END_DEVICE_BIND_NO_MATCH:
                                                    LREP( (ROM char *)"End device bind/unbind failed - no match.\r\n" );
                                                    break;
                                                default:
                                                    LREP( (ROM char *)"End device bind/unbind invalid response.\r\n" );
                                                    break;
                                            }
                                            myStatusFlags.bits.bTryingToBind = 0;
                                            break;
                                        #endif

                                        default:
                                            break;
                                    }

                                    // Read out the rest of the MSG in case there is another transaction.
                                    for (; transByte<dataLength; transByte++)
                                    {
                                        APLGet();
                                    }
                                }
                            }
                            break;

                        // ************************************************************************
                        // Place a case for each user defined endpoint.
                        // ************************************************************************

                        case EP_LIGHT:
                            if ((frameHeader & APL_FRAME_TYPE_MASK) == APL_FRAME_TYPE_KVP)
                            {
                                frameHeader &= APL_FRAME_COUNT_MASK;
                                for (transaction=0; transaction<frameHeader; transaction++)
                                {
                                    sequenceNumber          = APLGet();
                                    command                 = APLGet();
                                    attributeId.byte.LSB    = APLGet();
                                    attributeId.byte.MSB    = APLGet();

                                    //dataType = command & APL_FRAME_DATA_TYPE_MASK;
                                    command &= APL_FRAME_COMMAND_MASK;

                                    if ((params.APSDE_DATA_indication.ClusterId == OnOffSRC_CLUSTER) &&
                                        (attributeId.Val == OnOffSRC_OnOff))
                                    {
                                        if ((command == APL_FRAME_COMMAND_SET) ||
                                            (command == APL_FRAME_COMMAND_SETACK))
                                        {
                                            // Prepare a response in case it is needed.
                                            TxBuffer[TxData++] = APL_FRAME_TYPE_KVP | 1;    // KVP, 1 transaction
                                            TxBuffer[TxData++] = sequenceNumber;
                                            TxBuffer[TxData++] = APL_FRAME_COMMAND_SET_RES | (APL_FRAME_DATA_TYPE_UINT8 << 4);
                                            TxBuffer[TxData++] = attributeId.byte.LSB;
                                            TxBuffer[TxData++] = attributeId.byte.MSB;

                                            // Data type for this attibute must be APL_FRAME_DATA_TYPE_UINT8
                                            data = APLGet();
                                            switch (data)
                                            {
                                                case LIGHT_OFF:
                                                    LREP( (ROM char *)"Turning light off.\r\n" );
//                                                    MESSAGE_INDICATION = 0;
                                                    TxBuffer[TxData++] = SUCCESS;
                                                    break;
                                                case LIGHT_ON:
                                                    LREP( (ROM char *)"Turning light on.\r\n" );
//                                                    MESSAGE_INDICATION = 1;
                                                    TxBuffer[TxData++] = SUCCESS;
                                                    break;
                                                case LIGHT_TOGGLE:
                                                    LREP( (ROM char *)"Toggling light.\r\n" );
//                                                    MESSAGE_INDICATION ^= 1;
                                                    TxBuffer[TxData++] = SUCCESS;
                                                    break;
                                                default:
                                                    LREP("%02X",  data );
                                                    LREP( (ROM char *)" Invalid light message.\r\n" );
                                                    TxBuffer[TxData++] = KVP_INVALID_ATTRIBUTE_DATA;
                                                    break;
                                            }
                                        }
                                        if (command == APL_FRAME_COMMAND_SETACK)
                                        {
                                            // Send back an application level acknowledge.
                                            ZigBeeBlockTx();

                                            // Take care here that parameters are not overwritten before they are used.
                                            // We can use the data byte as a temporary variable.
                                            params.APSDE_DATA_request.DstAddrMode = params.APSDE_DATA_indication.SrcAddrMode;
                                            params.APSDE_DATA_request.DstEndpoint = params.APSDE_DATA_indication.SrcEndpoint;
                                            params.APSDE_DATA_request.DstAddress.ShortAddr = params.APSDE_DATA_indication.SrcAddress.ShortAddr;

                                            //params.APSDE_DATA_request.asduLength; TxData
                                            //params.APSDE_DATA_request.ProfileId; unchanged
                                            params.APSDE_DATA_request.RadiusCounter = DEFAULT_RADIUS;
                                            params.APSDE_DATA_request.DiscoverRoute = ROUTE_DISCOVERY_ENABLE;
											#ifdef I_SUPPORT_SECURITY
												params.APSDE_DATA_request.TxOptions.Val = 1;
											#else
                                            	params.APSDE_DATA_request.TxOptions.Val = 0;
											#endif
                                            params.APSDE_DATA_request.SrcEndpoint = EP_LIGHT;
                                            //params.APSDE_DATA_request.ClusterId; unchanged

                                            currentPrimitive = APSDE_DATA_request;
                                        }
                                        else
                                        {
                                            // We are not sending an acknowledge, so reset the transmit message pointer.
                                            TxData = TX_DATA_START;
                                        }
                                    }
                                    // TODO read to the end of the transaction.
                                } // each transaction
                            } // frame type
                            break;
                        default:
                            // If the command type was something that requested an acknowledge, we could send back
                            // KVP_INVALID_ENDPOINT here.
                            break;
                    }
                    APLDiscardRx();
                }
                break;

            case NO_PRIMITIVE:
                if (!ZigBeeStatus.flags.bits.bNetworkFormed)
                {
                    if (!ZigBeeStatus.flags.bits.bTryingToFormNetwork)
                    {
                        LREP( (ROM char *)"Trying to start network...\r\n" );
                        params.NLME_NETWORK_FORMATION_request.ScanDuration          = 8;
                        params.NLME_NETWORK_FORMATION_request.ScanChannels.Val      = ALLOWED_CHANNELS;
                        params.NLME_NETWORK_FORMATION_request.PANId.Val             = 0xFFFF;
                        params.NLME_NETWORK_FORMATION_request.BeaconOrder           = MAC_PIB_macBeaconOrder;
                        params.NLME_NETWORK_FORMATION_request.SuperframeOrder       = MAC_PIB_macSuperframeOrder;
                        params.NLME_NETWORK_FORMATION_request.BatteryLifeExtension  = MAC_PIB_macBattLifeExt;
                        currentPrimitive = NLME_NETWORK_FORMATION_request;
                    }
                }
                else
                {
                    if (ZigBeeReady())
                    {

                        // ************************************************************************
                        // Place all processes that can send messages here.  Be sure to call
                        // ZigBeeBlockTx() when currentPrimitive is set to APSDE_DATA_request.
                        // ************************************************************************

                        #ifdef I_AM_SWITCH
                        if ( myStatusFlags.bits.bLightSwitchToggled )
                        {
                            // Send a light toggle message to the other node.
                            myStatusFlags.bits.bLightSwitchToggled = FALSE;
                            ZigBeeBlockTx();

                            TxBuffer[TxData++] = APL_FRAME_TYPE_KVP | 1;    // KVP, 1 transaction
                            TxBuffer[TxData++] = APLGetTransId();
                            TxBuffer[TxData++] = APL_FRAME_COMMAND_SET | (APL_FRAME_DATA_TYPE_UINT8 << 4);
                            TxBuffer[TxData++] = OnOffSRC_OnOff & 0xFF;         // Attribute ID LSB
                            TxBuffer[TxData++] = (OnOffSRC_OnOff >> 8) & 0xFF;  // Attribute ID MSB
                            TxBuffer[TxData++] = LIGHT_TOGGLE;

                            #ifdef USE_BINDINGS
                                // We are sending indirect
                                params.APSDE_DATA_request.DstAddrMode = APS_ADDRESS_NOT_PRESENT;
                            #else
                                // We are sending direct
                                params.APSDE_DATA_request.DstAddrMode = APS_ADDRESS_16_BIT;
                                params.APSDE_DATA_request.DstEndpoint = EP_LIGHT;
                                params.APSDE_DATA_request.DstAddress.ShortAddr = destinationAddress;
                            #endif

                            //params.APSDE_DATA_request.asduLength; TxData
                            params.APSDE_DATA_request.ProfileId.Val = MY_PROFILE_ID;
                            params.APSDE_DATA_request.RadiusCounter = DEFAULT_RADIUS;
                            params.APSDE_DATA_request.DiscoverRoute = ROUTE_DISCOVERY_ENABLE;
							#ifdef I_SUPPORT_SECURITY
								params.APSDE_DATA_request.TxOptions.Val = 1;
							#else
                            	params.APSDE_DATA_request.TxOptions.Val = 0;
							#endif
                            params.APSDE_DATA_request.SrcEndpoint = EP_LIGHT;
                            params.APSDE_DATA_request.ClusterId = OnOffSRC_CLUSTER;

                            LREP( (ROM char *)" Trying to send light switch message.\r\n" );

                            currentPrimitive = APSDE_DATA_request;
                        }
                        else
                        #endif
                        #ifdef USE_BINDINGS
                        if (myStatusFlags.bits.bBindSwitchToggled)
                        {
                            myStatusFlags.bits.bBindSwitchToggled = FALSE;
                            if (myStatusFlags.bits.bTryingToBind)
                            {
                                LREP( (ROM char *)" End Device Binding already in progress.\r\n" );
                            }
                            else
                            {
                                myStatusFlags.bits.bTryingToBind = 1;

                                // Send down an end device bind primitive.
                                LREP( (ROM char *)" Trying to perform end device binding.\r\n" );
                                currentPrimitive = ZDO_END_DEVICE_BIND_req;

                                params.ZDO_END_DEVICE_BIND_req.ProfileID.Val = MY_PROFILE_ID;
                                #ifdef I_AM_LIGHT
                                    params.ZDO_END_DEVICE_BIND_req.NumInClusters = 1;
                                    if ((params.ZDO_END_DEVICE_BIND_req.InClusterList=SRAMalloc(1)) != NULL)
                                    {
                                        *params.ZDO_END_DEVICE_BIND_req.InClusterList = OnOffSRC_CLUSTER;
                                    }
                                    else
                                    {
                                        myStatusFlags.bits.bTryingToBind = 0;
                                        LREP( (ROM char *)" Could not send down ZDO_END_DEVICE_BIND_req.\r\n" );
                                        currentPrimitive = NO_PRIMITIVE;
                                    }
                                #else
                                    params.ZDO_END_DEVICE_BIND_req.NumInClusters = 0;
                                    params.ZDO_END_DEVICE_BIND_req.InClusterList = NULL;
                                #endif
                                #ifdef I_AM_SWITCH
                                    params.ZDO_END_DEVICE_BIND_req.NumOutClusters = 1;
                                    if ((params.ZDO_END_DEVICE_BIND_req.OutClusterList=SRAMalloc(1)) != NULL)
                                    {
                                        *params.ZDO_END_DEVICE_BIND_req.OutClusterList = OnOffSRC_CLUSTER;
                                    }
                                    else
                                    {
                                        myStatusFlags.bits.bTryingToBind = 0;
                                        LREP( (ROM char *)" Could not send down ZDO_END_DEVICE_BIND_req.\r\n" );
                                        currentPrimitive = NO_PRIMITIVE;
                                    }
                                #else
                                    params.ZDO_END_DEVICE_BIND_req.NumOutClusters = 0;
                                    params.ZDO_END_DEVICE_BIND_req.OutClusterList = NULL;
                                #endif
                                params.ZDO_END_DEVICE_BIND_req.LocalCoordinator = macPIB.macShortAddress;
                                params.ZDO_END_DEVICE_BIND_req.endpoint = EP_LIGHT;
                            }
                        }
                        #else
                        if (myStatusFlags.bits.bBroadcastSwitchToggled)
                        {
                            myStatusFlags.bits.bBroadcastSwitchToggled = FALSE;

                            // Send NWK_ADDR_req message
                            ZigBeeBlockTx();

                            TxBuffer[TxData++] = APL_FRAME_TYPE_MSG | 1;    // KVP, 1 transaction
                            TxBuffer[TxData++] = APLGetTransId();
                            TxBuffer[TxData++] = 10; // Transaction Length

                            // IEEEAddr
                            TxBuffer[TxData++] = 0x65;
                            TxBuffer[TxData++] = 0x00;
                            TxBuffer[TxData++] = 0x00;
                            TxBuffer[TxData++] = 0x00;
                            TxBuffer[TxData++] = 0x00;
                            TxBuffer[TxData++] = 0xa3;
                            TxBuffer[TxData++] = 0x04;
                            TxBuffer[TxData++] = 0x00;

                            // RequestType
                            TxBuffer[TxData++] = 0x00;

                            // StartIndex
                            TxBuffer[TxData++] = 0x00;

                            params.APSDE_DATA_request.DstAddrMode = APS_ADDRESS_16_BIT;
                            params.APSDE_DATA_request.DstEndpoint = EP_ZDO;
                            params.APSDE_DATA_request.DstAddress.ShortAddr.Val = 0xFFFF;

                            //params.APSDE_DATA_request.asduLength; TxData
                            params.APSDE_DATA_request.ProfileId.Val = ZDO_PROFILE_ID;
                            params.APSDE_DATA_request.RadiusCounter = DEFAULT_RADIUS;
                            params.APSDE_DATA_request.DiscoverRoute = ROUTE_DISCOVERY_ENABLE;
							#ifdef I_SUPPORT_SECURITY
								params.APSDE_DATA_request.TxOptions.Val = 1;
							#else
                            	params.APSDE_DATA_request.TxOptions.Val = 0;
							#endif
                            params.APSDE_DATA_request.SrcEndpoint = EP_ZDO;
                            params.APSDE_DATA_request.ClusterId = NWK_ADDR_req;

                            LREP( (ROM char *)" Trying to send NWK_ADDR_req.\r\n" );

                            currentPrimitive = APSDE_DATA_request;
                        }
                        #endif

                        // Re-enable interrupts.
//                        #if defined(__C30__)
//	                        IEC1bits.CNIE = 1;
//	                    #else
//	                    	INTCONbits.RBIE = 1;
//	                    #endif
                    }
                }
                break;

            default:
                LREP("%02X",  currentPrimitive );
                LREP( (ROM char *)" Unhandled primitive.\r\n" );
                currentPrimitive = NO_PRIMITIVE;
                break;
        }

        // *********************************************************************
        // Place any non-ZigBee related processing here.  Be sure that the code
        // will loop back and execute ZigBeeTasks() in a timely manner.
        // *********************************************************************

//        #if !defined (__18F4620) && !defined(__C30__)
//            if (PORTBbits.RB3 == SWITCH_PRESSED)
//            {
//                LATDbits.LATD7 = 1;
//            }
//            else
//            {
//                LATDbits.LATD7 = 0;
//            }
//        #endif

    }
	lib_threadStop(txThread, 1000);
	mrf24j40_freeDevice(g_rfDevice);
	lib_semPost(s_semTx);
	lib_semPost(s_semRx);
	lib_semFree(s_semTx);
	lib_semFree(s_semRx);
	eepromMemoryDestroy();
	LREP("QUIT.\n");
	return 0;
}
void nothing_fxn(){

}
void UserInterruptHandler(){

}
int mac_callback(int type, void* param, void* obj){
	if(type == MRF24J40_CALLBACK_TYPE_RX){
		MRF24J40_CALLBACK_RX_PARAM* rx = (MRF24J40_CALLBACK_RX_PARAM*)param;
		MAC_RX_DATA_PACKET* pkt = (MAC_RX_DATA_PACKET*) rx->packet;
		int frameLen = pkt->frameLen;
		int payloadLen = frameLen - 2 - sizeof(MAC_HEADER);
		if(frameLen < 0) frameLen = 0;
		if(frameLen > 256) frameLen = 256;
		if(payloadLen < 0) payloadLen = 0;
		if(payloadLen > 256) payloadLen = 256;
//		LREP("rx %d bytes\n", rx->length);
//		DUMP(&pkt->header, sizeof(MAC_HEADER), "header %d bytes", sizeof(MAC_HEADER));
//		DUMP(pkt->payload, payloadLen, "%d --> rx %d bytes",pkt->header.srcAddr, payloadLen);

		if(s_optMode == 1){
			memcpy(s_txBuffer, pkt->payload, payloadLen);
			s_txLength = payloadLen;
			s_txDestId = pkt->header.srcAddr;
			lib_semPost(s_semTx);
		}else if(s_optMode == 2){
			memcpy(s_rxBuffer, pkt->payload, payloadLen);
			s_rxLength = payloadLen;
			lib_semPost(s_semRx);
		}
	}
	return 0;
}
void tx_thread(void* obj, int* terminate){
	void* mrf = obj;
	int ret;
	void *tx;
	LREP("tx thread is running.\n");
	while((*terminate) == 0){
		ret = lib_semPend(s_semTx, 100);
		if(ret < 0){
			LREP_WARN("pend sem failed.\n");
			break;
		}else if(ret > 0){
			//LREP(".");

//			lib_sleepMs(10);
			//DUMP( s_txBuffer, s_txLength, "tx --> %d", s_txDestId);
			tx = mrf24j40_getTxPayload(mrf);
			memcpy(tx, s_txBuffer, s_txLength);
			mrf24j40_sendDataPacket16(mrf, s_txLength,
								0xcafe, s_txDestId, 1, 0, 0, 0);
		}
	}
	LREP("tx thread is stopped.\n");
}
