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

ifeq ($(TARGET),STM32F103)
	CPU              	:= stm32f103
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/generic
	LDSCRIPT			:= ./$(CPU)/stm32f103x8.ld
	ARCH				= STM32F1
	
endif
ifeq ($(TARGET),STM32F072)
	CPU              	:= stm32f072
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/generic
	LDSCRIPT			:= ./$(CPU)/stm32f072x8.ld
	ARCH				= STM32F0
	
endif
ifeq ($(TARGET),BLUEPILL)
	CPU              	= stm32f103
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/bluepill
	LDSCRIPT			:= ./$(CPU)/stm32f103x8.ld
	ARCH				= STM32F1
	DEFS				+= -DHAVE_LED=1 -DLED_GPIO_PORT=GPIOC -DLED_GPIO_PIN=GPIO13 -DLED_OPEN_DRAIN=1 -DUSES_GPIOC=1
endif
ifeq ($(TARGET),BLUEPILL_072)
	CPU              	:= stm32f072
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/bluepill
	LDSCRIPT			:= ./$(CPU)/stm32f072x8.ld
	ARCH				= STM32F0
endif
ifeq ($(TARGET),MAPLEMINI)
	CPU              	:= stm32f103
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/maplemini
	LDSCRIPT			:= ./$(CPU)/stm32f103x8.ld
	ARCH				= STM32F1
endif
ifeq ($(TARGET),ERCF-CAN)
	CPU              	:= stm32f103
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/ERCF-CAN
	LDSCRIPT			:= ./$(CPU)/stm32f103x8_16k.ld
	ARCH				= STM32F1
endif
ifeq ($(TARGET),Clockwork2-CAN_103)
	CPU              	:= stm32f103
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/Clockwork2-CAN
	LDSCRIPT			:= ./$(CPU)/stm32f103x8_16k.ld
	ARCH				= STM32F1
endif
ifeq ($(TARGET),Clockwork2-CAN_072)
	CPU              	:= stm32f072
	TARGET_COMMON_DIR	:= ./$(CPU)
	TARGET_SPEC_DIR		:= ./$(CPU)/Clockwork2-CAN
	LDSCRIPT			:= ./$(CPU)/stm32f072x8.ld
	ARCH				= STM32F0
endif


ifndef ARCH
$(error Unknown target $(TARGET))
endif
