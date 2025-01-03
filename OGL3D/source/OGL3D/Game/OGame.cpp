#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <OGL3D/Graphics/OVertexArrayObject.h>

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>();
	m_display = std::make_unique<OWindow>();

	m_display->makeCurrentContext();
	m_graphicsEngine->setViewport(m_display->getInnerSize());
}

OGame::~OGame()
{
}

void OGame::onCreate()
{
	const f32 triangleVertices[] = {
		-0.5f, -0.5f, 0.0f,
		1,		0,		0,

		0.5f, -0.5f, 0.0f,
		0,		1,		0,

		0.0f, 0.5f, 0.0f,
		0,		0,		1
	};

	OvertexAttribute attributeList[] = {
		3,// position
		3 // color
	};

	m_triangleVAO = m_graphicsEngine->createVertexArrayObject({ 
		(void*)triangleVertices, 
		(3+3) * sizeof(f32),
		3,

		attributeList,
		2
		});

	m_shader = m_graphicsEngine->createShaderProgram(
		{
			L"Assets/Shaders/BasicShader.vert", 
			L"Assets/Shaders/BasicShader.frag"
		});
}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(0.024, 0.224, 0.437, 1));

	m_graphicsEngine->setVertexArrayObject(m_triangleVAO);
	m_graphicsEngine->setShaderProgram(m_shader);
	m_graphicsEngine->drawTriangles(m_triangleVAO->getVertexBufferSize(), 0);

	

	m_display->present(false);
}

void OGame::onDestroy()
{
}

void OGame::Quit()
{
	m_isRunning = false;
}
