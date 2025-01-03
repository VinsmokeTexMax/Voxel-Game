#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVertexBufferDesc& data)
{
	if (!data.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL");
	if (!data.VertexSize) OGL3D_ERROR("OVertexArrayObject | VertexSize is NULL");
	if (!data.VerticesList) OGL3D_ERROR("OVertexArrayObject | VerticesList is NULL");


	glGenVertexArrays(1, &m_vertexArrayObjectID);
	glBindVertexArray(m_vertexArrayObjectID);

	glGenBuffers(1, &m_vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.VertexSize * data.listSize,data.VerticesList, GL_STATIC_DRAW);

	for (ui32 i = 0; i < data.attributeListSize; i++)
	{
		glVertexAttribPointer(
			i, 
			data.attributeList[i].numElements,
			GL_FLOAT, 
			GL_FALSE, 
			data.VertexSize,
			(void*)((i==0) ? 0 : data.attributeList[i-1].numElements*sizeof(f32))
		);

		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);

	m_vertexBufferData = data;
}

OVertexArrayObject::~OVertexArrayObject()
{
	glDeleteBuffers(1, &m_vertexBufferID);
	glDeleteVertexArrays(1, &m_vertexArrayObjectID);
}

ui32 OVertexArrayObject::getID()
{
	return m_vertexArrayObjectID;
}

ui32 OVertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

ui32 OVertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.VertexSize;
}
