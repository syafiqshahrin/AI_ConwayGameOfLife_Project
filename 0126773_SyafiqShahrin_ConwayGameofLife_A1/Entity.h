#pragma once

//struct Transform;

class Entity
{
public:
	Entity();
	Entity(MeshObject* mesh, Shader* shader);
	void TranslateEntity(Vector3 newPosition);
	void RotateEntity();
	void ScaleEntity(Vector3 newScale);
	void DrawEntity(GLuint texture);
	void DrawEntity(GLuint texture, GLuint texture2); 
	void DrawEntity(GLuint texture, GLuint texture2, GLuint texture3);
	void SetShader(Shader* shader);
	void UseIdentityMatrix(bool identity);
	//
	Transform m_EntityTransform;
	MeshObject* m_EntityMesh;
	Shader* m_meshShader;
	bool useIdentity;
};