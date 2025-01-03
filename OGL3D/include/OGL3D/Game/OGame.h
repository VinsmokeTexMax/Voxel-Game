#pragma once
#include <OGL3D/OPrerequisites.h>

#include <memory>

class OGraphicsEngine;
class OWindow;
class OGame
{

public:
	OGame(); // Constructor
	~OGame(); // Destructor

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();


	void Run();
	void Quit();

protected:

	bool m_isRunning = true;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
	std::unique_ptr<OWindow> m_display;

	OVertexArrayObjectPtr m_triangleVAO;
	OShaderProgramPtr m_shader;

};