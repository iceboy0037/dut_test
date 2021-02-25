TARGET = ./libnotify.so
SVRTEST = ./server.out
CLITEST = ./client.out

CROSS_COMPILE =
DEBUG=-DA9APP
LIBS = -lm -lpthread -lhiredis -lsqlite3


TESTFLAGS  = -O0 $(DEBUG) -Wall -g
TESTLIBS = -L./ -lnotify

exclude_dirs = $(wildcard ./test )

include_dirs = ./
include_dirs += ./inc
include_dirs += ../dbs/inc/
include_dirs += ../common/inc/

test_files = ./test/test.c

######################################################################################################################
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
AR = $(CROSS_COMPILE)ar
LD = $(CROSS_COMPILE)ld

MV = mv -f
RM = rm -rf
LN = ln -sf

AFLAG=-Wall
CFLAG=-Wall -Wno-unused-result
CFLAGS += -O0 $(DEBUG) -Wall -g -fPIC
INC = $(foreach dir, $(include_dirs), -I$(dir))

AFLAGS = -g -Wall
SOFLAGS = -shared -fPIC

all_dirs = $(shell find . -maxdepth 3 -type d)
DIRS = $(filter-out $(exclude_dirs), $(all_dirs))
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.s))
CFILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

HFILES = $(foreach dir, $(include_dirs), $(wildcard $(dir)/*.h))
#$(foreach hfile, $(HFILES), $(info $(hfile)))

OBJS = $(patsubst %.s, %.o, $(FILES))
OBJS += $(patsubst %.c, %.o, $(CFILES))

VPATH =
.c.o:$(HFILES)
	$(CC) -c $(CFLAGS) $(INC) $(DEF) $< -o $@
.s.o:
	@$(CC) -c $(AFLAGS) $(INC) $(DEF) -D_asm $< -o $@

$(TARGET):$(OBJS) $(HFILES) $(test_files)
	@$(CC) $(SOFLAGS) -o $@ $(OBJS) $(LIBS)

	$(info Compiling test program...)
	$(CC) $(TESTFLAGS) $(INC) -DTEST_SERVER $(test_files) -o $(SVRTEST) $(TESTLIBS)
	$(CC) $(TESTFLAGS) $(INC) -DTEST_CLIENT $(test_files) -o $(CLITEST) $(TESTLIBS)

clean:
	@$(RM) *.out
	@$(RM) $(TARGET)
	@$(RM) $(OBJS)
