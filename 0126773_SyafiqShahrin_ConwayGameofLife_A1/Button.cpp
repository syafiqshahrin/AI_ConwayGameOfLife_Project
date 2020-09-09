#include <glad/glad.h>
#include <glfw3.h>
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "Shader.h"
#include "MeshObject.h"
#include "UIHandler.h"
#include "Button.h"



Button::Button()
{
	m_ButtonTransform = Transform();
	m_ButtonMesh = nullptr;
}
Button::Button(MeshObject* mesh, Shader* shader)
{
	m_ButtonTransform = Transform();
	m_ButtonMesh = mesh;
	m_meshShader = shader;
}
void Button::TranslateButton(Vector3 newPosition)
{
	m_ButtonTransform.Position = newPosition;
}
void Button::RotateButton()
{

}
void Button::ScaleButton(Vector3 newScale)
{
	m_ButtonTransform.Scale = newScale;
}
void Button::BindFunction(UIHandler* obj, void (UIHandler::*buttonFunction)())
{
	handler = obj;
	buttonFunctionPtr = buttonFunction;
}
bool Button::CheckInput(InputData& input)
{
	bool isClicked = false;
	float x1 = m_ButtonTransform.Position.x - (1.0f * m_ButtonTransform.Scale.x);
	float x2 = m_ButtonTransform.Position.x + (1.0f * m_ButtonTransform.Scale.x);

	float y1 = m_ButtonTransform.Position.y - (1.0f * m_ButtonTransform.Scale.y);
	float y2 = m_ButtonTransform.Position.y + (1.0f * m_ButtonTransform.Scale.y);
	if (input.mousePosition.x >= x1 && input.mousePosition.x <= x2)
	{
		if (input.mousePosition.y >= y1 && input.mousePosition.y <= y2)
		{
			isHover = true;
			//std::cout << "Inside Button Boundary" << std::endl;
			if (input.isLeftClicked)
			{
				isClicked = input.isLeftClicked;
				input.isLeftClicked = false;
				OnClick();
				//std::cout << "Button Clicked" << std::endl;
			}
		}
		else
		{
			isHover = false;
		}
	}
	else
	{
		isHover = false;
	}
	return isClicked;
}
void Button::OnClick()
{
	(handler->*(buttonFunctionPtr))();
}
void Button::DrawButton(GLuint texture)
{
	Matrix4 gOthorMatrix = Matrix4::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 30.0f);
	Matrix4 gViewMatrix = Matrix4::translate(Vector3(0.0f, 0.0f, -1.0f));
	m_meshShader->use();

	Matrix4 modelMatrix =
		Matrix4::translate(m_ButtonTransform.Position) *
		Matrix4::scale(m_ButtonTransform.Scale) *
		Matrix4::rotate(0.0f, m_ButtonTransform.Rotation);
	Matrix4 OrthoModelMatrix = gOthorMatrix * gViewMatrix * modelMatrix;
	m_meshShader->setMat4("uModelMatrix", modelMatrix.data);
	m_meshShader->setMat4("uOrthoModelMatrix", OrthoModelMatrix.data);
	m_meshShader->setInt("Main_Tex", 0);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	m_ButtonMesh->DrawMesh();
}