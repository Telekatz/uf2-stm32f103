# MSC bootloader for STM32F072 and STM32F103

This project was initially forked off https://github.com/mmoskal/uf2-stm32f103 though the UF2 functionality has been removed
and replaced with the ability to load .bin firmware files.

## Build instructions
The default target is a generic STM32F103 dev board with an LED on PC13, commonly referred to as a "bluepill" board.

To build other targets, you can override the
`TARGET` variable when invoking `make`.

    make clean
    make TARGET=MAPLEMINI

### Targets

| Target Name | Description | Bootloader offset | Link |
| ----------- | ----------- |------------------ | ---- |
|`STM32F103`  | Generic STM32F103 target without LED | 8KiB |  |
|`STM32F072`  | Generic STM32F072 target without LED | 16KiB |  |
|`BLUEPILL`   | Cheap dev board | 8KiB | http://wiki.stm32duino.com/index.php?title=Blue_Pill |
|`MAPLEMINI`  | LeafLabs Maple Mini board and clone derivatives | 8KiB | http://wiki.stm32duino.com/index.php?title=Maple_Mini |


## Overriding defaults
Local makefile settings can be set by creating a `local.mk`, which is automatically included.

Here is an example `local.mk` that changes the default target to the MAPLEMINI.

    TARGET ?= STLINK

## Using the bootloader
### Building for the bootloader
The bootloader occupies the lower 8KiB or 16KiB of flash, so your application must offset its flash contents by 8KiB or 16KiB. This can be done by modifying your linker script or flags as appropriate.

### Switching to the bootloader
The bootloader can be built to look for arbitrary patterns, but the default for the STM32F103 target looks for a magic value stored in the RTC backup registers. Writing the magic value and then resetting will run the bootloader instead of the main application.
When compiling with the DOUBLE_TAP option, the bootloader can be activated by double-tapping the reset button.

## Licensing
All contents of the dapboot project are licensed under terms that are compatible with the terms of the GNU Lesser General Public License version 3.

Non-libopencm3 related portions of the dapboot project are licensed under the less restrictive ISC license, except where otherwise specified in the headers of specific files.

See the LICENSE file for full details.
