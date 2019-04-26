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
	while (in.peek() != EOF) {
		in >> data;
		//cout << data << endl;
		unsigned char payload[] = { (unsigned char)data };
		serial_port.WriteData(payload, 1);
		char read_data;
		serial_port.ReadChar(read_data);
		//cout << (int)read_data << endl;
	}

	return 0;
}