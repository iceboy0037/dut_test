# 说明
- 依赖hiredis 和sqlite 库

## hiredis编译
```bash

cd dtu_apps/thirdparty/hiredis

. /opt/fsl-imx-fb/5.4-zeus/environment-setup-cortexa9t2hf-neon-poky-linux-gnueabi

make
PREFIX=./build  make install

mkdir  /nfsroot/usr/local/hiredis
cp -ad dtu_apps/thirdparty/hiredis/build/* /nfsroot/usr/local/hiredis/

# 开发板上配置
vi /etc/ld.so.conf
#添加一行
/usr/local/hiredis/lib
#保存退出后执行
ldconfig
```

## sqlite编译
```bash
# /xxxxxx/dtu_apps/thirdparty/sqlite/build使用绝对路径
./configure  --host=arm-poky-linux-gnueabi --prefix=/xxxxxx/dtu_apps/thirdparty/sqlite/build

make && make install

mkdir  /nfsroot/usr/local/sqlite
cp -ad dtu_apps/thirdparty/sqlite/build/* /nfsroot/usr/local/sqlite/


# 开发板上配置
vi /etc/ld.so.conf
#添加一行
/usr/local/sqlite/lib
#保存退出后执行
ldconfig
```