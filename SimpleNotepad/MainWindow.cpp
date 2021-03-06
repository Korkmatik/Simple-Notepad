#include "MainWindow.h"

#include <stdio.h> 
#include <string.h>
#include <time.h>


MainWindow::MainWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, LRESULT(*WindowProcedure)(HWND, UINT, WPARAM, LPARAM)) :
	hInstance(hInstance), hPrevInstance(hPrevInstance), lpCmdLine(lpCmdLine), nCmdShow(nCmdShow), WindowProcedure(WindowProcedure)
{
	initWindow();

	if (!RegisterClassW(&wc))
		PostQuitMessage(-1);
}


MainWindow::~MainWindow() {}

void MainWindow::start() {
	hMainWindow = CreateWindowW(wc.lpszClassName, L"Simple Notepad",
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
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
		15, 80, 1000, 450,
		hWnd, NULL, NULL, NULL);

	HMENU hMenuBar = CreateMenu();

	HMENU hFileMenu = CreateMenu();
	AppendMenuW(hFileMenu, MF_STRING, FILE_NEW, L"New");
	AppendMenuW(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenuW(hFileMenu, MF_STRING, FILE_OPEN, L"Open");
	AppendMenuW(hFileMenu, MF_STRING, FILE_SAVE, L"Save");
	AppendMenuW(hFileMenu, MF_STRING, FILE_SAVE_AS, L"Save as ..");
	AppendMenuW(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenuW(hFileMenu, MF_STRING, FILE_EXIT, L"Exit");

	HMENU hTemplateMenu = CreateMenu();
	AppendMenuW(hTemplateMenu, MF_STRING, TEMPLATE_TIME_OF_DAY, L"Time of day");
	AppendMenuW(hTemplateMenu, MF_STRING, TEMPLATE_DATE, L"Date");
	AppendMenuW(hTemplateMenu, MF_STRING, TEMPLATE_TIME, L"Time");


	AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hTemplateMenu, L"Templates");
	SetMenu(hWnd, hMenuBar);
}

void MainWindow::newFile(HWND hWnd) {
	int retVal = MessageBox(hWnd, "Do you want to save before creating a new file?", "New file ..", MB_YESNOCANCEL);

	if (retVal == IDCANCEL)
		return;
	else if (retVal == IDNO) {
		saveChanged = false;
		clearEditControl();
	}
	else if (retVal == IDYES) {
		save(hWnd);
		saveChanged = false;
		clearEditControl();
	}
}

void MainWindow::save(HWND hWnd) {
	if (saveChanged) {
		saveFile(path);
	} else {
		getSaveFilePath(hWnd);
	}
}

void MainWindow::getSaveFilePath(HWND hWnd) {
	OPENFILENAME ofn;
	
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = path;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 10000;
	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.cpp\0Text Files\0*.txt\0";
	ofn.nFilterIndex = 1;

	if (GetSaveFileName(&ofn) != NULL) {
		saveFile(ofn.lpstrFile);
		saveChanged = true;
	}
	
}

void MainWindow::getOpenFilePath(HWND hWnd) {
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = path;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 10000;
	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.cpp\0Text Files\0*.txt\0";
	ofn.nFilterIndex = 1;

	if (GetOpenFileName(&ofn) != NULL) {
		openFile(ofn.lpstrFile);
		saveChanged = true;
		char title[1000] = "Simple Notepad - ";
		strcat_s(title, 1000, path);
		SetWindowText(hWnd, title);
	}
}

void MainWindow::exit(HWND hWnd) {
	int retVel = MessageBoxW(hWnd, L"Do you want to save before exiting?", L"Exit", MB_YESNOCANCEL);
	if (retVel == IDCANCEL)
		return;
	else if (retVel == IDNO)
		PostQuitMessage(0);
	else if (retVel == IDYES) {
		save(hWnd);
		PostQuitMessage(0);
	}
}

void MainWindow::insertDate(HWND hWnd) {
	
	char* timeBuffer = getTime();
	char date[11];
	int j = 0;
	for (int i = 0; i < 10; ++j, i++) {
		date[j] = timeBuffer[i];
	}
	date[j] = '\0';

	if(insertIntoEditControl(date) == false)
		MessageBox(NULL, "Couldn't insert Date into edit control", "Error", MB_ICONERROR);

}

void MainWindow::insertTimeOfDay(HWND hWnd) {
	char* fullTime = getTime();
	char time[7];

	int j = 0;
	for (int i = 11; i < 16; ++j, ++i) {
		time[j] = fullTime[i];
	}
	time[j] = '\0';

	if (insertIntoEditControl(time) == false)
		MessageBox(NULL, "Couldn't insert Time into edit control", "Error", MB_ICONERROR);
}

void MainWindow::insertTime(HWND hWnd) {
	char* fullTime = getTime();

	if (insertIntoEditControl(fullTime) == false)
		MessageBox(NULL, "Couldn't insert Time into edit control", "Error", MB_ICONERROR);
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

char * MainWindow::getTime() {
	time_t rawtime;
	struct tm newTime;
	static char timeBuffer[26];
	static char err[] = "Error";

	time(&rawtime);

	if (localtime_s(&newTime, &rawtime)) {
		MessageBox(NULL, "Error: localtime_s", "Error", MB_OK);
		return err;
	}
	if (asctime_s(timeBuffer, 26, &newTime)) {
		MessageBox(NULL, "Error: asctime_s", "Time", MB_OK);
		return err;
	}

	return timeBuffer;
}

bool MainWindow::insertIntoEditControl(char * txt) {
	int textLength = GetWindowTextLength(hEditBox) + strlen(txt) + 1;

	char* buffer = (char*)malloc(textLength);
	if (buffer == NULL) return false;

	GetWindowText(hEditBox, buffer, textLength);

	strcat_s(buffer, textLength, txt);

	SetWindowText(hEditBox, buffer);

	free(buffer);

	return true;
}

void MainWindow::clearEditControl() {
	SetWindowText(hEditBox, "");
}


