
C_SOURCES := 

C_SOURCES += \
./main.cc \
../module/serial_port.cc

all: clean program.exe

program.exe: $(C_SOURCES)
	g++.exe -O2 -o program.exe -std=c++17 -municode $(C_SOURCES)

clean:
	del /q *.exe