#ifndef UNICODE
#undef _UNICODE
#else
#ifndef _UNICODE
#define _UNICODE
#endif
#endif

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>

#include "../module/serial_port.h"

using namespace std;

int wmain(int argc, const char *argv[]) {
	SerialPort serial_port;

	UINT port = 4;
	UINT baud = CBR_4800;

	if (argc == 2) {
		port = atoi(argv[1]);
	}
	if (!serial_port.InitPort(port, baud)) {
		cout << "can't init port on COM" << port << ", baud " << baud << endl;
		return 1;
	}
	else {
		cout << "init success on COM" << port << ", baud " << baud << endl;
	}

	ifstream in;
	in.open("video_context.txt", std::ios_base::in);
	int data;
	int count = 0;
	string line;
	while (std::getline(in, line)) {
		istringstream iss(line);
		
		int len = 0;
		unsigned char payload[64];
		while (iss >> data) {
			payload[len++] = (unsigned char)data;
		}
		cout << "send payload len: " << len << endl;
		serial_port.WriteData(payload, len);

		char read_data;
		serial_port.ReadChar(read_data);
		cout << "frame: " << count << ", result: " << (int)read_data << endl;
		count++;
	}

	return 0;
}