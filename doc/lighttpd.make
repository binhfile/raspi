wget http://download.lighttpd.net/lighttpd/releases-1.4.x/lighttpd-1.4.33.tar.gz
------------- uclibc -----------------
export PATH=$PATH:/home/toolchain/raspi/bin
./configure -prefix=/home/dev/Desktop/PI/build/fs -host=arm-linux CC=arm-linux-gcc  RANLIB=arm-linux-ranlib STRIP=arm-linux-strip --without-zlib --without-bzip2 --without-pcre
make
make install
@note find /tmp/home/root@host
