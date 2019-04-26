
C_SOURCES := 

C_SOURCES += \
./main.c \
../module/i2c_pcf8574t.c \
../module/i2c_lcd1602.c \
../module/usart.c

all: clean program.hex

program.hex: $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe$(QUOTE) -O2 -mmcu=atmega8 -DBUILD -o program.elf $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "program.elf" "program.hex"	

clean:
	del /q *.elf *.hex *.o