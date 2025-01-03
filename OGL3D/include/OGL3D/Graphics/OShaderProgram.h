#pragma once

#include <OGL3D/OPrerequisites.h>

class OShaderProgram
{

public:

	OShaderProgram(const OShaderProgramDesc& desc);
	~OShaderProgram();
	ui32 getID();

private:
	void attach(const wchar_t* shaderPath, const OShaderType& type);
	void link();

private:
	ui32 m_programID = 0;
	ui32 m_attachedShaders[2] = {};
};

