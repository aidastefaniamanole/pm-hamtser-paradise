all: hamsterParadise.hex

hamsterParadise.elf: hamsterParadise.c 
	avr-gcc -mmcu=atmega324p -DF_CPU=16000000 -std=c99 -Wall -O3 -o $@ $^ 

hamsterParadise.hex: hamsterParadise.elf
	avr-objcopy -j .text -j .data -O ihex hamsterParadise.elf hamsterParadise.hex
	avr-objdump -t -h -S -C hamsterParadise.elf > hamsterParadise.lss
	avr-size hamsterParadise.elf

clean:
	rm -rf hamsterParadise.elf hamsterParadise.lss hamsterParadise.hex

.PHONY: all clean

