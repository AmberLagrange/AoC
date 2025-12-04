AOLIBC_PATH := ../AolibC
LIB_PATH    := $(AOLIBC_PATH)/lib
INC_PATH    := $(AOLIBC_PATH)/include

LIBS := $(LIB_PATH)/AolibC.so $(LIB_PATH)/start_main.a

all: part_1 part_2

part_1: part_1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_PATH) part_1.c helper.c $(LIBS) -o part_1

part_2: part_2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_PATH) part_2.c helper.c $(LIBS) -o part_2

clean:
	$(RM) part_1 part_2

remake: clean all

.PHONY: all clean remake
