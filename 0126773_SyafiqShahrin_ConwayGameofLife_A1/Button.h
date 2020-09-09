#pragma once
struct Transform;

class Button
{
public:
	Button();
	Button(MeshObject* mesh, Shader* shader);
	void TranslateButton(Vector3 newPosition);
	void RotateButton();
	void ScaleButton(Vector3 newScale);
	void DrawButton(GLuint texture);
	void BindFunction(UIHandler* obj, void (UIHandler::*buttonFunction)());
	bool CheckInput(InputData& input);
	void OnClick();
	void SetShader();
	//
	Transform m_ButtonTransform;
	MeshObject* m_ButtonMesh;
	Shader* m_meshShader;
	UIHandler* handler;
	bool isHover = false;
	//
	
private:
	void (UIHandler::*buttonFunctionPtr)();
};