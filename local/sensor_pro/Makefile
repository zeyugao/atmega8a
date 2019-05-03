CC = g++.exe
RC = windres.exe
EXECUTABLE_NAME = sensor_pro.exe

CFLAGS = -O2 -std=c++17 -DUNICODE -D_UNICODE

OBJS = obj/main.o obj/Resource.o obj/serial_port.o

all: bin/$(EXECUTABLE_NAME)

bin obj:
	@if not exist "$@" mkdir "$@"

obj/serial_port.o: ../module/serial_port.cc | obj
	${CC} ${CFLAGS} -c "$<" -o "$@

obj/%.o: src/%.cc | obj
	${CC} ${CFLAGS} -c "$<" -o "$@

obj/Resource.o: res/Resource.rc res/Application.manifest res/Application.ico src/Resource.h | obj
	${RC} -I./include -I./res -i "$<" -o "$@"

LDFLAGS = -mwindows -municode -mconsole

bin/${EXECUTABLE_NAME}: ${OBJS} | bin
	${CC} -o "$@" ${OBJS} ${LDFLAGS}

.PHONY : clean
clean:
	del /q .\\bin\\*.exe
	del /q .\\obj\\*.o