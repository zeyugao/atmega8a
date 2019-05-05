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
#include <time.h>

#include "../module/serial_port.h"

using namespace std;

int wmain(int argc, const char *argv[]) {
	SerialPort serial_port;

	UINT port = 4;
	UINT baud = CBR_9600;

	if (argc == 2) {
		port = atoi(argv[1]);
	}
	cout << "Trying to init on COM" << port << ", with baud " << baud << endl;
	if (!serial_port.InitPort(port, baud)) {
		cout << "Can't init on COM" << port << ", with baud " << baud << endl;
		return 1;
	}
	else {
		cout << "Initialization succeed on COM" << port << ", with baud " << baud << endl;
	}

	ifstream in;
	in.open("video_context.txt", std::ios_base::in);
	int data;
	int count = 0;
	string line;
	clock_t start_time = clock();
	while (std::getline(in, line)) {
		istringstream iss(line);

		int len = 0;
		unsigned char payload[64];
		while (iss >> data) {
			payload[len++] = (unsigned char)data;
		}
		//cout << "send payload len: " << len << endl;
		//serial_port.send_with_verify(payload, len);
		serial_port.WriteData(payload, len);
		char read_data;
		serial_port.ReadChar(read_data);
		cout << "frame: " << count << ", result: " << (int)read_data << endl;
		count++;
		while (clock() - start_time < 67) {
			Sleep(1);
		}
		start_time += 66;
	}

	return 0;
}