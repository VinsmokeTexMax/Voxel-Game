#pragma once
#include <memory>

class OVertexArrayObject;

typedef std::shared_ptr<OVertexArrayObject> OVertexArrayObjectPtr;

typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct OVertexBufferData
{
	void* VerticesList = nullptr;
	ui32 VertexSize = 0;
	ui32 listSize = 0;
};