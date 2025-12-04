SRC_DIR   ?= $(CURDIR)/src
INC_DIR   ?= $(CURDIR)/../include
PCH_DIR   ?= $(CURDIR)/pch
BUILD_DIR ?= $(CURDIR)/build
DEP_DIR   ?= $(CURDIR)/deps
TMP_DIR   ?= $(CURDIR)/tmp
LIB_DIR   ?= $(CURDIR)/../lib

START_MAIN = start_main
TMP_FILE   = $(TMP_DIR)/$(*F).$$$$

SILENT_FLAG = $(findstring s, $(word 1, $(MAKEFLAGS)))

ifeq ($(SILENT_FLAG), s)
	OUTPUT_REDIRECT = >/dev/null
else
	OUTPUT_REDIRECT =
endif

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
	mkdir -p $(TMP_DIR)
	mkdir -p $(LIB_DIR)

pchs: $(PCHS)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(PCH_DIR)
	$(RM) -r $(DEP_DIR)
	$(RM) -r $(TMP_DIR)
	$(RM)    $(LIB_DIR)/$(START_MAIN).a

remake: clean all

$(PCH_DIR)/%$(PCH_EXT): $(INC_DIR)/%
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC $(PCH_COMP_FLAGS) -nostdlib -nostdinc -x c-header -MD -MP -MT $@ -MF - -I$(INC_DIR) -c $< -o $@ > $(TMP_FILE); \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d#' < $(TMP_FILE) > $(DEP_DIR)/$(*F).d; \
	$(RM) $(TMP_FILE)
	@printf '$(*F)$(PCH_EXT) Created.\n' $(OUTPUT_REDIRECT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC --static -nostdlib -nostdinc -MD -MP -MT $@ -MF - $(PCH_FLAGS) -I$(INC_DIR) -c $< -o $@ > $(TMP_FILE); \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $(TMP_FILE) > $(DEP_DIR)/$(*F).d; \
	$(RM) $(TMP_FILE)
	@printf '$(*F).o created.\n' $(OUTPUT_REDIRECT)

$(LIB_DIR)/$(START_MAIN).a: $(OBJS)
	$(AR) rcs $@ $(OBJS)
	@printf '$(START_MAIN).a created.\n' $(OUTPUT_REDIRECT)

.PHONY: all dirs pchs clean remake

-include $(DEPS)

