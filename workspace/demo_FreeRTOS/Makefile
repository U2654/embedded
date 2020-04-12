TARGET = demo_FreeRTOS

RISCV_PATH = ../../riscv64-unknown-elf-gcc
CC = $(RISCV_PATH)/bin/riscv64-unknown-elf-gcc
AR = $(RISCV_PATH)/bin/riscv64-unknown-elf-ar
RISCV_ARCH=rv32imac 
RISCV_ABI=ilp32
BOARD=freedom-e300-hifive1
LINK_TARGET=flashfr

BSP_BASE = ../freedom-bsp

#FreeRTOS >
FREE_RTOS = ../FreeRTOS
INCLUDES += -I$(FREE_RTOS)/Source/include
C_SRCS += $(FREE_RTOS)/Source/croutine.c
C_SRCS += $(FREE_RTOS)/Source/event_groups.c
C_SRCS += $(FREE_RTOS)/Source/list.c
C_SRCS += $(FREE_RTOS)/Source/queue.c
C_SRCS += $(FREE_RTOS)/Source/stream_buffer.c
C_SRCS += $(FREE_RTOS)/Source/tasks.c
C_SRCS += $(FREE_RTOS)/Source/timers.c
INCLUDES += -I$(FREE_RTOS)/Source/portable/GCC/RISC-V
INCLUDES += -I$(FREE_RTOS)/Source/portable/GCC/RISC-V/chip_specific_extensions/RV32I_CLINT_no_extensions
C_SRCS += $(FREE_RTOS)/Source/portable/GCC/RISC-V/port.c
C_SRCS += $(FREE_RTOS)/Source/portable/MemMang/heap_4.c
ASM_SRCS += $(FREE_RTOS)/Source/portable/GCC/RISC-V/portASM.S
#FreeRTOS <

INCLUDES += -I./common/include
C_SRCS += common/blocktim.c
C_SRCS += common/dynamic.c
C_SRCS += common/recmutex.c
C_SRCS += common/TaskNotify.c
C_SRCS += common/TimerDemo.c
C_SRCS += common/EventGroupsDemo.c
INCLUDES += -I./
C_SRCS += main.c
C_SRCS += blinky_demo/main_blinky.c
C_SRCS += full_demo/main_full.c
ASM_SRCS += full_demo/RegTest.S


include $(BSP_BASE)/env/common.mk

CFLAGS += -O2 -DportasmHANDLE_INTERRUPT=handle_trap


