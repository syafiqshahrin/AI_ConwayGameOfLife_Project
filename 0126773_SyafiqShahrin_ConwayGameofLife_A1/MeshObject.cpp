#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "Shader.h"
#include "MeshObject.h"


MeshObject:: MeshObject()
{
	Init();
}



void MeshObject::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_meshVertices), m_meshVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_vertexIndices), m_vertexIndices, GL_STATIC_DRAW);

	//linking vertex attribute for vertex pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//linking vertex attribute for vertex color
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(0 + 3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//unbinding the buffers
	glBindVertexArray(0);
	//unbind vertex array first before unbind the element buffer/vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

void MeshObject::DrawMesh()
{

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

MeshObject::~MeshObject()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
