TARGET = ./simulator.out
CROSS_COMPILE = 
DEBUG=
LIBS = -lm -lpthread -lhiredis

exclude_dirs = $(wildcard ./.git )
exclude_dirs += $(wildcard ./.git/* )
exclude_dirs += $(wildcard ./.git/*/* )
exclude_dirs += ../doc

include_dirs = -I./
include_dirs += -I./inc
include_dirs += -I../common
include_dirs += -I../common/inc

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
CFLAGS = -O2 $(DEBUG) -Wall -g $(include_dirs)

AFLAGS = -g -Wall
SOFLAGS = 

all_dirs = $(shell find . -maxdepth 3 -type d)
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
