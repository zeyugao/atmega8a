
C_SOURCES := 

C_SOURCES += \
./main.cc \
../module/serial_port.cc

all: clean program.exe

program.exe: $(C_SOURCES)
	$(QUOTE)D:\Program\mingw\x86_64-8.1.0-release-posix-seh-rt_v6-rev0\bin\g++.exe$(QUOTE) -O2 -o program.exe -std=c++17 -municode $(C_SOURCES)

clean:
	del /q *.exe