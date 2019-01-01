#include "MainWindow.h"

MainWindow* window;

LRESULT WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam) {
		case MainWindow::FILE_NEW:
			window->newFile(hwnd);
			break;
		case MainWindow::FILE_SAVE:
			window->save(hwnd);
			break;
		case MainWindow::FILE_SAVE_AS:
			window->getSaveFilePath(hwnd);
			break;
		case MainWindow::FILE_OPEN:
			window->getOpenFilePath(hwnd);
			break;
		case MainWindow::FILE_EXIT:
			window->exit(hwnd);
			break;
		case MainWindow::TEMPLATE_DATE:
			window->insertDate(hwnd);
			break;
		case MainWindow::TEMPLATE_TIME_OF_DAY:
			window->insertTimeOfDay(hwnd);
			break;
		case MainWindow::TEMPLATE_TIME:
			window->insertTime(hwnd);
			break;
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
