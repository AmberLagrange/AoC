AOLIBC_PATH := ../AolibC
LIB_PATH    := $(AOLIBC_PATH)/libs
INC_PATH    := $(AOLIBC_PATH)/include

LIBS := $(LIB_PATH)/AolibC.so $(LIB_PATH)/start_main.a

part_1: part_1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_PATH) part_1.c helper.c $(LIBS) -o part_1

part_2: part_2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_PATH) part_2.c helper.c $(LIBS) -o part_2

all: part_1 part_2

clean:
	rm -f part_1 part_2

.PHONY: all clean
