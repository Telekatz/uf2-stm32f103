/*
 * Copyright (c) 2016, Devan Lai
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice
 * appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED


#define APP_BASE_ADDRESS      0x08004000
#define FLASH_SIZE_OVERRIDE   0x20000
#define FLASH_PAGE_SIZE       2048

#define FILE_INFO 1
#define PRODUCT_NAME          "Clockwork2 CAN"
#define VOLUME_LABEL          "CW2 CAN"
#define BOOTLOADER_SIZE       "16k"


#define HAVE_LED 1
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_PIN  GPIO5

#define LED_OPEN_DRAIN 0

#ifndef HAVE_USB_PULLUP_CONTROL
#define HAVE_USB_PULLUP_CONTROL 0
#endif

#define DOUBLE_TAP


//#define target_gpio_setup()     {\
                                    rcc_periph_clock_enable(RCC_GPIOA);\
                                    rcc_periph_clock_enable(RCC_GPIOB);\
                                    rcc_periph_clock_enable(RCC_GPIOC);\
                                    GPIO_MODER(GPIOC) = 0x4000000;\
                                    GPIO_MODER(GPIOA) = 0x29000000;\
                                    GPIO_OSPEEDR(GPIOA) = 0xc000000;\
                                  }


#endif
