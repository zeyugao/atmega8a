
C_SOURCES := 

C_SOURCES += \
./main.c \
../module/i2c_pcf8574t.c \
../module/i2c_lcd1602.c \
../module/usart.c

AVR_GCC = D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe
AVR_OBJ_COPY = D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe

all: clean program.hex

program.hex: $(C_SOURCES)
	$(AVR_GCC) -O2 -mmcu=atmega8 -DBUILD -o program.elf $(C_SOURCES)
	$(AVR_OBJ_COPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "program.elf" "program.hex"	

clean:
	del /q *.elf *.hex *.o