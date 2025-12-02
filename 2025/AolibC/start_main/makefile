CC ?= gcc

SRC_DIR   ?= ./src
INC_DIR   ?= ./include
BUILD_DIR ?= ./build
LIB_DIR   ?= ../libs

SRCS := $(SRC_DIR)/start.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

START_MAIN := start_main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -static -nostdlib -nostdinc -I$(INC_DIR) -c $< -o $@

$(LIB_DIR)/$(START_MAIN).a : $(OBJS)
	ar rcs $@ $(OBJS)

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(LIB_DIR)/$(START_MAIN).a

.PHONY: dirs clean
