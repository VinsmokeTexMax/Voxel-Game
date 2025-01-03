#pragma once

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

};