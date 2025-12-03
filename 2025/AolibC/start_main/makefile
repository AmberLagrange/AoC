SRC_DIR   ?= $(PWD)/src
INC_DIR   ?= $(PWD)/../include
BUILD_DIR ?= $(PWD)/build
DEP_DIR   ?= $(PWD)/deps
LIB_DIR   ?= $(PWD)/../lib

SRCS := $(SRC_DIR)/start.c
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

START_MAIN := start_main

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -static -nostdlib -nostdinc -MD -MP -MT $@ -MF - -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$

$(LIB_DIR)/$(START_MAIN).a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(DEP_DIR)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(DEP_DIR)
	$(RM)    $(LIB_DIR)/$(START_MAIN).a

all: $(LIB_DIR)/$(START_MAIN).a

remake: clean dirs all

.PHONY: dirs clean all remake

-include $(DEPS)
