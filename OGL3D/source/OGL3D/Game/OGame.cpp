#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();

	m_display->makeCurrentContext();
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(0.024, 0.224, 0.437, 1));

	m_display->present(false);
}

void OGame::onDestroy()
{
}

void OGame::Quit()
{
	m_isRunning = false;
}
