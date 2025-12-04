SRC_DIR   = $(PWD)/src
INC_DIR   = $(PWD)/include
PCH_DIR   = $(PWD)/pch
BUILD_DIR = $(PWD)/build
DEP_DIR   = $(PWD)/deps
LIB_DIR   = $(PWD)/lib

LIB_NAME   = AolibC.so
START_MAIN = start_main
TEST_BIN   = test

ifeq ($(CC), clang)
	PCH_EXT        := .pch
	PCH_FLAGS := $(foreach PCH, $(PCHS), -include-pch $(PCH))
else
	PCH_EXT        := .gch
	PCH_FLAGS := $(foreach PCH, $(PCHS), -include $(PCH))
endif

SRCS =  $(SRC_DIR)/fcntl.c $(SRC_DIR)/stack_chk_fail.c $(SRC_DIR)/stdio.c \
		$(SRC_DIR)/stdlib.c $(SRC_DIR)/string.c $(SRC_DIR)/syscall.c \
		$(SRC_DIR)/unistd.c

INCS = $(INC_DIR)/fcntl.h $(INC_DIR)/stdio.h $(INC_DIR)/stdlib.h \
	   $(INC_DIR)/string.h $(INC_DIR)/syscall.h $(INC_DIR)/unistd.h

PCHS = $(INCS:$(INC_DIR)/%=$(PCH_DIR)/%$(PCH_EXT))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRCS:$(SRC_DIR)/%.c=$(DEP_DIR)/%.d)

DEPS += $(DEP_DIR)/$(TEST_BIN).d

all: dirs pchs libs $(TEST_BIN)

dirs:
	mkdir -p $(PCH_DIR)
	mkdir -p $(BUILD_DIR)
	mkdir -p $(DEP_DIR)
	mkdir -p $(LIB_DIR)
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) dirs

pchs: $(PCHS)
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) INC_DIR=$(INC_DIR) $@

libs: $(LIB_DIR)/$(LIB_NAME)
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) LIB_DIR=$(LIB_DIR) $(LIB_DIR)/$(START_MAIN).a

remake: clean all

clean:
	$(RM) -r $(PCH_DIR)
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(DEP_DIR)
	$(RM) -r $(LIB_DIR)
	$(RM)    $(TEST_BIN)
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) clean

$(PCH_DIR)/%$(PCH_EXT): $(INC_DIR)/%
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC -nostdlib -nostdinc -x c-header -MD -MP -MT $@ -MF - -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$
	@printf '$(*F)$(PCH_EXT) created.\n'

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	set -e; \
	$(RM) $(DEP_DIR)/$(*F).d; \
	$(CC) $(CFLAGS) -fPIC -nostdlib -nostdinc -MD -MP -MT $@ -MF - $(PCH_FLAGS) -I$(INC_DIR) -c $< -o $@ > $@.$$$$; \
	sed -e 's#$@:#$@ $(DEP_DIR)/$(*F).d:#' < $@.$$$$ > $(DEP_DIR)/$(*F).d; \
	$(RM) $@.$$$$
	@printf '$(*F).o created.\n'

$(LIB_DIR)/$(LIB_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) --shared -nostdlib -nostdinc $(OBJS) -o $@
	@printf '$(LIB_NAME) created.\n'

$(LIB_DIR)/$(START_MAIN).a:
	$(MAKE) -C $(START_MAIN) PWD=$(PWD)/$(START_MAIN) LIB_DIR=$(LIB_DIR) $@

$(TEST_BIN): $(TEST_BIN).c
	set -e; \
	$(RM) $(DEP_DIR)/$@.d; \
	$(CC) $(CFLAGS) $(LDFLAGS) -nostdlib -nostdinc -MD -MP -MT $@ -MF - -I$(INC_DIR) $(PWD)/$< $(LIB_DIR)/$(LIB_NAME) $(LIB_DIR)/$(START_MAIN).a -o $(PWD)/$@ > $@.$$$$; \
	sed 's#$@:#$@ $(DEP_DIR)/$@.d:#' < $@.$$$$ > $(DEP_DIR)/$@.d; \
	$(RM) $@.$$$$
	@printf '$(TEST_BIN) created.\n'

.PHONY: all dirs pchs libs clean remake

-include $(DEPS)

