# project specific files
SRC = matrix.c

COMMON_VPATH += $(LIB_PATH)/ec_touch/include

LDFLAGS += -L$(LIB_PATH)/ec_touch/lib/ -lec_touch_4x12

#For platform and packs
ARM_ATSAM = SAMD51G18A
MCU = cortex-m4

BOOTLOADER_SIZE = 16384

NO_USB2422 = yes
NO_SR_EXP = yes

CUSTOM_MATRIX = yes

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no        # Mouse keys(+4700)
EXTRAKEY_ENABLE = no # yes       # Audio control and System control(+450)
CONSOLE_ENABLE = yes         # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no # yes           # USB Nkey Rollover
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = no         # Unicode
VIRTSER_ENABLE = no         # USB Serial Driver
RAW_ENABLE = no             # Raw device
AUTO_SHIFT_ENABLE = no      # Auto Shift
TAP_DANCE_ENABLE = no
