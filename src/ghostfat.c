

#include <string.h>
#include "target.h"
#include "dmesg.h"
#include "ghostfat.h"
#include "config.h"

typedef struct {
    uint8_t JumpInstruction[3];
    uint8_t OEMInfo[8];
    uint16_t SectorSize;
    uint8_t SectorsPerCluster;
    uint16_t ReservedSectors;
    uint8_t FATCopies;
    uint16_t RootDirectoryEntries;
    uint16_t TotalSectors16;
    uint8_t MediaDescriptor;
    uint16_t SectorsPerFAT;
    uint16_t SectorsPerTrack;
    uint16_t Heads;
    uint32_t HiddenSectors;
    uint32_t TotalSectors32;
    uint8_t PhysicalDriveNum;
    uint8_t Reserved;
    uint8_t ExtendedBootSig;
    uint32_t VolumeSerialNumber;
    uint8_t VolumeLabel[11];
    uint8_t FilesystemIdentifier[8];
} __attribute__((packed)) FAT_BootBlock;

typedef struct {
    char name[8];
    char ext[3];
    uint8_t attrs;
    uint8_t reserved;
    uint8_t createTimeFine;
    uint16_t createTime;
    uint16_t createDate;
    uint16_t lastAccessDate;
    uint16_t highStartCluster;
    uint16_t updateTime;
    uint16_t updateDate;
    uint16_t startCluster;
    uint32_t size;
} __attribute__((packed)) DirEntry;

#if (FILE_INFO == 1)
static size_t flashSize(void) {
    return USER_FLASH_END - USER_FLASH_START;
}
#endif

//#define DBG NOOP
#define DBG DMESG

struct TextFile {
    const char name[11];
    const char *content;
};

#define NUM_FAT_BLOCKS BIN_NUM_BLOCKS

#define STR0(x) #x
#define STR(x) STR0(x)
const char infoUf2File[] = //
    "MSC Bootloader " MSC_VERSION "\r\n"
    "Model: " PRODUCT_NAME "\r\n"
    "Bootloader size: " BOOTLOADER_SIZE "\r\n";

static const struct TextFile info[] = {
    {.name = "INFO_MSCTXT", .content = infoUf2File},
    {.name = "CURRENT BIN"},
};
#define NUM_INFO (int)(sizeof(info) / sizeof(info[0]))

#define BIN_SIZE (flashSize())
#define BIN_SECTORS (BIN_SIZE / 512)
#define BIN_FIRST_SECTOR (NUM_INFO + 1)
#define BIN_LAST_SECTOR (uint32_t)(BIN_FIRST_SECTOR + BIN_SECTORS - 1)

#define RESERVED_SECTORS 1
#define ROOT_DIR_SECTORS 4
#define SECTORS_PER_FAT ((NUM_FAT_BLOCKS * 2 + 511) / 512)

#define START_FAT0 RESERVED_SECTORS
#define START_FAT1 (START_FAT0 + SECTORS_PER_FAT)
#define START_ROOTDIR (START_FAT1 + SECTORS_PER_FAT)
#define START_CLUSTERS (START_ROOTDIR + ROOT_DIR_SECTORS)

static const FAT_BootBlock BootBlock = {
    .JumpInstruction = {0xeb, 0x3c, 0x90},
    .OEMInfo = "MSC MSC ",
    .SectorSize = 512,
    .SectorsPerCluster = 1,
    .ReservedSectors = RESERVED_SECTORS,
    .FATCopies = 2,
    .RootDirectoryEntries = (ROOT_DIR_SECTORS * 512 / 32),
    .TotalSectors16 = NUM_FAT_BLOCKS - 2,
    .MediaDescriptor = 0xF8,
    .SectorsPerFAT = SECTORS_PER_FAT,
    .SectorsPerTrack = 1,
    .Heads = 1,
    .ExtendedBootSig = 0x29,
    .VolumeSerialNumber = 0x00420042,
    .VolumeLabel = VOLUME_LABEL,
    .FilesystemIdentifier = "FAT16   ",
};

#define NO_CACHE 0xffffffff

static uint32_t flashAddr = NO_CACHE;
static uint8_t flashBuf[FLASH_PAGE_SIZE] __attribute__((aligned(4)));
static bool firstFlush = true;
static bool hadWrite = false;
static uint32_t ms;
static uint32_t resetTime;
static uint32_t lastFlush;

static void flushFlash(void) {
    lastFlush = ms;
    if (flashAddr == NO_CACHE)
        return;

    if (firstFlush) {
        firstFlush = false;

        // disable bootloader or something
    }

    DBG("Flush at %x", flashAddr);
    if (memcmp(flashBuf, (void *)flashAddr, FLASH_PAGE_SIZE) != 0) {
        DBG("Write flush at %x", flashAddr);

        target_flash_unlock();
        bool ok = target_flash_program_array((void *)flashAddr, (void*)flashBuf, FLASH_PAGE_SIZE / 2);
        target_flash_lock();
        (void)ok;
    }

    flashAddr = NO_CACHE;
}

static void flash_write(uint32_t dst, const uint8_t *src, int len) {
    uint32_t newAddr = dst & ~(FLASH_PAGE_SIZE - 1);

    hadWrite = true;

    if (newAddr != flashAddr) {
        flushFlash();
        flashAddr = newAddr;
        memcpy(flashBuf, (void *)newAddr, FLASH_PAGE_SIZE);
    }
    memcpy(flashBuf + (dst & (FLASH_PAGE_SIZE - 1)), src, len);
}

static void uf2_timer_start(int delay) {
    resetTime = ms + delay;
}

// called roughly every 1ms
void ghostfat_1ms() {
    ms++;

    if (resetTime && ms >= resetTime) {
        flushFlash();
        target_manifest_app();
        while (1);
    }

    if (lastFlush && ms - lastFlush > 100) {
        flushFlash();
    }
}

static void padded_memcpy(char *dst, const char *src, int len) {
    for (int i = 0; i < len; ++i) {
        if (*src)
            *dst = *src++;
        else
            *dst = ' ';
        dst++;
    }
}

int read_block(uint32_t block_no, uint8_t *data) {
    for(uint16_t x=0; x<512;x++) {
      data[x] = 0;
    }

    //memset(data, 0, 512);
    uint32_t sectionIdx = block_no;

    if (block_no == 0) {
        memcpy(data, &BootBlock, sizeof(BootBlock));
        data[510] = 0x55;
        data[511] = 0xaa;
        // logval("data[0]", data[0]);
    } else if (block_no < START_ROOTDIR) {
        sectionIdx -= START_FAT0;
        // logval("sidx", sectionIdx);
        if (sectionIdx >= SECTORS_PER_FAT)
            sectionIdx -= SECTORS_PER_FAT;
        if (sectionIdx == 0) {
            data[0] = 0xf0;
            for (int i = 1; i < NUM_INFO * 2 + 4; ++i) {
                data[i] = 0xff;
            }
        }
#if (FILE_INFO == 1)
        for (int i = 0; i < 256; ++i) {
            uint32_t v = sectionIdx * 512 + i;
            if (BIN_FIRST_SECTOR <= v && v <= BIN_LAST_SECTOR)
                ((uint16_t *)(void *)data)[i] = v == BIN_LAST_SECTOR ? 0xffff : v + 1;
        }
#endif
    } else if (block_no < START_CLUSTERS) {
        sectionIdx -= START_ROOTDIR;
        if (sectionIdx == 0) {

            DirEntry *d = (void *)data;
            padded_memcpy(d->name, (const char *)BootBlock.VolumeLabel, 11);
            d->attrs = 0x28;
#if (FILE_INFO == 1)
            for (int i = 0; i < NUM_INFO; ++i) {
                d++;
                const struct TextFile *inf = &info[i];
                d->size = inf->content ? strlen(inf->content) : BIN_SIZE;
                d->startCluster = i + 2;
                d->attrs = 0x01;
                padded_memcpy(d->name, inf->name, 11);
            }
#endif
        }
    } else {
        sectionIdx -= START_CLUSTERS;
#if (FILE_INFO == 1)
        if (sectionIdx < NUM_INFO - 1) {
            memcpy(data, info[sectionIdx].content, strlen(info[sectionIdx].content));
        } else {
            sectionIdx -= NUM_INFO - 1;
            uint32_t addr = sectionIdx * 512;
            if (addr < flashSize()) {

                memcpy(data, (void *)(addr + APP_BASE_ADDRESS), 512);
            }
        }
#endif
    }

    return 0;
}


static void write_block_bin(uint32_t block_no, const uint8_t *data) {
    static bool binStart=0;
    static uint32_t targetAddr = USER_FLASH_START;

    (void)block_no;

    if (!binStart && (((data[2]+(data[3]<<8)) & 0x2FFE) == 0x2000)) {
      binStart = 1;
    }

    if(!binStart) {
      return;
    }
    flash_write(targetAddr, data, 512);
    targetAddr+=512;
    uf2_timer_start(500);

}


int write_block(uint32_t lba, const uint8_t *copy_from)
{
    DBG("Write lba: %x", lba);
    target_set_led(1);
    if(lba > 0x44) {
      write_block_bin(lba, copy_from);
    }
    target_set_led(0);
    return 0;
}
