TARGET = demo_gpio

RISCV_PATH = ../../riscv64-unknown-elf-gcc
CC = $(RISCV_PATH)/bin/riscv64-unknown-elf-gcc
AR = $(RISCV_PATH)/bin/riscv64-unknown-elf-ar
RISCV_ARCH=rv32imac 
RISCV_ABI=ilp32
BOARD=freedom-e300-hifive1
LINK_TARGET=flash

BSP_BASE = ../freedom-bsp

C_SRCS += src/demo_gpio.c
C_SRCS += $(BSP_BASE)/drivers/plic/plic_driver.c

include $(BSP_BASE)/env/common.mk

CFLAGS += -O2 -fno-builtin-printf -DUSE_PLIC -DUSE_M_TIME


