CC	= mist32e-elf-gcc
CFLAGS	= -nostdlib -ffreestanding -std=gnu11 -Wall

SRC	= start.s display_keyboard.c uart.c display.c keyboard.c
HEAD	= io.h
ELF	= display_keyboard.elf
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
	$(CC) $(CFLAGS) -o $@ $(SRC)
