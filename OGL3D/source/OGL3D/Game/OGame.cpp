#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <Windows.h>

OGame::OGame()
{
	m_display = std::unique_ptr< OWindow>(new OWindow());
}

OGame::~OGame()
{
	
}

void OGame::Run()
{
	while (m_isRunning && !m_display->isClosed())
	{
		MSG m_msg;
		if (PeekMessage(&m_msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		Sleep(1);
	}
}

void OGame::Quit()
{
	m_isRunning = false;
}
