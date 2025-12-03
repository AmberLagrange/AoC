SRC_DIR   ?= $(PWD)/src
INC_DIR   ?= $(PWD)/../include
PCH_DIR   ?= $(PWD)/pch
BUILD_DIR ?= $(PWD)/build
DEP_DIR   ?= $(PWD)/deps
LIB_DIR   ?= $(PWD)/../lib

SRCS := $(SRC_DIR)/start.c
INCS := $(INC_DIR)/stdlib.h

PCHS := $(INCS:$(INC_DIR)/%=$(PCH_DIR)/%.pch)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

START_MAIN := start_main

$(PCH_DIR)/%.pch: $(INC_DIR)/%
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC -Xclang -static-define -nostdlib -nostdinc -x c-header -MD -MP -MT $@ -MF - -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC --static -nostdlib -nostdinc -MD -MP -MT $@ -MF - $(foreach PCH, $(PCHS), -include-pch $(PCH)) -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$

$(LIB_DIR)/$(START_MAIN).a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(PCH_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(DEP_DIR)

pchs: $(PCHS)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(PCH_DIR)
	$(RM) -r $(DEP_DIR)
	$(RM)    $(LIB_DIR)/$(START_MAIN).a

all: $(LIB_DIR)/$(START_MAIN).a

remake: clean dirs all

.PHONY: dirs clean pchs all remake

-include $(DEPS)
