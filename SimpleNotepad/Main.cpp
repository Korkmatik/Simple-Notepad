#include "MainWindow.h"

LRESULT WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
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
	
	MainWindow window(hInstance, hPrevInstance, lpCmdLine, nCmdShow, WindowProcedure);

	window.start();

	return EXIT_SUCCESS;
}
