#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc)
{
	m_programID = glCreateProgram();
	attach(desc.VertexShaderPath, VertexShader);
	attach(desc.FragmentShaderPath, FragmentShader);
	link();
}

OShaderProgram::~OShaderProgram()
{
	for (ui32 i = 0; i < 2; i++)
	{
		glDetachShader(m_programID, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	glDeleteProgram(m_programID);
}

ui32 OShaderProgram::getID()
{
	return m_programID;
}

void OShaderProgram::attach(const wchar_t* shaderPath, const OShaderType& type)
{
	std::string shaderCode;
	std::ifstream shaderStream(shaderPath);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		OGL3D_WARNING("OShaderProgram | " << shaderPath << "not founded");
		return;
	}

	ui32 shaderID = 0;
	if (type == VertexShader)
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);


	// get compile errors
	i32 longlength = 0;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &longlength);
	if (longlength > 0)
	{
		std::vector<char> errorMessage(longlength + 1);
		glGetShaderInfoLog(shaderID, longlength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << shaderPath << " compiled with errors: " << std::endl << &errorMessage[0]);
		return;
	}

	glAttachShader(m_programID, shaderID);
	m_attachedShaders[type] = shaderID;

	OGL3D_INFO("OShaderProgram | " << shaderPath << " compiled successfully");
}

void OShaderProgram::link()
{
	glLinkProgram(m_programID);

	// get link errors
	i32 longlength = 0;
	glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &longlength);
	if (longlength > 0)
	{
		std::vector<char> errorMessage(longlength + 1);
		glGetShaderInfoLog(m_programID, longlength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << &errorMessage[0]);
		return;
	}
}
