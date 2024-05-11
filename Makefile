# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2024 Fausto "O3" Ribeiro | ONT Lab <mailme@tripleoxygen.net>
#

PREFIX=mips-buildroot-linux-uclibc-
CC=$(PREFIX)gcc
LIBS=
STRIP=$(PREFIX)strip
CFLAGS=-Wall -std=c99 -march=mips1 -I. -Os -fPIC -nostdlib -nodefaultlibs
LDFLAGS=-Wl,-shared

all: libohwtc.so

libohwtc.so: libohwtc.o
	$(CC) $< -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)
	$(STRIP) $@

libohwtc.o: libohwtc.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf *.o *.so
