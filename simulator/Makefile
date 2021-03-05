TARGET = ./dtush
#CROSS_COMPILE =arm-fsl-linux-gnueabi-
CROSS_COMPILE =
DEBUG=
LIBS = -lm -lpthread -lhiredis -lsqlite3
DEF = -DSIMULATOR


exclude_dirs = $(wildcard ./.git )
exclude_dirs += $(wildcard ./.git/* )
exclude_dirs += $(wildcard ./.git/*/* )
exclude_dirs += $(wildcard ./.git/*/*/* )
exclude_dirs += ../doc

include_dirs = -I./
include_dirs += -I./inc
include_dirs += -I../common
include_dirs += -I../common/inc
include_dirs += -I../thirdparty/sqlite/build/include
include_dirs += -I../thirdparty/hiredis/build/include

include_dirs += -I./dbs
include_dirs += -I./dbs/inc

include_dirs += -I./devs
include_dirs += -I./devs/inc

export LD_LIBRARY_PATH=/usr/local/lib/

######################################################################################################################
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld

MV = mv -f
RM = rm -rf
LN = ln -sf

CFLAG=-Wall -Wno-unused-result
AFLAG=-Wall
CFLAGS = -O0 $(DEBUG) -Wall -g $(include_dirs) -std=c99

AFLAGS = -g -Wall
SOFLAGS = -L../thirdparty/hiredis

all_dirs = $(shell find . -maxdepth 4 -type d)
link_dir = $(shell find . -maxdepth 4 -type l)
#$(warning "the value of LINK is: $(link)")
all_dirs += $(foreach n, $(link_dir), $(shell find $(n)/ -maxdepth 4 -type d))
#$(warning "the value of LOCAL_PATH is: $(all_dirs)")
#all_dirs += $(foreach n, $(link_dir), $(n))

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
