#! bin/bash

platfrom=$1

if [ ! -d './build' ];then
	mkdir ./build
fi

if [ ! -d './build/'$platfrom ];then
	mkdir ./build/$platfrom
fi
pwd=`pwd`

cmd_str="./configure --prefix=$pwd/build/$platfrom"

if [ "$platfrom"x = "mac"x ] 
then
	cmd_str+=" CPPFLAGS=\"-I/usr/local/Cellar/openssl/1.0.2k/include\" LDFLAGS=\"-I/usr/local/Cellar/openssl/1.0.2k/lib\""
fi
echo $cmd_str


#./configure -prefix=/Users/heyuhan/Desktop/ppt_demo/server/src/3rd/libevent/build/mac/ CPPFLAGS="-I/usr/local/Cellar/openssl/1.0.2h_1/include" LDFLAGS="-I/usr/local/Cellar/openssl/1.0.2h_1/lib" 