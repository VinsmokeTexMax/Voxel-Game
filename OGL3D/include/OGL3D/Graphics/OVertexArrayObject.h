#pragma once
#include <OGL3D/OPrerequisites.h>


class OVertexArrayObject
{
	
public:

	OVertexArrayObject(const OVertexBufferDesc& data); // Constructor
	~OVertexArrayObject(); // Destructor

	ui32 getID();

	ui32 getVertexBufferSize();
	ui32 getVertexSize();


private:

	ui32 m_vertexBufferID = 0;
	ui32 m_vertexArrayObjectID = 0;
	OVertexBufferDesc m_vertexBufferData;
};

