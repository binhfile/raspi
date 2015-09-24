export PATH=$PATH:/home/toolchain/raspi-toolchain/bin
make ARCH=arm CROSS_COMPILE=arm-linux- bcm2709_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux- menuconfig
make ARCH=arm CROSS_COMPILE=arm-linux- zImage modules dtbs
mkdir -p _boot/overlays
mkknlimg arch/arm/boot/zImage kernel.img
cp kernel.img _boot/
cp arch/arm/boot/dts/*.dtb _boot/
cp arch/arm/boot/dts/overlays/*.dtb _boot/overlays/ 
