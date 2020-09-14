#ifndef _MD_BOOTLOADER_H_
#define _MD_BOOTLOADER_H_

extern uint32_t _srom;
extern uint32_t _lrom;
extern uint32_t _erom;

#define BOOTLOADER_SERIAL_MAX_SIZE 20   //DO NOT MODIFY!

extern uint32_t _eram;
#ifdef KEYBOARD_massdrop_ctrl
//WARNING: These are only for CTRL bootloader release "v2.18Jun 22 2018 17:28:08" for bootloader_jump support
#define BOOTLOADER_MAGIC 0x3B9ACA00
#define MAGIC_ADDR (uint32_t *)(&_eram - 4)
#else
#define BOOTLOADER_MAGIC 0xf01669ef
#define MAGIC_ADDR (uint32_t *)((intptr_t)(&_eram) - 4)
#endif

#ifdef MD_BOOTLOADER

#define MCU_HZ 48000000
#define I2C_HZ 0 //Not used

#endif //MD_BOOTLOADER

#endif //_MD_BOOTLOADER_H_

