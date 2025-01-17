## Copyright (c) 2016, Devan Lai
##
## Permission to use, copy, modify, and/or distribute this software
## for any purpose with or without fee is hereby granted, provided
## that the above copyright notice and this permission notice
## appear in all copies.
##
## THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
## WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
## WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
## AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
## CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
## LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
## NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
## CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

-include local.mk

BINARY = MSCboot
OPENCM3_DIR = ../libopencm3

MSC_VERSION_BASE = $(shell git describe --dirty --always --tags)
VER_FLAGS = -DMSC_VERSION='"$(MSC_VERSION_BASE)"'

TARGET ?= BLUEPILL
include targets.mk

SRCS := $(wildcard *.c)
SRCS += $(wildcard $(TARGET_COMMON_DIR)/*.c)
SRCS += $(wildcard $(TARGET_SPEC_DIR)/*.c)

BUILD = build/$(TARGET)

OBJS += $(addprefix $(BUILD)/,$(SRCS:.c=.o))
DEPS  = $(addprefix $(BUILD)/,$(SRCS:.c=.d))

ELF = $(BUILD)/$(BINARY).elf

all: $(BUILD) $(BUILD)/$(BINARY).bin size
	
$(BUILD):
	mkdir -p $(BUILD)/$(CPU)

clean::
	rm -rf build/

include rules.mk

size: $(OBJS) $(ELF)
	@$(PREFIX)-size $(ELF)

.PHONY += debug size erase

OBJS := $(sort $(OBJS))

# Add the base directory to the header search path
CPPFLAGS += -I.

# Add target config directory to the header search path
CPPFLAGS += -I$(TARGET_COMMON_DIR)/
CPPFLAGS += -I$(TARGET_SPEC_DIR)/


