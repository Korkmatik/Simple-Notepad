#include "MainWindow.h"

MainWindow* window;

LRESULT WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case MainWindow::FILE_NEW:
			MessageBeep(MB_ICONINFORMATION);
		case MainWindow::FILE_SAVE:
			window->getSaveFilePath(hwnd);
		default:
			break;
		}
		break;
	case WM_CREATE:
		window->addComponents(hwnd, window->hEditBox);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	window = new MainWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WindowProcedure);


	window->start();

	delete window;

	return EXIT_SUCCESS;
}
