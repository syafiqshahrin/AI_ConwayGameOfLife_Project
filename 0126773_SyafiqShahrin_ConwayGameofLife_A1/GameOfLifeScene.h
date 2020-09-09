#pragma once
#include "Scene.h"

class Shader;
class MeshObject;
class Entity;
class Button;
class UIHandler;

class GameOfLifeScene : Scene
{
public:
	GameOfLifeScene(int* wH, int* wW, double* dTime);
	~GameOfLifeScene();
	void DrawScene();
	void UpdateInput(InputData &input);
	void UpdateScene();
private:
	void Init();
	void LoadTextures();
	void LoadShaders();
	void CreateMeshes();
	void CreateEntities();
	//========Game Of Life Functions=============//
	void CheckCellMap(InputData& input);

	//========== Members ============//
	//Shaders
	Shader basicShader;
	Shader cellMapShaderRead;
	Shader cellMapShaderWrite;
	Shader cellMapShaderErase;
	Shader cellMapShaderAdd;
	Shader cellMapShaderUpdate;
	Shader uiDimensionBarShader;
	Shader uiTimestepBarShader;
	Shader uiPlayButtonShader;
	Shader basicColShader;

	//Meshes
	MeshObject* meshRectangle;

	//Textures
	GLuint textureID[9];
	GLuint cellTextureWrite;
	GLuint cellTextureWrite2;
	GLuint cellTextureRead;
	GLuint cellTextureTemp;
	GLuint cellTextureUpdate;


	//Entities
	Entity CellMap;
	Entity CellMapMain;

	Entity DimensionBar;
	Entity TimestepBar;
	Entity TimestepBarIcon;
	Entity DimensionBarIcon;
	Entity ButtonPanel;
	Entity BarPanel;
	Entity textPanel;
	Entity text1;

	//Buttons
	Button playButton;
	Button clearButton;
	Button increaseDimensionsButton;
	Button decreaseDimensionsButton;
	Button increaseTimeStepButton;
	Button decreaseTimeStepButton;

	//Cell Map Properties
	float cellDimension = 0.0f;
	bool isClicked = false;
	float leftMXPos = -1.0f;
	float leftMYPos = -1.0f;
	float rightMXPos = -1.0f;
	float rightMYPos = -1.0f;
	float timeStep = 0.0f;
	double currentTime = 0.0f;
	double*deltaTime;


	//
	UIHandler uiHandler;

	//
	GLuint CellFrameBuffer;
	GLuint CellDepthRenderBuffer;

	//Window details
	int* wHeight;
	int* wWidth;
	bool uiToggle = false;
	bool mouseInWindow = false;
	


};