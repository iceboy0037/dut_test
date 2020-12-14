TARGET = ./m4firm.out
CROSS_COMPILE = 
DEBUG=
DEF = -DSIMULATOR -DM4FIRMWARE

exclude_dirs = $(wildcard ./.git )
exclude_dirs += $(wildcard ./.git/* )
exclude_dirs += $(wildcard ./.git/*/* )
exclude_dirs += $(wildcard ./.git/*/*/* )
exclude_dirs += ../doc

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

LIBS = -lm -lpthread -lhiredis
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
