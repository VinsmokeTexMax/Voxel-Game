#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
#include <assert.h>

LRESULT CALLBACK WindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
	{
		OWindow* window = (OWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		window->onDestroy();
		break;
	}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return NULL;
}


OWindow::OWindow()
{
	WNDCLASSEX wcex = {};

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = L"OGL3DWindow";
	wcex.lpfnWndProc = &WindProc;
	
	assert(RegisterClassEx(&wcex));

	RECT rect = { 0, 0, 1024, 768 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(NULL, L"OGL3DWindow", L"Voxel-Engine | OpenGL 3D Game", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);

}

OWindow::~OWindow()
{

	DestroyWindow((HWND)m_handle);

}

void OWindow::onDestroy()
{
	m_handle = nullptr;
}

bool OWindow::isClosed()
{
	return !m_handle;
}
