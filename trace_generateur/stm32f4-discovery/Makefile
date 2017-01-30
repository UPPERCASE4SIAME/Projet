# put your *.o targets here, make should handle the rest!

SRCS = main.c system_stm32f4xx.c tm_stm32f4_disco.c tm_stm32f4_gpio.c tm_stm32f4_usb_vcp.c usb_cdc_device/usbd_cdc_core.c usb_cdc_device/usbd_cdc_vcp.c usb_cdc_device/usbd_core.c usb_cdc_device/usbd_desc.c usb_cdc_device/usbd_ioreq.c usb_cdc_device/usbd_req.c usb_cdc_device/usbd_usr.c usb_cdc_device/usb_bsp.c usb_cdc_device/usb_core.c usb_cdc_device/usb_dcd.c usb_cdc_device/usb_dcd_int.c 

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=main

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

FLASH=st-flash

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

###################################################

vpath %.c src
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals 

SRCS += lib/startup_stm32f4xx.s # add startup file to build

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C lib

proj: 	$(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -Llib -lstm32f4 
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

upload: main.bin
	${FLASH} write main.bin 0x8000000

clean:
	$(MAKE) -C lib clean
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
