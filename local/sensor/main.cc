#ifndef UNICODE
#undef _UNICODE
#else
#ifndef _UNICODE
#define _UNICODE
#endif
#endif

#include "../module/serial_port.h"
#include <iostream>

using namespace std;

SerialPort serial_port;

int wmain(int argc, const char *argv[]) {
	UINT port = 4;
	UINT baud = CBR_9600;

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

	unsigned char query_payload[] = { 0 };

	char r;

	char data[4];

	double v;

	while (1) {
		cin >> r;
		query_payload[0] = r - '0';
		serial_port.WriteData(query_payload, 1);

		switch (r - '0') {
			case 1:
				cout << "1" << endl;
				for (int i = 0; i < 4; i++) {
					serial_port.ReadChar(data[i]);
				}
				cout << (int)data[3] << (int)data[2] << " " << (int)data[1] << (int)data[0] << endl;
				break;
			case 2:
				cout << "2" << endl;
				for (int i = 0; i < 2; i++) {
					serial_port.ReadChar(data[i]);
				}
				cout << (int)(unsigned char)data[0] << " " << (int)(unsigned char)data[1] << endl;
				v = ((unsigned char)data[0] << 8) + (unsigned char)data[1];
				cout << v * 5 / 1024 << endl;
				break;
			default:
				break;
		}
	}
}