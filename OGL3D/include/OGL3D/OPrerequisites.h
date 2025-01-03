#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

class OVertexArrayObject;
class OShaderProgram;	

typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;
typedef std::shared_ptr<OShaderProgram> OShaderProgramPtr;

typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct OvertexAttribute
{

	ui32 numElements = 0;
};

struct OVertexBufferDesc
{
	void* VerticesList = nullptr;
	ui32 VertexSize = 0;
	ui32 listSize = 0;

	OvertexAttribute* attributeList = nullptr;
	ui32 attributeListSize = 0;
};

struct OShaderProgramDesc
{
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

enum OShaderType
{
	VertexShader = 0,
	FragmentShader
};


#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;

#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;