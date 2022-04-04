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

#define APP_BASE_ADDRESS 0x08002000
#define FLASH_SIZE_OVERRIDE 0x20000
#define FLASH_PAGE_SIZE  1024

#define HAVE_LED 1
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_PIN  GPIO12

#define LED_OPEN_DRAIN 0

#define UF2_FAMILY 0x5ee21072

#ifndef HAVE_USB_PULLUP_CONTROL
#define HAVE_USB_PULLUP_CONTROL 0
#endif

#define DOUBLE_TAP

#define target_gpio_setup()     {\
                                  rcc_periph_clock_enable(RCC_GPIOA);\
                                  rcc_periph_clock_enable(RCC_GPIOB);\
                                   GPIO_CRH(GPIOB) = 0x44414444;\
                                  }

#endif
