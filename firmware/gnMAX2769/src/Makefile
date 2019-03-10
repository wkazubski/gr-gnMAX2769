#-----------------------------------------------------------------------------
# Makefile for gn-max FX2 firmware
#-----------------------------------------------------------------------------
# Copyright 2016 Wojciech Kazubski, wk@ire.pw.edu.pl
# Copyright 2007 Kolja Waschk, ixo.de
#-----------------------------------------------------------------------------
# This code is part of usbjtag. usbjtag is free software; you can redistribute
# it and/or modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of the License,
# or (at your option) any later version. usbjtag is distributed in the hope
# that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.  You should have received a
# copy of the GNU General Public License along with this program in the file
# COPYING; if not, write to the Free Software Foundation, Inc., 51 Franklin
# St, Fifth Floor, Boston, MA  02110-1301  USA
#-----------------------------------------------------------------------------

LIBDIR=../lib
LIB=../lib/libfx2.lib

CC=sdcc
CFLAGS+=-mmcs51 --no-xinit-opt -I../include

AS=sdas8051
ASFLAGS+=-plosgff

LDFLAGS=--code-loc 0x0000 --code-size 0x1800
LDFLAGS+=--xram-loc 0x1800 --xram-size 0x0800
LDFLAGS+=-Wl '-b USBDESCSEG = 0xE000'
LDFLAGS+=-L ${LIBDIR}

%.rel : %.a51
	$(AS) $(ASFLAGS) $<

%.rel : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

all: default

default: gnMAX2769_firmware.hex

gnMAX2769_firmware.hex: vectors.rel gnmax_main.rel usb_descriptors.rel _startup.rel gnmax_max2769.rel eeprom.rel init_gpif.rel gn3s_gpif.rel usrp_common.rel ${LIBDIR}/${LIB}
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $+ 

${LIBDIR}/${LIB}:
	make -C ${LIBDIR}

spi.rel: spi.c

.PHONY: clean distclean

clean:
	make -C ${LIBDIR} clean
	rm -f *.lst *.asm *.lib *.sym *.rel *.mem *.map *.rst *.lk *.ihex

distclean: clean

install:
	cp gnMAX2769_firmware.hex ../bin
