#pragma once

#include <memory>

class OWindow;
class OGame
{

public:
	OGame(); // Constructor
	~OGame(); // Destructor

	void Run();
	void Quit();

protected:

	bool m_isRunning = true;
	std::unique_ptr<OWindow> m_display;

};