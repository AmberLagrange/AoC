SRC_DIR   = $(PWD)/src
INC_DIR   = $(PWD)/include
BUILD_DIR = $(PWD)/build
DEP_DIR   = $(PWD)/deps
LIB_DIR   = $(PWD)/libs

SRCS := $(SRC_DIR)/fcntl.c $(SRC_DIR)/stack_chk_fail.c $(SRC_DIR)/stdio.c \
		$(SRC_DIR)/stdlib.c $(SRC_DIR)/string.c $(SRC_DIR)/syscall.c \
		$(SRC_DIR)/unistd.c

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

LIB_NAME   := AolibC.so
START_MAIN := start_main
TEST_BIN   := test

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(DEP_DIR)
	mkdir -p $(LIB_DIR)
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) dirs

clean:
	$(RM) -rf $(BUILD_DIR)
	$(RM) -rf $(DEP_DIR)
	$(RM) -rf $(LIB_DIR)
	$(RM)  -f $(TEST_BIN)
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) clean

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -fPIC $(CFLAGS) -nostdlib -nostdinc -MD -MP -MT $@ -MF $(DEP_DIR)/$(*F).d -I$(INC_DIR) -c $< -o $@

$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -nostdlib -nostdinc $(OBJS) -o $@

$(LIB_DIR)/$(START_MAIN).a:
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) LIB_DIR=$(LIB_DIR) $@

libs: $(LIB_DIR)/$(LIB_NAME) $(LIB_DIR)/$(START_MAIN).a
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) LIB_DIR=$(LIB_DIR) $(LIB_DIR)/$(START_MAIN).a

$(TEST_BIN): $(TEST_BIN).c libs
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -I$(INC_DIR) $< $(LIB_DIR)/$(LIB_NAME) $(LIB_DIR)/$(START_MAIN).a -o $@

libs: $(LIB_DIR)/$(LIB_NAME) $(LIB_DIR)/$(START_MAIN).a

all: libs $(TEST_BIN)

remake: clean dirs all

.PHONY: dirs clean all remake

-include $(DEPS)

