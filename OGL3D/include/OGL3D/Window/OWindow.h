#pragma once

#include <OGL3D/Math/ORect.h>


class OWindow
{

public:
	OWindow(); // Constructor
	~OWindow(); // Destructor

	ORect getInnerSize();

	void makeCurrentContext();
	void present(bool vsync);

private:
	void* m_handle = nullptr;
	void* m_conext = nullptr;
};