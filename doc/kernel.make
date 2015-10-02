export PATH=$PATH:/home/toolchain/raspi/bin
make ARCH=arm CROSS_COMPILE=arm-linux- bcm2709_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux- menuconfig
make ARCH=arm CROSS_COMPILE=arm-linux- zImage modules dtbs
mkimage/mkknlimg arch/arm/boot/zImage kernel.img
mkdir -p _boot/overlays
cp kernel.img _boot/
cp arch/arm/boot/dts/*.dtb _boot/
cp arch/arm/boot/dts/overlays/*.dtb _boot/overlays/ 
make ARCH=arm CROSS_COMPILE=arm-linux- modules_install  INSTALL_MOD_PATH=modules_install
make ARCH=arm CROSS_COMPILE=arm-linux- firmware_install  INSTALL_MOD_PATH=modules_install
