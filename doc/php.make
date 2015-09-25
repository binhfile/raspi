http://jp1.php.net/distributions/php-5.5.13.tar.bz2
request
	libxml2
------------- uclibc -----------------
export PATH=$PATH:/home/toolchain/raspi/bin
./configure CC=arm-linux-gcc CXX=arm-linux-g++ AR=arm-linux-ar LD=arm-linux-ld RANLIB=arm-linux-ranlib --host=arm-linux --target=arm -prefix=/home/dev/Desktop/PI/build/fs --with-sqlite3 --without-pdo-sqlite --without-pear --enable-simplexml --disable-mbregex --enable-sockets --enable-fpm --disable-opcache --enable-libxml --without-zlib --enable-session --with-libxml-dir=/home/dev/Desktop/PI/build/fs --enable-sysvmsg --disable-all
make 
make install
