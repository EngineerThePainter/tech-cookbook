OPENCM3_DIR = <path to opencm3 root>
OPENCM3_LIB = libopencm3_stm32f0.a
OPENCM3_DEFS = -DSTM32F0
ARCH_FLAGS = -mthumb -mcpu=cortex-m0
PROJECT = stm32f0-blink
CFILES = blink.c
# LDSCRIPT = ./stm32f030r8t6.ld
BUILD_DIR = bin
DEVICE = STM32F030R8T6

VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))


include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/tests/rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk