#pragma once

class OWindow
{

public:
	OWindow(); // Constructor
	~OWindow(); // Destructor

	void onDestroy();
	bool isClosed();

private:
	void* m_handle = nullptr;

};