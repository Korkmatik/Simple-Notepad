#pragma once
#include <Windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LRESULT(*WindowProcedure)(HWND, UINT, WPARAM, LPARAM));
	~MainWindow();

	void start();

private:
	WNDCLASSW wc = {};
	HINSTANCE hInstance, hPrevInstance;
	LPSTR lpCmdLine;
	int nCmdShow;
	HWND hMainWindow;
	LRESULT (*WindowProcedure)(HWND, UINT, WPARAM, LPARAM);

	void initWindow();
};

