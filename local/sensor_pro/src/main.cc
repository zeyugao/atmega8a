#include "stdafx.h"
#include "main.h"
#include "../../module/serial_port.h"
#include <iostream>

HINSTANCE g_hInstance = NULL;
static LPCTSTR MainWndClass = TEXT("Sensors");

HWND Read_Button, Cancel_Button, edit_max_percent, edit_min_percent;
HWND text_light, text_temperature, text_humidity;

int nWidth = 400;
int nHeight = 300;

int _dpiX, _dpiY;

SerialPort serial_port;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
	HWND hWnd = nullptr;
	MSG msg;

	g_hInstance = hInstance;

	if (!RegisterMainWindowClass()) {
		MessageBox(NULL, TEXT("Error registering main window class."), TEXT("Error"), MB_ICONERROR | MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(0, MainWndClass, MainWndClass, WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX), CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, g_hInstance, NULL);
	if (hWnd) {
		HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
	}
	else {
		MessageBox(NULL, TEXT("Error creating main window."), TEXT("Error"), MB_ICONERROR | MB_OK);
		return 1;
	}

	RECT WindowRect, ClientRect;
	GetWindowRect(hWnd, &WindowRect);
	GetClientRect(hWnd, &ClientRect);

	nWidth += (WindowRect.right - WindowRect.left) - (ClientRect.right - ClientRect.left);
	nHeight += (WindowRect.bottom - WindowRect.top) - (ClientRect.bottom - ClientRect.top);

	int nX = (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
	int nY = (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;
	SetWindowPos(hWnd, nullptr, nX, nY, nWidth, nHeight, 0);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	serial_port.InitPort(3);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

int PointsToPixels(int pt) {
	return MulDiv(pt, _dpiY, 72);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HINSTANCE hInstance;
	HFONT hFont;
	LOGFONT lf;
	HDC hdc;
	char data[4];
	unsigned char query_payload[1];
	double v;
	switch (msg) {
		case WM_COMMAND:
			/*if (LOWORD(wParam) == IDB_READ_BUTTON) {
				MessageBox(hWnd, TEXT("OK"), TEXT(""), MB_OK);
			}*/
			switch (LOWORD(wParam)) {
				case IDB_READ_BUTTON:
					query_payload[0] = 1;
					serial_port.WriteData(query_payload, 1);
					// now the temperature and the humidity
					for (int i = 0; i < 4; i++) {
						serial_port.ReadChar(data[i]);
					}
					std::cout << (int)data[3] << (int)data[2] << " " << (int)data[1] << (int)data[0] << std::endl;
					wchar_t text[10];
					
					if(data[0]+data[1]+data[2]+data[3]){
					wsprintf(text, TEXT("%d%d"), (int)data[1], (int)data[0]);
					SendMessage(text_humidity, WM_SETTEXT, 0, (LPARAM)text);
					wsprintf(text, TEXT("%d%d"), (int)data[3], (int)data[2]);
					SendMessage(text_temperature, WM_SETTEXT, 0, (LPARAM)text);
					}
					// now the dht11
					query_payload[0] = 2;
					serial_port.WriteData(query_payload, 1);
					for (int i = 0; i < 2; i++) {
						serial_port.ReadChar(data[i]);
					}
					std::cout << (int)(unsigned char)data[1] << (int)(unsigned char)data[0] << std::endl;
					v = ((double)((unsigned char)data[0] << 8) + (double)(unsigned char)data[1]) * 5 / 1024;
					std::cout << v << std::endl;

					swprintf(text, TEXT("%f"), v);

					SendMessage(text_light, WM_SETTEXT, 0, (LPARAM)text);
					break;
			}
			break;
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			Read_Button = CreateWindow(TEXT("BUTTON"), TEXT("读取"), WS_CHILD | WS_VISIBLE, 50, 250, 100, 30, hWnd, (HMENU)IDB_READ_BUTTON, 0, 0);
			HWND static_light, static_temperature, static_humidity;

			static_light = CreateWindow(TEXT("static"), TEXT("当前DHT11电压"), WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 50, 150, 30, hWnd, (HMENU)1, 0, 0);
			static_temperature = CreateWindow(TEXT("static"), TEXT("当前温度"), WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 100, 150, 30, hWnd, (HMENU)2, 0, 0);
			static_humidity = CreateWindow(TEXT("static"), TEXT("当前湿度"), WS_CHILD | WS_VISIBLE | SS_LEFT, 50, 150, 150, 30, hWnd, (HMENU)3, 0, 0);

			text_light = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_LEFT, 250, 50, 150, 30, hWnd, (HMENU)4, 0, 0);
			text_temperature = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_LEFT, 250, 100, 150, 30, hWnd, (HMENU)5, 0, 0);			
			text_humidity = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_LEFT, 250, 150, 150, 30, hWnd, (HMENU)6, 0, 0);

			hdc = GetDC(NULL);
			if (hdc) {
				_dpiX = GetDeviceCaps(hdc, LOGPIXELSX);
				_dpiY = GetDeviceCaps(hdc, LOGPIXELSY);
				ReleaseDC(NULL, hdc);
			}

			GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
			lf.lfHeight = -PointsToPixels(13);
			wchar_t faceName[32];
			wsprintf(lf.lfFaceName, TEXT("微软雅黑"));
			hFont = CreateFontIndirect(&lf);
			SendMessage(static_light, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			SendMessage(static_temperature, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			SendMessage(static_humidity, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			SendMessage(text_light, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			SendMessage(text_temperature, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			SendMessage(text_humidity, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			SendMessage(Read_Button, WM_SETFONT, (WPARAM)hFont, (LPARAM)NULL);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL RegisterMainWindowClass() {
	WNDCLASSEX wc;

	wc.cbSize = sizeof(wc);
	wc.style = 0;
	wc.lpfnWndProc = &WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = (HICON)LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
	wc.hCursor = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = MainWndClass;
	wc.hIconSm = (HICON)LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

	return (RegisterClassEx(&wc));
}