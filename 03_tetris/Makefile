CC	= mist32-elf-gcc
CFLAGS	= -nostdlib -ffreestanding -std=gnu11 -Wall -O3
LIBGCC = `${CC} -print-libgcc-file-name`

SRC	= start.s tetris.c uart.c display.c keyboard.c lib.c
HEAD	= tetris.h io.h
ELF	= tetris.elf
BIN	= $(ELF:.elf=.bin)
HEX	= $(ELF:.elf=.hex)

all:	$(BIN) $(HEX)

clean:
	rm -f $(BIN) $(HEX) $(ELF)

.SUFFIXES:	.elf .bin
.elf.bin:
	mist32-elf-objcopy -O binary $< $@
.SUFFIXES:	.elf .hex
.elf.hex:
	mist32-elf-objcopy -O ihex $< $@

$(BIN):	$(ELF)
$(HEX):	$(ELF)

$(ELF):	$(SRC) $(HEAD)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBGCC)
