AOLIBC_PATH := $(CURDIR)/../AolibC
LIB_PATH    := $(AOLIBC_PATH)/lib
INC_PATH    := $(AOLIBC_PATH)/include
COMMON_PATH := $(CURDIR)/../common

LIBS := $(LIB_PATH)/AolibC.so $(LIB_PATH)/start_main.a

COMMON_SRC := $(COMMON_PATH)/common.c

all: part_1 part_2

part_1: part_1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_PATH) -I$(COMMON_PATH) part_1.c $(COMMON_SRC) $(LIBS) -o part_1

part_2: part_2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_PATH) -I$(COMMON_PATH) part_2.c $(COMMON_SRC) $(LIBS) -o part_2

run: part_1 part_2
	./part_1 input
	./part_2 input

clean:
	$(RM) part_1 part_2

remake: clean all

.PHONY: all run clean remake
