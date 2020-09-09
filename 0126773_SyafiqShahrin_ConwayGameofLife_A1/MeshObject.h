#pragma once

class Shader;
struct Vector3;
struct Transform;



class MeshObject{
public:

private:
	//store mesh data
	
	GLfloat m_meshVertices[20] = {
		-1.0f, -1.0f, 0.0f, //position
		0.0f, 0.0f,  //Tex Coord
		-1.0f, 1.0f, 0.0f, //position
		0.0f, 1.0f,  //Tex Coord
		1.0f, -1.0f, 0.0f, //position
		1.0f, 0.0f, //Tex Coord
		1.0f, 1.0f, 0.0f, //position
		1.0f, 1.0f //Tex Coord
	};
	
	GLint m_vertexIndices[6] =
	{
		0, 1, 2,
		3, 2, 1
	};

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;


	void Init();

public:
	MeshObject();
	~MeshObject();
	//Draw mesh
	void DrawMesh();
	//Change Shader

};

