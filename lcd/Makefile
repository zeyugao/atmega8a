
all: clean main.hex

main.o:
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe$(QUOTE) -O2 -DBUILD -mmcu=atmega8 -c main.c

main.elf: main.o
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe$(QUOTE) -mmcu=atmega8 -o main.elf main.o

main.hex: main.elf
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "main.elf" "main.hex"

clean:
	del /q *.elf *.hex *.o