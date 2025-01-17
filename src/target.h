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

#ifndef TARGET_H_INCLUDED
#define TARGET_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/stm32/flash.h>

extern void target_clock_setup(void);
extern void target_gpio_setup(void);
extern const usbd_driver* target_usb_init(void);
extern bool target_get_force_bootloader(void);
extern bool target_get_force_app(void);
extern void target_get_serial_number(char* dest, size_t max_chars);
extern size_t target_get_max_firmware_size(void);
extern void target_log(const char* str);
//extern void target_relocate_vector_table(void);
extern void target_manifest_app(void);
extern void target_flash_unlock(void);
extern void target_flash_lock(void);
extern bool target_flash_program_array(uint16_t* dest, const uint16_t* data, size_t half_word_count);
extern void target_set_led(int on);

extern void target_pre_main(void);

#define target_relocate_vector_table()    SCB_VTOR = APP_BASE_ADDRESS & 0xFFFF;
#define target_flash_lock()               flash_lock();

#endif
