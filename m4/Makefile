TARGET = ./m4firm.out
CROSS_COMPILE =
DEBUG=
DEF = -DSIMULATOR -DM4FIRMWARE

exclude_dirs = $(wildcard ./.git )
exclude_dirs += $(wildcard ./.git/* )
exclude_dirs += $(wildcard ./.git/*/* )
exclude_dirs += $(wildcard ./.git/*/*/* )
exclude_dirs += ../doc
exclude_dirs += ./build
exclude_dirs += ./board
exclude_dirs += ./board/inc
exclude_dirs += ./board/src
exclude_dirs += ./platform
exclude_dirs += ./platform/drivers
exclude_dirs += ./platform/drivers/inc
exclude_dirs += ./platform/drivers/src
exclude_dirs += ./platform/CMSIS
exclude_dirs += ./platform/CMSIS/Include
exclude_dirs += ./platform/CMSIS/Lib
exclude_dirs += ./platform/devices
exclude_dirs += ./platform/devices/MCIMX6X
exclude_dirs += ./platform/devices/MCIMX6X/startup
exclude_dirs += ./platform/devices/MCIMX6X/include
exclude_dirs += ./platform/utilities
exclude_dirs += ./platform/utilities/inc
exclude_dirs += ./platform/utilities/src

include_dirs = -I./
include_dirs += -I./inc
include_dirs += -I./src
include_dirs += -I../common
include_dirs += -I../common/inc

include_dirs += -I./dbs
include_dirs += -I./dbs/inc
include_dirs += -I./dbs/src

include_dirs += -I./devs
include_dirs += -I./devs/inc
include_dirs += -I./devs/src

######################################################################################################################
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld

MV = mv -f
RM = rm -rf
LN = ln -sf

LIBS = -lm -lpthread -lhiredis -lsqlite3
CFLAG=-Wall -Wno-unused-result
AFLAG=-Wall
CFLAGS = -O0 $(DEBUG) -Wall -g $(include_dirs)

AFLAGS = -g -Wall
SOFLAGS =

all_dirs = $(shell find . -maxdepth 4 -type d)
link_dir = $(shell find . -maxdepth 4 -type l)
all_dirs += $(foreach n, $(link_dir), $(shell find $(n)/ -maxdepth 4 -type d))

DIRS = $(filter-out $(exclude_dirs), $(all_dirs))
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.s))
CFILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

OBJS = $(patsubst %.s, %.o, $(FILES))
OBJS += $(patsubst %.c, %.o, $(CFILES))

VPATH =
.c.o:
	@$(CC) -c $(CFLAGS) $(DEF) $< -o $@
.s.o:
	@$(CC) -c $(AFLAGS) $(DEF) -D_asm $< -o $@

$(TARGET):$(OBJS)
	@$(CC) $(SOFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@$(RM) $(TARGET)
	@$(RM) $(OBJS)
