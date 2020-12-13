# DTU软件编译开发环境

- 应用软件的开发可基于ubuntu平台开发与模拟运行，在ubuntu环境下需要准备些运行环境。

## 一、Redis安装与配置

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

在文件中，找到supervised指令。 该指令允许您声明一个init系统来管理Redis作为服务，从而为您提供对其操作的更多控制。 受supervised指令默认设置为no 。 由于您正在运行使用systemd init系统的Ubuntu，请将其更改为systemd ：

```
# If you run Redis from upstart or systemd, Redis can interact with your
# supervision tree. Options:
#   supervised no      - no supervision interaction
#   supervised upstart - signal upstart by putting Redis into SIGSTOP mode
#   supervised systemd - signal systemd by writing READY=1 to $NOTIFY_SOCKET
#   supervised auto    - detect upstart or systemd method based on
#                        UPSTART_JOB or NOTIFY_SOCKET environment variables
# Note: these supervision methods only signal "process is ready."
#       They do not enable continuous liveness pings back to your supervisor.
supervised systemd
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

使用

```c
#include <hiredis/hiredis.h>
```

