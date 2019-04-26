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

int wmain() {
	CSerialPort serial_port;

	UINT port = 3;
	UINT baud = CBR_4800;

	if (!serial_port.InitPort(port, baud)) {
		cout << "can't init port on COM" << port << ", baud " << baud << endl;
		return 1;
	}
	else {
		cout << "init success" << endl;
	}

	ifstream in;
	in.open("video_context.txt", std::ios_base::in);
	int data;
	int count = 0;
	string line;
	while (std::getline(in, line)) {
		istringstream iss(line);
		while (iss >> data) {
			//cout << data << endl;
			unsigned char payload[] = { (unsigned char)data };
			serial_port.WriteData(payload, 1);
		}
		char read_data;
		serial_port.ReadChar(read_data);
		cout << "frame: " << count << ", result: " << (int)read_data << endl;
		count++;
	}

	return 0;
}