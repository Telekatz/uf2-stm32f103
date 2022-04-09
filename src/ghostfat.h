#pragma once

#define BIN_NUM_BLOCKS 8000
#define USER_FLASH_START (uint32_t)(APP_BASE_ADDRESS)
#define USER_FLASH_END (0x08000000+FLASH_SIZE_OVERRIDE)

int write_block(uint32_t lba, const uint8_t *copy_from);
int read_block(uint32_t block_no, uint8_t *data);
void ghostfat_1ms(void);
