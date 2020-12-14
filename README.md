# DTU软件编译开发环境

- 应用软件的开发可基于ubuntu平台开发与模拟运行，在ubuntu环境下需要准备些运行环境。

## 一、Redis安装与配置

这些操作只在首次未安装redis环境时操作一次即可。

### 1.1 Redis-Server

```shell
apt install redis-server
```

打开配置文件

```shell
vi /etc/redis/redis.conf
```

查看运行状态

```shell
systemctl status redis
```

启动redis服务

```shell
service redis start
```

关闭redis服务

```shell
$ sudo service redis stop
```

### 1.3 hiredis

下载

```shell
git clone  https://github.com/redis/hiredis
```

安装

```shell
cd hiredis
make && make install
```

修改配置文件，增加链接目录

```shell
# 打开配置文件
vi ~/.bashrc
# 在里面添加共享库搜索目录
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
# 退出VI，让配置生效
source ~/.bashrc
```

## 二、模块化开发

在开发过程中，每个模块开发人员，原则上不可提交模块自身以外的代码，模块的划分及目录的配置如下：

| 目录名         | 目录      | 说明                                       |
| -------------- | --------- | ------------------------------------------ |
| 通用文件       | common    | 系统共用的头文件或定义，由其它模块调用     |
| 配置文件       | config    | 系统配置文件相关，启动脚本，数据表定义等   |
| 数据服务       | dbs       | 数据库管理，模拟环境下由其它模块直接调用   |
| 设备服务       | devs      | 系统设备，模拟环境下由其它模块直接调用     |
| 保护逻辑与计算 | m4/relay  | 生成可执行文件，Ubuntu上可直接运行         |
| 通讯协议处理   | protocol  | 生成可执行文件，Ubuntu上可直接运行         |
| DTU模拟器      | simulator | 提供DIO模拟，ADC控制接口，Ubuntu可直接运行 |

**因为多模块联合编译时的功能切换宏的问题，需要重新编译其它模块时，请使用make clean先清除再重新make编译，如编译了m4后，需要重新编译simulator，则对simulator进行make clean**

### 2.1 模拟器使用

模拟器仅用于在PC上Ubuntu下的模拟运行，可以以命令行的方式，提供基本的DIO操作，ADC控制（根据调试需求，持续完善中），这些操作的结果，将被记录于数据库中。在其它的模块读取DIO的结果时，可以反应出来。

编译与运行（需要redis的支持）

```shell
cd simulator
make
 ./simulator.out
```

运行之后可以进入模拟器的命令模式，输入help可查看所支持的命令模式

```shell
------ DTU Simulator v1.0.0 (Dec 14 2020 10:12:52) ------
DTU > help
?        - Print all shell commands
help     - Print all shell commands
q        - quit
dbset    - Set Database key-value
dbget    - Get Database key-value
lsdi     - List DI status
lsdo     - List DO status
setdo    - Set DO status to 1
setdi    - Set DI status to 1
clrdo    - Clear DO status to 0
clrdi    - Clear DI status to 0
togdo    - Toggle DO status
togdi    - Toggle DI status
DTU >
```



### 2.2 M4相关的保护与计算

M4相关的部分只设置了两个函数，中断处理和主进程，对应的函数入口于relay_isr.c和relay_main.c中，相应的头文件位于m4/relay/inc中。

编译：

```shell
cd dtu_apps/m4
make
./m4firm.out
```

将会生成**m4firm.out**文件，可直接在ubuntu环境下运行，常见的C函数都可以使用。

### 2.3 协议进程



