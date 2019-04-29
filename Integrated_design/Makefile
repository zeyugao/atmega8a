
C_SOURCES := 

C_SOURCES += \
./main.c \
./dht11.c \
./hc_sr04.c \
./menu.c \
./boss_mode.c \
./snake.c \
../module/custom_char.c \
../module/i2c_pcf8574t.c \
../module/i2c_lcd1602.c \
../module/keyboard.c \
../module/dht11.c \
../module/28byj_48.c \
../module/hc_sr04.c

all: clean program.hex

program.hex: $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe$(QUOTE) -O2 -mmcu=atmega8 -DBUILD -o program.elf $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe$(QUOTE) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "program.elf" "program.hex"	

clean:
	del /q *.elf *.hex *.o