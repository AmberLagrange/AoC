SRC_DIR   := $(CURDIR)/src
INC_DIR   := $(CURDIR)/include
PCH_DIR   := $(CURDIR)/pch
BUILD_DIR := $(CURDIR)/build
DEP_DIR   := $(CURDIR)/deps
TMP_DIR   := $(CURDIR)/tmp
LIB_DIR   := $(CURDIR)/lib
BIN_DIR   := $(CURDIR)

LIB_NAME   = AolibC.so
START_MAIN = start_main
BIN_NAME  := test

SILENT_FLAG := $(findstring s, $(word 1, $(MAKEFLAGS)))

ifeq ($(SILENT_FLAG), s)
	OUTPUT_REDIRECT = >/dev/null
else
	OUTPUT_REDIRECT =
endif

ifeq ($(CC), clang)
	PCH_EXT    = .pch
	PCH_FLAGS := $(foreach PCH, $(PCHS), -include-pch $(PCH))
else
	PCH_EXT    = .gch
	PCH_FLAGS := $(foreach PCH, $(PCHS), -include $(PCH))
endif

SRCS = $(SRC_DIR)/debug/stack_chk_fail.c \
	   $(SRC_DIR)/fcntl/fcntl.c \
	   $(SRC_DIR)/mman/mman.c \
	   $(SRC_DIR)/stdio/stdio.c \
	   $(SRC_DIR)/stdlib/stdlib.c \
	   $(SRC_DIR)/string/string.c \
	   $(SRC_DIR)/syscall/syscall.c \
	   $(SRC_DIR)/unistd/unistd.c

BUILD_FILE_STRUCT = $(dir $(SRCS:$(SRC_DIR)/%=$(BUILD_DIR)/%))
DEP_FILE_STRUCT   = $(dir $(SRCS:$(SRC_DIR)/%=$(DEP_DIR)/%))

INCS = $(INC_DIR)/fcntl.h $(INC_DIR)/mman.h $(INC_DIR)/stdint.h \
	   $(INC_DIR)/stdio.h $(INC_DIR)/stdlib.h $(INC_DIR)/string.h \
	   $(INC_DIR)/syscall.h $(INC_DIR)/unistd.h

PCHS  = $(INCS:$(INC_DIR)/%=$(PCH_DIR)/%$(PCH_EXT))
OBJS  = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS  = $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)
DEPS += $(DEP_DIR)/$(BIN_NAME).d

all: dirs pchs libs $(BIN_DIR)/$(BIN_NAME)

dirs:
	mkdir -p $(PCH_DIR)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_FILE_STRUCT)
	mkdir -p $(DEP_DIR)
	mkdir -p $(DEP_FILE_STRUCT)
	mkdir -p $(TMP_DIR)
	mkdir -p $(LIB_DIR)
	$(MAKE) -C $(START_MAIN) dirs

pchs: $(PCHS) | dirs
	$(MAKE) -C $(START_MAIN) INC_DIR=$(INC_DIR) $@

libs: $(LIB_DIR)/$(LIB_NAME) | dirs
	$(MAKE) -C $(START_MAIN) LIB_DIR=$(LIB_DIR) $(LIB_DIR)/$(START_MAIN).a

remake:
	$(MAKE) clean
	$(MAKE) all

clean:
	$(RM) -r $(PCH_DIR)
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(DEP_DIR)
	$(RM) -r $(TMP_DIR)
	$(RM) -r $(LIB_DIR)
	$(RM)    $(BIN_DIR)/$(BIN_NAME)
	$(MAKE) -C $(START_MAIN) clean

$(PCH_DIR)/%$(PCH_EXT): $(INC_DIR)/% | dirs
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC -nostdlib -nostdinc -x c-header -MD -MP -MT $@ -MF - -I$(INC_DIR) -c $< -o $@ 1> $(TMP_DIR)/$(*F).$$$$ 2>&1; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $(TMP_DIR)/$(*F).$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $(TMP_DIR)/$(*F).$$$$
	@printf '$(*F)$(PCH_EXT) created.\n' $(OUTPUT_REDIRECT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC -nostdlib -nostdinc -MD -MP -MT $@ -MF - $(PCH_FLAGS) -I$(INC_DIR) -c $< -o $@ 1> $(TMP_DIR)/$(*F).$$$$ 2>&1; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $(TMP_DIR)/$(*F).$$$$ > $(@:$(BUILD_DIR)/%.o=$(DEP_DIR)/%.d); \
	$(RM) $(TMP_DIR)/$(*F).$$$$
	@printf '$(*F).o created.\n' $(OUTPUT_REDIRECT)

$(LIB_DIR)/$(LIB_NAME): $(OBJS) | dirs
	$(CC) $(CFLAGS) $(LDFLAGS) --shared -nostdlib -nostdinc $(OBJS) -o $@
	@printf '$(LIB_NAME) created.\n' $(OUTPUT_REDIRECT)

$(LIB_DIR)/$(START_MAIN).a: | dirs
	$(MAKE) -C $(START_MAIN) LIB_DIR=$(LIB_DIR) $@

$(BIN_DIR)/$(BIN_NAME): $(BIN_DIR)/$(BIN_NAME).c libs | dirs
	set -e; \
	$(RM) $(DEP_DIR)/$(BIN_NAME).d; \
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -MD -MP -MT $@ -MF - -I$(INC_DIR) $< $(LIB_DIR)/$(LIB_NAME) $(LIB_DIR)/$(START_MAIN).a -o $@ 1> $(TMP_DIR)/$(*F).$$$$ 2>&1; \
	sed 's#$@:#$@ $(DEP_DIR)/$(BIN_NAME).d:#' < $(TMP_DIR)/$(*F).$$$$ > $(DEP_DIR)/$(BIN_NAME).d; \
	$(RM) $(TMP_DIR)/$(*F).$$$$
	@printf '$(BIN_NAME) created.\n' $(OUTPUT_REDIRECT)

.PHONY: all dirs pchs libs clean remake

-include $(DEPS)

