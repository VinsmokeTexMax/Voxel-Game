#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <Windows.h>

void OGame::Run()
{
	onCreate();
	while (m_isRunning)
	{
		MSG m_msg = {};
		if (PeekMessage(&m_msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);
			}
		}
		onUpdate();
	}
	onDestroy();
}