
C_SOURCES := 

C_SOURCES += \
./main.c \
./snake.c \
./light.c \
../module/i2c_lcd1602.c \
../module/i2c_pcf8574t.c

COMPILE_TIME = $(shell echo %date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%)

all: clean program.hex

program.hex: $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe$(QUOTE) -O2 -mmcu=atmega8 -DBUILD -o program.elf -D MY_TIME_STAMP=$(COMPILE_TIME) $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "program.elf" "program.hex"	

clean:
	del /q *.elf *.hex *.o