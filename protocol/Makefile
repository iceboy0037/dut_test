LIB60870_HOME=../thirdparty/lib60870

PROJECT_BINARY_NAME = ./cs104.out
#PROJECT_SOURCES = ./src/cs104.c

include_dirs = -I./
include_dirs += -I./inc
include_dirs += -I./src
include_dirs += -I../common
include_dirs += -I../common/inc

include_dirs += -I./dbs
include_dirs += -I./dbs/inc
include_dirs += -I./dbs/src

all_dirs = $(shell find . -maxdepth 4 -type d)
link_dir = $(shell find . -maxdepth 4 -type l)
all_dirs += $(foreach n, $(link_dir), $(shell find $(n)/ -maxdepth 4 -type d))
DIRS = $(filter-out $(exclude_dirs), $(all_dirs))
FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.s))
PROJECT_SOURCES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
OBJS += $(patsubst %.c, %.o, $(CFILES))

include $(LIB60870_HOME)/make/target_system.mk
include $(LIB60870_HOME)/make/stack_includes.mk

LDLIBS += -lhiredis -lsqlite3
CFLAGS += -g $(include_dirs) -Wall
DEF = -DSIMULATOR -DM4FIRMWARE

all:	$(PROJECT_BINARY_NAME)
include $(LIB60870_HOME)/make/common_targets.mk

$(PROJECT_BINARY_NAME):	$(PROJECT_SOURCES) $(LIB_NAME)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(DEF) -o $(PROJECT_BINARY_NAME) $(PROJECT_SOURCES) $(INCLUDES) $(LIB_NAME) $(LDLIBS)

clean:
	@rm -f $(PROJECT_BINARY_NAME)