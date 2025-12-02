CC ?= gcc

SRC_DIR   ?= ./src
INC_DIR   ?= ./include
BUILD_DIR ?= ./build
LIB_DIR   ?= ./libs

SRCS := $(SRC_DIR)/exit.c $(SRC_DIR)/fcntl.c $(SRC_DIR)/stack_chk_fail.c $(SRC_DIR)/syscall.c $(SRC_DIR)/unistd.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LIB_NAME   := AolibC.so
START_MAIN := start_main
TEST_BIN   := main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -nostdlib -nostdinc -I$(INC_DIR) -c $< -o $@

$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -nostdlib -nostdinc $(OBJS) -o $@

$(LIB_DIR)/$(START_MAIN).a:
	$(MAKE) -C $(START_MAIN) ../$@

$(TEST_BIN): $(TEST_BIN).c $(LIB_DIR)/$(LIB_NAME) $(LIB_DIR)/$(START_MAIN).a
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_DIR) $^ -o $@

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	$(MAKE) -C $(START_MAIN) dirs

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIRZ)
	rm -f $(TEST_BIN)
	$(MAKE) -C $(START_MAIN) clean

.PHONY: dirs clean

