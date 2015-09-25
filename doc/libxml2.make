http://xmlsoft.org/sources/libxml2-2.7.3.tar.gz
export PATH=$PATH:/home/toolchain/raspi/bin
------------- uclibc -----------------
./configure CC=arm-linux-gcc --host=arm-linux --prefix=/home/dev/Desktop/PI/build/fs ARCH=arm AR=arm-linux-ar LD=arm-linux-ld RANLIB=arm-linux-ranlib --without-python --without-iconv --without-zlib
