SRC_DIR   ?= $(PWD)/src
INC_DIR   ?= $(PWD)/../include
PCH_DIR   ?= $(PWD)/pch
BUILD_DIR ?= $(PWD)/build
DEP_DIR   ?= $(PWD)/deps
LIB_DIR   ?= $(PWD)/../lib

START_MAIN := start_main

ifeq ($(CC), clang)
	PCH_EXT        := .pch
	PCH_COMP_FLAGS := -Xclang -static-define
	PCH_INC_FLAGS  := $(foreach PCH, $(PCHS), -include-pch $(PCH))
else
	PCH_EXT        := .gch
	PCH_COMP_FLAGS :=
	PCH_INC_FLAGS  := $(foreach PCH, $(PCHS), -include $(PCH))
endif

INCS := $(INC_DIR)/stdlib.h

SRCS := $(SRC_DIR)/start.c

PCHS := $(INCS:$(INC_DIR)/%=$(PCH_DIR)/%$(PCH_EXT))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

all: dirs pchs $(LIB_DIR)/$(START_MAIN).a

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(PCH_DIR)
	mkdir -p $(DEP_DIR)
	mkdir -p $(LIB_DIR)

pchs: $(PCHS)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(PCH_DIR)
	$(RM) -r $(DEP_DIR)
	$(RM)    $(LIB_DIR)/$(START_MAIN).a

remake: clean all

$(PCH_DIR)/%$(PCH_EXT): $(INC_DIR)/%
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC $(PCH_COMP_FLAGS) -nostdlib -nostdinc -x c-header -MD -MP -MT $@ -MF - -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$
	@printf '$(*F)$(PCH_EXT) Created.\n'

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC --static -nostdlib -nostdinc -MD -MP -MT $@ -MF - $(PCH_FLAGS) -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$
	@printf '$(*F).o created.\n'

$(LIB_DIR)/$(START_MAIN).a: $(OBJS)
	$(AR) rcs $@ $(OBJS)
	@printf '$(START_MAIN).a created.\n'

.PHONY: all dirs pchs clean remake

-include $(DEPS)

