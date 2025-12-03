SRC_DIR   ?= $(PWD)/src
INC_DIR   ?= $(PWD)/../include
BUILD_DIR ?= $(PWD)/build
DEP_DIR   ?= $(PWD)/deps
LIB_DIR   ?= $(PWD)/../libs

SRCS := $(SRC_DIR)/start.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

START_MAIN := start_main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -static -nostdlib -nostdinc -MD -MP -MT $@ -MF $(DEP_DIR)/$(*F).d -I$(INC_DIR) -c $< -o $@

$(LIB_DIR)/$(START_MAIN).a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(DEP_DIR)

clean:
	$(RM) -rf $(BUILD_DIR)
	$(RM) -rf $(DEP_DIR)
	$(RM)  -f $(LIB_DIR)/$(START_MAIN).a

all: $(LIB_DIR)/$(START_MAIN).a

remake: clean dirs all

.PHONY: dirs clean all remake

-include $(DEPS)
