all: lab0.hex

lab0.elf: lab0.c 
	avr-gcc -mmcu=atmega324p -DF_CPU=16000000 -std=c99 -Wall -O3 -o $@ $^ 

lab0.hex: lab0.elf
	avr-objcopy -j .text -j .data -O ihex lab0.elf lab0.hex
	avr-objdump -t -h -S -C lab0.elf > lab0.lss
	avr-size lab0.elf

clean:
	rm -rf lab0.elf lab0.lss lab0.hex

.PHONY: all clean

