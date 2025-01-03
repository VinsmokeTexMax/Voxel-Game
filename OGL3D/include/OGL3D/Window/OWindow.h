#pragma once

class OWindow
{

public:
	OWindow(); // Constructor
	~OWindow(); // Destructor

	void makeCurrentContext();
	void present(bool vsync);

private:
	void* m_handle = nullptr;
	void* m_conext = nullptr;
};