#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>

LRESULT CALLBACK WindProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
	{
		OWindow* window = (OWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
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
	wcex.style = CS_OWNDC;
	
	auto classId = RegisterClassEx(&wcex);
	assert(classId);

	RECT rect = { 0, 0, 1024, 768 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU, false);

	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classId), L"Voxel-Engine | OpenGL 3D Game", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, NULL);

	assert(m_handle);

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow((HWND)m_handle, SW_SHOW);
	UpdateWindow((HWND)m_handle);


	// Creating OpenGL Rendering Context

	auto hDC = GetDC((HWND)m_handle);

	int pfAttribs[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pf = 0;
	UINT numFormats = 0;
	wglChoosePixelFormatARB(hDC, pfAttribs, nullptr, 1, &pf, &numFormats);
	assert(numFormats);


	PIXELFORMATDESCRIPTOR pfd = {};
	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	SetPixelFormat(hDC, pf, &pfd);

	int openGLAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	m_conext = wglCreateContextAttribsARB(hDC, 0, openGLAttribs);
	assert(m_conext);

}

OWindow::~OWindow()
{
	wglDeleteContext(HGLRC(m_conext));
	DestroyWindow(HWND(m_handle));

}

void OWindow::makeCurrentContext()
{
	wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_conext));
}

void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);
}
