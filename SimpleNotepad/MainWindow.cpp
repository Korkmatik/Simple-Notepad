#include "MainWindow.h"



MainWindow::MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LRESULT(*WindowProcedure)(HWND, UINT, WPARAM, LPARAM)) :
	hInstance(hInstance), hPrevInstance(hPrevInstance), lpCmdLine(lpCmdLine), nCmdShow(nCmdShow), WindowProcedure(WindowProcedure)
{
	initWindow();

	if (!RegisterClassW(&wc))
		PostQuitMessage(-1);
}


MainWindow::~MainWindow() {}

void MainWindow::start() {
	hMainWindow = CreateWindowW(wc.lpszClassName, L"First",
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		100, 100, 1024, 600,
		NULL, NULL, NULL, NULL);

	MSG msg = {};

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void MainWindow::initWindow() {
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"MainWindow";
}


