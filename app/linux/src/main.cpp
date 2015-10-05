#include <stdio.h>
#include <lib_debug.h>
#include <mrf24j40.h>
#include <iostream>

#define DEV_RESET_GPIO_NUM	 (18)
#define DEV_INT_GPIO_NUM	 (23)
#define DEV_CMD				 "/dev/spidev0.0"

int main(int argc, char** argv){
	std::string sz;

	driver::MRF24J40* mrf = new driver::MRF24J40(DEV_CMD,
			DEV_RESET_GPIO_NUM,
			DEV_INT_GPIO_NUM);
	if(mrf->openDevice() != 0){
		LREP("open device failed.\n");
		delete mrf;
		return 0;
	}
	LREP("open done\n");
	mrf->initDevice();
	mrf->setPan(0xcafe);
	mrf->setAddress16(0x6001);
	while(1){
		std::cout<<">";
		std::cin>>sz;
		if(sz == "q") break;
		else if(sz == "s"){
			std::cout<<"send>";
			std::cin>>sz;
			mrf->sendData(0x4202, sz.c_str(), sz.length());
		}
		else if(sz == "i"){
			mrf->initDevice();
		}
	}
	mrf->closeDevice();
	delete mrf;
	LREP("QUIT.\n");
	return 0;
}
