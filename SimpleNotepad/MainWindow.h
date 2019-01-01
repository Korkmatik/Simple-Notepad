#pragma once
#include <Windows.h>

class MainWindow
{
public:
	HWND hEditBox;
	enum RESOURCE { FILE_NEW = 1, FILE_OPEN, FILE_SAVE, FILE_SAVE_AS, FILE_EXIT, 
		TEMPLATE_TIME_OF_DAY, TEMPLATE_DATE, TEMPLATE_TIME};

	MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LRESULT(*WindowProcedure)(HWND, UINT, WPARAM, LPARAM));
	~MainWindow();

	void start();
	void addComponents(HWND hWnd, HWND& hEditB);
	void newFile(HWND hWnd);
	void save(HWND hWnd);
	void getSaveFilePath(HWND hWnd);
	void getOpenFilePath(HWND hWnd);
	void exit(HWND hWnd);
	void insertDate(HWND hWnd);
	void insertTimeOfDay(HWND hWnd);
	void insertTime(HWND hWnd);

private:
	WNDCLASSW wc = {};
	HINSTANCE hInstance, hPrevInstance;
	LPSTR lpCmdLine;
	bool saveChanged = false;
	char path[10000];
	int nCmdShow;
	HWND hMainWindow;
	LRESULT (*WindowProcedure)(HWND, UINT, WPARAM, LPARAM);

	void initWindow();
	void saveFile(const LPSTR& file);
	void openFile(const LPSTR& file);
	char* getTime();
	bool insertIntoEditControl(char* txt);
	void clearEditControl();
};

