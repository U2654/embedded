TARGET = demo_gprof

RISCV_PATH = ../../riscv64-unknown-elf-gcc
CC = $(RISCV_PATH)/bin/riscv64-unknown-elf-gcc
AR = $(RISCV_PATH)/bin/riscv64-unknown-elf-ar
RISCV_ARCH=rv32ima
RISCV_ABI=ilp32
BOARD=freedom-e300-arty
LINK_TARGET=flash

BSP_BASE = ../freedom-bsp

#include ./gprof.mk

C_PSRCS += src/demo_gprof.c
#C_SRCS += $(BSP_BASE)/drivers/plic/plic_driver.c

CFLAGS += -g -fno-builtin-printf 

.PHONY: all
all: $(TARGET)

ENV_DIR = $(BSP_BASE)/env
PLATFORM_DIR = $(ENV_DIR)/$(BOARD)

C_SRCS += lib/intctl.c \
	lib/sbrk.c \
	lib/semihost.c \
	lib/stat.c \
	lib/sys_exit.c \
	lib/gprof/gmon.c \
	lib/gprof/profil.c \
	board-startup/init.c

ASM_SRCS += lib/gprof/profiler.S \
	board-startup/start.S \
	board-startup/entry.S

#ASM_SRCS += $(ENV_DIR)/start.S
#ASM_SRCS += $(ENV_DIR)/entry.S
#C_SRCS += $(PLATFORM_DIR)/init.c

LINKER_SCRIPT := $(PLATFORM_DIR)/$(LINK_TARGET).lds

INCLUDES += -I./include
INCLUDES += -I./include/gprof
INCLUDES += -I$(BSP_BASE)/include
INCLUDES += -I$(BSP_BASE)/drivers/
INCLUDES += -I$(ENV_DIR)
INCLUDES += -I$(PLATFORM_DIR)

TOOL_DIR = $(BSP_BASE)/../toolchain/bin

#LDFLAGS += -T $(LINKER_SCRIPT) -nostartfiles
LDFLAGS += -T ./flash.lds -nostartfiles
LDFLAGS += -L$(ENV_DIR) #--specs=nano.specs

ASM_OBJS := $(ASM_SRCS:.S=.o)
C_OBJS := $(C_SRCS:.c=.o)
C_POBJS := $(C_PSRCS:.c=.o)

LINK_OBJS += $(ASM_OBJS) $(C_OBJS)  $(C_POBJS)
LINK_DEPS += $(LINKER_SCRIPT)

CLEAN_OBJS += $(TARGET) $(LINK_OBJS)

CFLAGS += -g
CFLAGS += -march=$(RISCV_ARCH)
CFLAGS += -mabi=$(RISCV_ABI)
CFLAGS += -mcmodel=medany

$(TARGET): $(LINK_OBJS) $(LINK_DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LINK_OBJS) -o $@ $(LDFLAGS)

$(ASM_OBJS): %.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(C_OBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -include sys/cdefs.h -c -o $@ $<

$(C_POBJS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -pg $(INCLUDES) -include sys/cdefs.h -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(CLEAN_OBJS)
