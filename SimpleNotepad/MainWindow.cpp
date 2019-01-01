#include "MainWindow.h"

#include <stdio.h> 



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
		100, 100, 1050, 600,
		NULL, NULL, NULL, NULL);

	MSG msg = {};

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void MainWindow::addComponents(HWND hWnd, HWND& hEditB) {
	hEditB = CreateWindowW(L"Edit", L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
		15, 80, 1000, 450,
		hWnd, NULL, NULL, NULL);

	HMENU hFileMenuBar = CreateMenu();
	HMENU hFileMenu = CreateMenu();

	AppendMenuW(hFileMenu, MF_STRING, FILE_NEW, L"New");
	AppendMenuW(hFileMenu, MF_STRING, FILE_OPEN, L"Open");
	AppendMenuW(hFileMenu, MF_STRING, FILE_SAVE, L"Save");
	AppendMenuW(hFileMenu, MF_STRING, FILE_SAVE_AS, L"Save as ..");

	AppendMenuW(hFileMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

	SetMenu(hWnd, hFileMenuBar);
}

void MainWindow::getSaveFilePath(HWND hWnd) {
	OPENFILENAME ofn;

	char fileName[10000];
	
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = fileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 10000;
	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.cpp\0Text Files\0*.txt\0";
	ofn.nFilterIndex = 1;

	if (GetSaveFileName(&ofn) != NULL)
		saveFile(ofn.lpstrFile);
}

void MainWindow::getOpenFilePath(HWND hWnd) {
	OPENFILENAME ofn;
	char fileName[10000];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = fileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 10000;
	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.cpp\0Text Files\0*.txt\0";
	ofn.nFilterIndex = 1;

	if (GetOpenFileName(&ofn) != NULL) {
		openFile(ofn.lpstrFile);
	}
}

void MainWindow::initWindow() {
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"MainWindow";
}

void MainWindow::saveFile(const LPSTR & file) {
	FILE* f;
	fopen_s(&f, file, "w");

	if (f != NULL) {
		int textLength = GetWindowTextLength(hEditBox);
		char* text;
		if ((text = (char*)malloc(textLength * sizeof(char) + 1)) != NULL) {
			GetWindowText(hEditBox, text, textLength);
		}
		fwrite(text, textLength, 1, f);
		fclose(f);
		free(text);
	}
}

void MainWindow::openFile(const LPSTR & file) {
	FILE* f;
	char* data;
	unsigned int dSize;

	fopen_s(&f, file, "rb");

	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		dSize = ftell(f) + 1;
		rewind(f);
		if ((data = (char*)malloc(dSize * sizeof(char))) != NULL) {
			fread(data, dSize - 1, 1, f);
			data[dSize - 1] = '\0';

			SetWindowText(hEditBox, data);
			fclose(f);
			free(data);
		}
	}
}


