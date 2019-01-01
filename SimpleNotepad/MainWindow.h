#pragma once
#include <Windows.h>

class MainWindow
{
public:
	HWND hEditBox;
	enum RESOURCE { FILE_NEW, FILE_OPEN, FILE_SAVE, FILE_SAVE_AS};

	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LRESULT(*WindowProcedure)(HWND, UINT, WPARAM, LPARAM));
	~MainWindow();

	void start();
	void addComponents(HWND hWnd, HWND& hEditB);
	void getSaveFilePath(HWND hWnd);
	void getOpenFilePath(HWND hWnd);

private:
	WNDCLASSW wc = {};
	HINSTANCE hInstance, hPrevInstance;
	LPSTR lpCmdLine;
	int nCmdShow;
	HWND hMainWindow;
	LRESULT (*WindowProcedure)(HWND, UINT, WPARAM, LPARAM);

	void initWindow();
	void saveFile(const LPSTR& file);
	void openFile(const LPSTR& file);
};

