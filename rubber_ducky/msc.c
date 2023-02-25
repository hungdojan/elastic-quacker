/**
 * @brief MSC class function definition with the implementation of the FAT12 file system disk.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @file msc.c
 * @author Hung Do
 * @date 22/02/2023
 */
#include "tusb.h"
#include "class/msc/msc_device.h"
#include "usb_general.h"

bool is_ejected = false;

// the documentation for FAT12 can be found here:
// http://www.c-jump.com/CIS24/Slides/FAT/lecture.html
static uint8_t memory_disk[NUM_OF_SECTORS][BYTES_PER_SECTOR] = {
    // Boot Table
    {
        0xEB, 0x3C, 0x90,   // Jump instruction
        'M', 'S', 'D', 'O', 'S', '5', '.', '0',     // OEM name in ASCII
        U16_TO_U8S_LE(BYTES_PER_SECTOR),            // Bytes per sector (512)
        0x01,               // Sectors per cluster (1)
        0x01, 0x00,         // Size of reserved area, in Sectors (1)
        0x01,               // Number of FATs (1)
        0x10, 0x00,         // Maximum number of files in the root directory (16)
        U16_TO_U8S_LE(NUM_OF_SECTORS),              // Total number of sectors in the filesystem (16)
        0xf8,               // Media descriptor type (f8 - hard disk)
        0x01, 0x00,         // Number of sectors per FAT (1)
        0x01, 0x00,         // Number of sectors per track
        0x01, 0x00,         // Number of heads (1)
        0x00, 0x00, 0x00, 0x00, // Number of hidden sectors (0)
        0x00, 0x00, 0x00, 0x00, // Number of sectors in the file system (0)
        0x80,               // Physical disk number; used by BIOS INT
        0x00,               // Reserved
        0x29,               // Extended boot signature (0x29)
        0x5c, 0x01, 0x23, 0x5a, // Volume serial number
        'F', 'I', 'T', ' ', 'S', 't', 'o', 'r', 'a', 'g', 'e',   // Volume label
        'F', 'A', 'T', '1', '2',    // System ID
        0x20, 0x20, 0x20, 0x00, 0x00,   // Bootstrap (63rd byte)
                                        //
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA,
    },
    // FAT12 table
    {
        0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    },
    // Root directory
    {
        // volume name
         'F',  'I',  'T',  ' ',  'V',  'o',  'l',  'u',  'm',  'e',  ' ', 0x08, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x52, 0x53, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // directory entries
        // 19/2/2023 15:50:36 -> 0xAC53 0x527E
         'A',  'u',  't',  'o',  'm',  'a',  't',  'a',  't',  'x',  't', 0x21, 0x00, 0x00, 0x7E, 0x52,
        0x53, 0xAC, 0x53, 0xAC, 0x00, 0x00, 0x7E, 0x52, 0x53, 0xAC, 0x02, 0x00, FILE_SIZE(sizeof(AUTOMATA_CONTENT)-1),
         '.',  'R',  'E',  'A',  'D',  'M',  'E',  ' ',  'm',  'd',  ' ', 0x22, 0x00, 0x00, 0x7F, 0x52,
        0x53, 0xAC, 0x53, 0xAC, 0x00, 0x00, 0x7F, 0x52, 0x53, 0xAC, 0x03, 0x00, FILE_SIZE(sizeof(README_CONTENT)-1),
    },
    // Files
    {
        AUTOMATA_CONTENT,
    },
    {
        README_CONTENT,
    },
};

int32_t tud_msc_read10_cb (uint8_t lun, uint32_t lba, uint32_t offset, void* buffer, uint32_t bufsize) {
    (void) lun; // only one logical unit
    if (lba >= NUM_OF_SECTORS) {
        return -1;
    }
    memcpy(buffer, memory_disk[lba] + offset, bufsize);

    return bufsize;
}

int32_t tud_msc_write10_cb (uint8_t lun, uint32_t lba, uint32_t offset, uint8_t* buffer, uint32_t bufsize) {
    (void) lun; // only one logical unit

    if (lba >= NUM_OF_SECTORS)
        return -1;

    memcpy(memory_disk[lba] + offset, buffer, bufsize);
    return bufsize;
}

void tud_msc_inquiry_cb(uint8_t lun, uint8_t vendor_id[8], uint8_t product_id[16], uint8_t product_rev[4]) {
    (void) lun; // only one logical unit
    const char vid[]  = "BUT FIT";
    const char pid[]  = "Rubber Storage";
    const char prev[] = "1.0";

    memcpy(vendor_id, vid, sizeof(vid));
    memcpy(product_id, pid, sizeof(pid));
    memcpy(product_rev, prev, sizeof(prev));
}

bool tud_msc_test_unit_ready_cb(uint8_t lun) {
    if (is_ejected) {
        tud_msc_set_sense(lun, SCSI_SENSE_NOT_READY, 0x04, 0x01);
        return false;
    }
    return true;
}

void tud_msc_capacity_cb(uint8_t lun, uint32_t* block_count, uint16_t* block_size) {
    (void) lun;

    *block_count = NUM_OF_SECTORS;
    *block_size = BYTES_PER_SECTOR;
}

bool tud_msc_start_stop_cb(uint8_t lun, uint8_t power_condition, bool start, bool load_eject) {
    (void) lun;
    (void) power_condition;

    if (!load_eject)
        return true;

    is_ejected = !start;
    return true;
}

int32_t tud_msc_scsi_cb (uint8_t lun, uint8_t const scsi_cmd[16], void* buffer, uint16_t bufsize) {
    (void) buffer;
    (void) bufsize;
    // TODO: fix later
    int32_t response_len = 0;

    switch(scsi_cmd[0]) {
        // already implemented
        case SCSI_CMD_TEST_UNIT_READY:
        case SCSI_CMD_INQUIRY:
        case SCSI_CMD_START_STOP_UNIT:
        case SCSI_CMD_READ_10:
        case SCSI_CMD_WRITE_10:
        case SCSI_CMD_READ_CAPACITY_10:
        case SCSI_CMD_READ_FORMAT_CAPACITY:
            break;
        case SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL:
            break;
        default:
            tud_msc_set_sense(lun, SCSI_SENSE_ILLEGAL_REQUEST, 0x20, 0x00);
            response_len = -1;
            break;
    }
    return response_len;
}

/* msc.c */
