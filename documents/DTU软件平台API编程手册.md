# DTU软件开发平台API编程指南

## 更改说明：

| 日期       | 作者   | 修改                                    |
| ---------- | ------ | --------------------------------------- |
| 2020-12-28 | 游荣强 | 添加总体描述，环境及部分API接口函数说明 |
| 2020-12-30 | 贾世鹏 | 添加DIO、MSG、MU接口说明                |
| 2020-12-30 | 游荣强 | 增加系统监测定义                        |

## 一、概述

DTU设备软件开发平台，是在Linux的环境下，建立的一个应用程序开发环境。通过软件模拟的方式，实现DTU设备主要的硬件设备数据（ADC板、DI板、DO板）的输入与输出，建立与实际产品相同的数据库支持环境，可以在纯软件模式下实现DTU应用软件的开发与调试。

实际产品上的应用程序的编译，通过在编译环境中设置交叉编译工具实现，编译过程与在虚拟环境下的编译方式基本相同。



## 二、环境

### 2.1 环境支持

系统平台需要数据库的支持，在实际的产品中使用了内存数据库Redis和关系数据库Sqlite3相结合的方式，Redis运行于内存，可以提供快速的访问接口。Sqlite3用于数据持久化，及更好的数据关系管理。Redis通过hiredis第三方库提供接口支持，在hiredis的基础上提供应用编程接口。

在进行编译开发之前，先安装以下三种插件：

#### 2.1.1 Redis-Server

安装，在ubuntu环境下直接使用apt命令安装即可，安装完毕可使用redis-cli命令，若能进入redis控制台，则可不再作其它操作。

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

#### 2.1.2 hiredis

hiredis提供redis数据库的访问接口，本系统是在其基础上封装出应用API接口。安装只能通过源码方式安装。

```shell
git clone  https://github.com/redis/hiredis
```

安装

```shell
cd hiredis
make && make install
```

修改配置文件，增加链接目录。若无此步，在编译时可能会出现找不到链接库的错误

```shell
# 打开配置文件
vi ~/.bashrc
# 在里面添加共享库搜索目录
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
# 退出VI，让配置生效
source ~/.bashrc
```

#### 2.1.3 sqlite3

数据的持久化通过sqlite3实现，在ubuntu下通过apt命令安装即可

```shell
apt install sqlite3 && apt install libsqlite3-dev
```

### 2.2 项目配置

项目Git位置：http://192.168.7.16:3000/gitadmin/dtu_apps。

#### 2.2.1 目录说明

整个工程克隆到本地之后，可以看到如下的目录配置

| 目录       | 功能说明                                                     |
| ---------- | ------------------------------------------------------------ |
| common     | 各个模块共用文件目录                                         |
| config     | 配置文件相关，实际发布的数据库文件，系统启动脚本配置等（虚拟环境不关心） |
| dbs        | 数据库操作操作API接口及服务                                  |
| devs       | 硬件（ADC/DIO等）相关API，非独立编译，PC环境时通过算法产生输入输出 |
| m4         | m4核app，独立编译出可执行文件，PC上可正常运行调试            |
| mu         | 双核管理代码                                                 |
| protocol   | IEC104/101应用APP，独立编译，PC上正常运行调试                |
| simulator  | 模拟器，独立编译APP，命令行方式操作数据库，模拟硬件设备      |
| startup    | 整个APP系统，启动及监控代码，独立编译出APP，在PC上可独立调试 |
| thirdparty | 第三方支持库，在应用开发中无需关心                           |
| documents  | 代码说明文档，API接口说明，版本更新说明等，存放于该目录下    |

#### 2.2.2 模拟器使用

模拟器仅用于在PC上Ubuntu下的模拟运行，可以以命令行的方式，提供基本的DIO操作，ADC控制（根据调试需求，持续完善中），这些操作的结果，将被记录于数据库中。在其它的模块读取DIO的结果时，可以反应出来。

编译与运行

```shell
cd simulator
make clean && make
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
lsyc     - List all YC in RDB
setdo    - Set DO status to 1
setdi    - Set DI status to 1
clrdo    - Clear DO status to 0
clrdi    - Clear DI status to 0
togdo    - Toggle DO status
togdi    - Toggle DI status
saveyc   - Save YC table to RDB
readyc   - Read YC from RDB
DTU >
```

#### 2.2.3 M4应用开发

M4相关的部分只设置了两个函数，中断处理和主进程，对应的函数入口于relay_isr.c和relay_main.c中，相应的头文件位于m4/relay/inc中。

编译：

```shell
cd dtu_apps/m4
make
./m4firm.out
```

将会生成**m4firm.out**文件，可直接在ubuntu环境下运行，常见的C函数都可以使用。

#### 2.2.4 协议APP开发

协议进程位于protocol目录，直接在目录下使用make即可编译生成protocol.out可执行文件，编译时前已定义两个宏定义IEC101和IEC104。

## 三、全局定义

系统预先定义了一些头文件，用于定义系统，这些头文件主要位于common目录下的inc目录下，需要使用时可以直接通过#include指令添加头文件包括，无需指明路径。为简化编程，同时这些头文件统一通过dtu.h包含，每个APP可直接通过以下方式添加系统定义。

```c
#include "dtu.h"
```

### 3.1 数据类型

在dtu_types.h中提供常见的数据格式定义

```c
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

typedef int int32;
typedef short int16;
typedef char int8;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
```

关于TRUE和FALSE定义，在Linux环境下，通常约定返回为0时表示函数执行无错。但同时gcc又提供了true和false的定义，false = 0。为避免出错和混乱，同时也考虑代码兼容，在新增代码中，请勿再直接使用true或false作为函数的返回值，而是按约定的返回为0时即表示函数执行无错。



### 3.2 系统配置

系统配置用于定义实际设备的硬件接口板数量，及相关通道数量，定义于dtu_config.h文件

```c
#define CONFIG_PWR_BOARD_NUMBER		1	// Power board number
#define CONFIG_DO_BOARD_NUMBER 		2	// DO output board number
#define	CONFIG_DI_BOARD_NUMBER		4 	// DI input board number
#define CONFIG_AD_BOARD_NUMBER 		5	// AD board number
```



### 3.3 应用限制

应用限制，根据系统的硬件限制及业务需求，定义一些数据相关最大使用限制，定义于dtu_limits.h。

```c
#define	BUS_NUMBER_MAX		(4)	        	// 最大母线数量
#define LINE_NUMBER_MAX 	(16)	        // 最大线路数量

#define	MAX_TRAN_AI			2560	        // 遥测参数
#define MAX_TRAN_DI			2560	        // 遥信参数
#define	MAX_TRAN_DO			2560	        // 遥控参数
#define MAX_TRAN_DD			2560	        // 电度参数

#define TYPE_STR_LENGTH		16				// 数据类型字符串长度
#define POINT_DESC_LENGTH	32	        	// 点位描述字符串长度
#define DTU_YC_LIST_MAX     256             // 本机遥测点位最大数量
#define POINT_UNUSED        "UNUSED"
```



## 四、API接口说明

### 4.1 调试相关

系统预先定义了一些常见的函数，用于应用程序的调试。主要定义于dbg.h和dbg.c文件中。已统一A9和M4核上的接口标准，开发人员无需关心代码所在位置，以下函数都可以直接使用。

#### 4.1.1 带行号打印

与printf函数使用一样，但在打印输出时，会在前面加上调用位置的行号和文件名，以便于更好定位代码位置，可通过 *\__DEBUG\__*宏关闭输出。

``` c
int dbg(fmt, args...);
```

#### 4.1.2 直接打印

因为printf函数使用限制，开发中将禁止使用printf函数进行调试，替换的是println函数，使用方式与printf函数相同。

```c
int println(fmt, args...);
```

#### 4.1.3 打印浮点数组

```c
/**
 * @brief Printf float array
 * @param  buf memory buffer entry
 * @param  len size in floats
 * @return int
 */
int print_float(float *buf, int len);
```

#### 4.1.4 打印32位整形数组

```c
/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in ints
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
int print_int32(int *buf, int len, int type);
```

#### 4.1.5 打印16位整数数组

```c
/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in short
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
int print_int16(short *buf, int len, int type)
```

#### 4.1.6 打印8位字节数组

```c
/**
 * @brief Print memory buffer
 * @param  buf	memory buffer entry
 * @param  len	size in bytes
 * @param  type	PRINT_DEC or PRINT_HEX
 * @return int 0 - success
 */
int print_buf(char *buf, int len, int type);
```

### 4.2 ADC控制

在模拟环境下，ADC数据的产生由函数产生，该函数位于void adc_sample_thread(void *p)，可通过修改该函数中的数据生成部分val = (short)(sin(2 * pi * wave_count / sample_points) * 32768);产生不同的测试数据。

#### 4.2.1 ADC初始化

```c
/**
 * @brief Init ADC peripheral
 * @param  grid		ADC sample frequency
 * @param  points	ADC Sample count per period
 * @return int		0 - success
 */
int adc_init(int grid, int points);
```

#### 4.2.2 获取电网频率

```c
/**
 * @brief Get Current Grid frequency from FPGA
 * @param  grid	Store freq from FPGA
 * @return int 	0 - success
 */
int adc_get_grid_freq(float *grid);
```

#### 4.2.3 读取ADC采样数据

该函数仅在计算模块的中断处理函数中调用，指定的buf必须不小于平台设置最大80路，4个点缓存的数据，也就是640字节大小。

```c
/**
 * @brief Read ADC Buffer
 * @param  buf	Return ADC sample buffer, point count = adc_get_buff_count()
 * @return int
 */
int adc_get(short *buf);
```

#### 4.2.4 启动ADC转换

在模拟环境下，启动ADC将启动adc_sample_thread，同时将周期性触发M4中的中断。

```c
/**
 * @brief Start ADC sample, M4's relay_isr() will be called every adc_get_buff_count() points
 * @return int
 */
int adc_start(void);
```

#### 4.2.5 停止ADC转换

```c
/**
 * @brief Stop ADC sample, and relay_isr() will be stop
 * @return int
 */
int adc_stop(void);
```

### 4.3 DIO控制
接口函数若无特别说明，则在应用层编程时，无需作区分，在A9核和M4核都可以直接使用，使用情形取决于实际的应用场景。在PC调试环境下，DIO的状态可通过Simulator的控制台进行管理与监测。
#### 4.3.1 DIO 初始化
初始化DIO子系统，需要对DIO进行初始化操作。
```c
/**
 * @brief Init DIO system
 * @return int 0 - success
 */
int dio_init(void);
```

#### 4.3.2 获取DI值

在DTU的业务设计上，DI值由保护逻辑处理部分进行读取，当然在A9部分也可以调用该函数，可用于实际的DI状态监测。

```c
/**
 * @brief get DI
 * @param  buf              获取到的DI数据存放空间
 * @param  start            DI 起始号，从DI哪一位开始读取
 * @param  count            从DI 起始号开始获取多少个
 * @return int
 * 		0 success
 * 		-1 error
 */
int di_get(int *buf, int start, int count);
```

#### 4.3.3 置位DO
```c
/**
 * @brief set DO
 * @param  start            DO 起始号，从DO哪一位开始置位
 * @param  count            从DO 起始号开始置位多少个
 * @return int
 * 		0 success
 * 		-1 error
 */
int do_set(int start, int count);
```

#### 4.3.3 清零DO
```c
/**
 * @brief clear DO
 * @param  start            DO 起始号，从DO哪一位开始清零
 * @param  count            从DO 起始号开始清零多少个
 * @return int
 * 		0 success
 * 		-1 error
 */
int do_clr(int start, int count);
```

#### 4.3.4 设置单独的DO通道
```c
/**
 * @brief 设置DO 的index 通道 为 1 或 0
 * @param  index            要设置的DO 通道号
 * @param  value            要设置的DO 通道的值 1 或 0
 * @return int 0 - success
 */
int do_set_value(int index, int value);
```

### 4.4 电源板控制

TBD

### 4.5 遥测数据

ADC采样后通过M4程序计算生成电力交采遥测数据，这一部分通过结构体进行数据组织，以方便管理访问，每个遥测数据定义为yc_valut_t结构体

```c
struct yc_value_t {
	float	rating;		// 额定值
	float	raw;		// 原始值
	float	output;		// 原始值1次值
	int	q;				// 品质
};
```

设备自身的所有遥测值，再二次封装成系统自己和遥测计算结果，按线路，母线方式组织为数组，全部遥测数组又再次封装为yc_table_t结构体。计算完成后配合线路定义，直接将值写入结构体变量即可。

```c
struct yc_relay_bus_t {
	struct yc_value_t ua;
	struct yc_value_t ub;
	struct yc_value_t uc;
	struct yc_value_t uab;
	struct yc_value_t ubc;
};
struct yc_line_t {
	struct yc_value_t ia;
	struct yc_value_t ib;
	struct yc_value_t ic;
	struct yc_value_t i0;
	struct yc_value_t p;
	struct yc_value_t q;
	struct yc_value_t s;
	struct yc_value_t cos;
};
// 总遥测表结构
struct yc_table_t {
	struct yc_bus_t		bus[BUS_NUMBER_MAX];			// 母线电压遥测
	struct yc_line_t 	line[LINE_NUMBER_MAX];			// 线路遥测结构表
	struct yc_relay_bus_t	rbus[BUS_NUMBER_MAX]; 		// 保护遥测值
	struct yc_relay_line_t	rline[LINE_NUMBER_MAX];		// 保护线路遥测值
};
```

#### 4.5.1 遥测保存到实时库

保存于yc_table_t变量中的设备本身遥测数据，可通过该接口存储到实时库中。

```c
/**
 * @brief Save YC table to RT DB
 * @param entry YC table entry
 * $param name
 * @return int
 */
int yc_save_table(struct yc_table_t *base);
```

该接口将使用映射表创建变量与名称的映射，对遥测表的修改，需同时修改以下的表格。

```c
PT_MAP_START(yc)
	PT_ITEM("ua1",		PT_TYPE_FLOAT,	struct yc_table_t, 	bus[0].ua.raw)
	PT_ITEM("ub1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uc1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("uab1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
	PT_ITEM("ubc1",		PT_TYPE_FLOAT,	struct yc_table_t,	bus[0].ub.raw)
PT_MAP_END(yc)
```

保存的yc数据可通过模拟器的命令lsyc显示，如下所示。

```c
------ DTU Simulator v1.0.0 (Dec 28 2020 21:07:55) ------
DTU > lsyc
----------------YC Status----------------
                     Key         Status
       0:        yc:iz1:36        0.000000
       1:       yc:q10:182        0.000000
       2:       yc:s13:231        0.000000
       3:        yc:ic4:83        0.000000
       4:     yc:cos11:200        0.000000
       5:      yc:q11a:676        0.000000
       6:        yc:s9:167        0.000000
       7:       yc:cos3:72        0.000000
       8:      yc:s12b:696        0.000000
       9:         yc:uz1:7        0.000000
      10:        yc:iz2:52        0.000000
      11:      yc:s10b:664        0.000000
      12:        yc:ib2:50        0.000000
      13:     yc:cos8c:636        0.000000
      14:     yc:cos7c:620        0.000000
```

遥测在数据库中的编码，以yc开头，中间部分为遥测名称，最后部分为遥测内部ID号。

#### 4.5.2 遥测读取

遥测读取目前通过遥测的内部ID编号进行读取，返回值存储于value指向的数据量。

```c
/**
 * @brief Read YC by ID
 * @param  value Return value
 * @param  id	YC ID
 * @return int 0 - success
 */
int yc_read_single(void *value, int id);
```

### 4.6 双核交互

这部分的所有函数，**只允许系统的服务部分调用，业余逻辑所有模块（保护逻辑、远动计算、通讯模块等），禁止使用。**

#### 4.6.1 MSG 初始化
此接口M4和A9应用层共用，MSG 共享内存初始化，参数为共享内存起始地址。
```c
/**
 * @brief Message queue share memory init
 * @return int
 * 		0 success
 * 		-1 error
 */
int mq_init(unsigned int addr_base);
```

#### 4.6.2 申请一个MSG共享内存空间
此接口M4和A9应用层共用，申请一块空间，以便填充MSG数据
```c
/**
 * @brief Malloc a message memory
 * @return void*
 * 	The message address of the malloc
 */
void *mq_malloc_msg(void);
```

#### 4.6.3 释放一个或多个MSG共享内存空间
此接口M4和A9应用层共用
```c
/**
 * @brief free message memory
 * @param  count            message count
 * @return int
 * 		0 success
 * 		-1 error
 */
int mq_free_msg(int count);
```

#### 4.6.4 基于MSG和MU的log接口
M4端使用，向A9端传输一条log信息
```c
/**
 * @brief send a log to A9
 * @param  level            log level
 * @param  buf              log buffer
 * @param  size             log buffer size
 * @return int
 * 		0 success
 * 		-1 error
 */
int plog(int level, char *buf, int size);
```

#### 4.6.5 基于MSG和MU的事件接口
仅在M4端使用，向A9端传输一个事件
```c
int event(int type, int value);
```

### 4.7 系统监测

系统设置了进程监测功能，业务层模块启动后自行调用看门狗初始化程序，以使能看门狗。在进行的运行过程中，间隔性地调用喂狗函数，否则进程将被重新启动。

#### 4.7.1 看门狗初始化
```c
/**
 * @brief Init watchdog
 * @return int 0 - success
 */
int init_dog(void);
```

#### 4.7.2 看门狗使能

```c
/**
 * @brief Enable watchdog
 * @return int 0 - success
 */
int enable_dog(void);
```



#### 4.7.3 看门狗禁止

```c
/**
 * @brief Disable watchdog
 * @return int 0 - success
 */
int disable_dog(void);
```



#### 4.7.4 喂狗

```c
/**
 * @brief kick watchdog
 * @return int 0 - success
 */
int kick_dog(void);
```



