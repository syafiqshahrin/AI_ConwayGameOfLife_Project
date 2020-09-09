#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Utility.h"
#include "MeshObject.h"
#include "UIHandler.h"
#include "Entity.h"
#include "UIHandler.h"
#include "Button.h"
#include "GameOfLifeScene.h"

GameOfLifeScene::GameOfLifeScene(int *wH, int *wW, double* dTime)
{
	wHeight = wH;
	wWidth = wW;
	deltaTime = dTime;
	Init();
}

GameOfLifeScene::~GameOfLifeScene()
{
	
	delete meshRectangle;
	glDeleteTextures(9, textureID);
	glDeleteFramebuffers(1, &CellFrameBuffer);
	glDeleteTextures(1, &cellTextureWrite);
	glDeleteTextures(1, &cellTextureWrite2);
	glDeleteTextures(1, &cellTextureRead);
	glDeleteTextures(1, &cellTextureTemp);
	glDeleteTextures(1, &cellTextureUpdate);
	std::cout << "Game Scene destructor called" << std::endl;

}

void GameOfLifeScene::Init()
{

	LoadShaders();
	LoadTextures();
	CreateMeshes();
	CreateEntities();
	cellDimension = uiHandler.cellMapDimension;
	timeStep = uiHandler.timeStep;
}

void GameOfLifeScene::LoadShaders()
{
	//std::cout << "Load Shader called" << std::endl;

	basicShader = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/BasicVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/BasicFrag.frag");
	cellMapShaderWrite = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapFrag.frag");
	cellMapShaderRead = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapReadVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapReadFrag.frag");
	cellMapShaderAdd = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapAddVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapAddFrag.frag");
	cellMapShaderUpdate = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapUpdateVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapUpdateFrag.frag");
	cellMapShaderErase = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapEraseVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/CellMapEraseFrag.frag");
	uiDimensionBarShader = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/DimensionBarShaderVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/DimensionBarShaderFrag.frag");
	uiTimestepBarShader = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/TimestepBarShaderVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/TimestepBarShaderFrag.frag");
	uiPlayButtonShader = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/uiPlayVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/uiPlayFrag.frag");
	basicColShader = Shader("../0126773_SyafiqShahrin_ConwayGameofLife_A1/basicColVert.vert", "../0126773_SyafiqShahrin_ConwayGameofLife_A1/basicColFrag.frag");

}

void GameOfLifeScene::LoadTextures()
{
	
	glGenFramebuffers(1, &CellFrameBuffer);

	glGenTextures(1, &cellTextureWrite);

	glBindTexture(GL_TEXTURE_2D, cellTextureWrite);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *wWidth, *wHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &cellTextureWrite2);

	glBindTexture(GL_TEXTURE_2D, cellTextureWrite2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *wWidth, *wHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &cellTextureRead);

	glBindTexture(GL_TEXTURE_2D, cellTextureRead);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *wWidth, *wHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &cellTextureTemp);

	glBindTexture(GL_TEXTURE_2D, cellTextureTemp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *wWidth, *wHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &cellTextureUpdate);

	glBindTexture(GL_TEXTURE_2D, cellTextureUpdate);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *wWidth, *wHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



	glGenTextures(9, textureID);
	Utility::loadTexturePNG("../Media/testPlay1.png", textureID[0]);
	Utility::loadTexturePNG("../Media/testClear3.png", textureID[1]);
	Utility::loadTexturePNG("../Media/testIncreaseDimension2.png", textureID[2]);
	Utility::loadTexturePNG("../Media/testDecreaseDimension2.png", textureID[3]);
	Utility::loadTexturePNG("../Media/testincreasetimestep1.png", textureID[4]);
	Utility::loadTexturePNG("../Media/testdecreasetime1.png", textureID[5]);
	Utility::loadTexturePNG("../Media/testgridicon1.png", textureID[6]);
	Utility::loadTexturePNG("../Media/testtimeicon1.png", textureID[7]);
	Utility::loadTexturePNG("../Media/textUI1.png", textureID[8]);


}

void GameOfLifeScene::CreateMeshes()
{
	meshRectangle = new MeshObject();
}

void GameOfLifeScene::CreateEntities()
{
	CellMap = Entity(meshRectangle, &cellMapShaderWrite);
	CellMap.ScaleEntity(Vector3(1.0f, 1.0f, 1.0f));
	CellMap.TranslateEntity(Vector3(0.0f, 0.0f, 0.0f));

	CellMapMain = Entity(meshRectangle, &cellMapShaderRead);
	CellMapMain.ScaleEntity(Vector3(1.0f, 1.0f, 1.0f));
	CellMapMain.TranslateEntity(Vector3(0.0f, 0.0f, 0.0f));

	DimensionBar = Entity(meshRectangle, &uiDimensionBarShader);
	DimensionBar.ScaleEntity(Vector3(0.05f, 0.02f, 0.1f));
	DimensionBar.TranslateEntity(Vector3(0.6f, 0.9f, 0.0f));

	TimestepBar = Entity(meshRectangle, &uiTimestepBarShader);
	TimestepBar.ScaleEntity(Vector3(0.05f, 0.02f, 0.1f));
	TimestepBar.TranslateEntity(Vector3(0.8f, 0.9f, 0.0f));

	TimestepBarIcon = Entity(meshRectangle, &basicShader);
	TimestepBarIcon.ScaleEntity(Vector3(0.02f, 0.025f, 0.1f));
	TimestepBarIcon.TranslateEntity(Vector3(0.72f, 0.895f, 0.0f));

	DimensionBarIcon = Entity(meshRectangle, &basicShader);
	DimensionBarIcon.ScaleEntity(Vector3(0.01f, 0.02f, 0.1f));
	DimensionBarIcon.TranslateEntity(Vector3(0.53f, 0.9f, 0.0f));

	ButtonPanel = Entity(meshRectangle, &basicColShader);
	ButtonPanel.ScaleEntity(Vector3(0.065f, 0.45f, 1.0f));
	ButtonPanel.TranslateEntity(Vector3(-0.845f, 0.22f, 0.0f));

	BarPanel = Entity(meshRectangle, &basicColShader);
	BarPanel.ScaleEntity(Vector3(0.2f, 0.04f, 1.0f));
	BarPanel.TranslateEntity(Vector3(0.69f, 0.9f, 0.0f));

	textPanel = Entity(meshRectangle, &basicColShader);
	textPanel.ScaleEntity(Vector3(0.175f, 0.04f, 1.0f));
	textPanel.TranslateEntity(Vector3(0.0, -0.85f, 0.0f));

	text1 = Entity(meshRectangle, &basicShader);
	text1.ScaleEntity(Vector3(0.15f, 0.04f, 1.0f));
	text1.TranslateEntity(Vector3(0.0, -0.85f, 0.0f));

	playButton = Button(meshRectangle, &uiPlayButtonShader);
	playButton.ScaleButton(Vector3(0.05f, 0.05f, 0.05f));
	playButton.TranslateButton(Vector3(-0.85f, 0.6f, 0.0f));
	playButton.BindFunction(&uiHandler, &UIHandler::Play);

	clearButton = Button(meshRectangle, &basicShader);
	clearButton.ScaleButton(Vector3(0.05f, 0.05f, 0.05f));
	clearButton.TranslateButton(Vector3(-0.85f, 0.45f, 0.0f));
	clearButton.BindFunction(&uiHandler, &UIHandler::Clear);

	increaseDimensionsButton = Button(meshRectangle, &basicShader);
	increaseDimensionsButton.ScaleButton(Vector3(0.05f, 0.05f, 0.05f));
	increaseDimensionsButton.TranslateButton(Vector3(-0.85f, 0.3f, 0.0f));
	increaseDimensionsButton.BindFunction(&uiHandler, &UIHandler::IncreaseCellMapDimensions);

	decreaseDimensionsButton = Button(meshRectangle, &basicShader);
	decreaseDimensionsButton.ScaleButton(Vector3(0.05f, 0.05f, 0.05f));
	decreaseDimensionsButton.TranslateButton(Vector3(-0.85f, 0.15f, 0.0f));
	decreaseDimensionsButton.BindFunction(&uiHandler, &UIHandler::DecreaseCellMapDimensions);

	increaseTimeStepButton = Button(meshRectangle, &basicShader);
	increaseTimeStepButton.ScaleButton(Vector3(0.05f, 0.05f, 0.05f));
	increaseTimeStepButton.TranslateButton(Vector3(-0.85f, 0.0f, 0.0f));
	increaseTimeStepButton.BindFunction(&uiHandler, &UIHandler::IncreaseTimeStep);

	decreaseTimeStepButton = Button(meshRectangle, &basicShader);
	decreaseTimeStepButton.ScaleButton(Vector3(0.05f, 0.05f, 0.05f));
	decreaseTimeStepButton.TranslateButton(Vector3(-0.85f, -0.15f, 0.0f));
	decreaseTimeStepButton.BindFunction(&uiHandler, &UIHandler::DecreaseTimeStep);


}
void GameOfLifeScene::CheckCellMap(InputData& input)
{
	
	float x1 = CellMap.m_EntityTransform.Position.x - (1.0f * CellMap.m_EntityTransform.Scale.x);
	float x2 = CellMap.m_EntityTransform.Position.x + (1.0f * CellMap.m_EntityTransform.Scale.x);

	float y1 = CellMap.m_EntityTransform.Position.y - (1.0f * CellMap.m_EntityTransform.Scale.y);
	float y2 = CellMap.m_EntityTransform.Position.y + (1.0f * CellMap.m_EntityTransform.Scale.y);
	if (input.mousePosition.x >= x1 && input.mousePosition.x <= x2)
	{
		if (input.mousePosition.y >= y1 && input.mousePosition.y <= y2)
		{
			float totalRange = (x2 - x1);
			float xP = (input.mousePosition.x - CellMap.m_EntityTransform.Position.x) + (x2 - CellMap.m_EntityTransform.Position.x);
			float yP = (input.mousePosition.y - CellMap.m_EntityTransform.Position.y) + (y2 - CellMap.m_EntityTransform.Position.y);

			xP = (xP / totalRange);
			yP = (yP / totalRange);

			
			//std::cout << "cellCoordX: " << xP << " ,cellCoordY: " << yP << std::endl;
			if (input.isLeftClicked)
			{
				isClicked = input.isLeftClicked;
				//CellMap.m_meshShader->setInt("Clicked", isClicked);
				leftMXPos = xP;
				leftMYPos = yP;
				//std::cout << "Left Clicked inside cell map" << std::endl;
			}
			if(input.isRightClicked)
			{
				isClicked = input.isRightClicked;
				//CellMap.m_meshShader->setInt("Clicked", isClicked);
				rightMXPos = xP;
				rightMYPos = yP;
				//std::cout << "Right Clicked inside cell map" << std::endl;
			}
	

		}
	
	}

	
}
void GameOfLifeScene::UpdateInput(InputData &input)
{
	mouseInWindow = input.mouseInWindow;
	uiToggle = input.uiKeyToggle;
	if (uiToggle)
	{
		playButton.CheckInput(input);
		clearButton.CheckInput(input);
		increaseDimensionsButton.CheckInput(input);
		decreaseDimensionsButton.CheckInput(input);
		increaseTimeStepButton.CheckInput(input);
		decreaseTimeStepButton.CheckInput(input);
	}

	CheckCellMap(input);
}
void GameOfLifeScene::UpdateScene()
{
	currentTime += *deltaTime;
	//
	cellDimension = uiHandler.cellMapDimension;
	//
	timeStep = uiHandler.timeStep;
	//
	cellMapShaderWrite.use();
	cellMapShaderWrite.setFloat("Dimension", cellDimension);
	cellMapShaderWrite.setFloat("wHeight", *wHeight);
	cellMapShaderWrite.setFloat("wWidth", *wWidth);
	cellMapShaderWrite.setFloat("mouseX", leftMXPos);
	cellMapShaderWrite.setFloat("mouseY", leftMYPos);
	leftMXPos = -1.0f;
	leftMYPos = -1.0f;
	//
	cellMapShaderErase.use();
	cellMapShaderErase.setFloat("Dimension", cellDimension);
	cellMapShaderErase.setFloat("wHeight", *wHeight);
	cellMapShaderErase.setFloat("wWidth", *wWidth);
	cellMapShaderErase.setFloat("mouseX", rightMXPos);
	cellMapShaderErase.setFloat("mouseY", rightMYPos);
	rightMXPos = -1.0f;
	rightMYPos = -1.0f;
	//
	cellMapShaderAdd.use();
	cellMapShaderAdd.setFloat("Dimension", cellDimension);
	cellMapShaderAdd.setFloat("wHeight", *wHeight);
	cellMapShaderAdd.setFloat("wWidth", *wWidth);
	//
	uiDimensionBarShader.use();
	uiDimensionBarShader.setFloat("Percentage", (cellDimension/600.0f));

	uiTimestepBarShader.use();
	uiTimestepBarShader.setFloat("Percentage", (timeStep / 0.2f));

	//
	if (uiHandler.isPlaying)
	{
		if (currentTime >= timeStep)
		{
			currentTime = 0.0f;
			cellMapShaderUpdate.use();
			cellMapShaderUpdate.setFloat("Dimension", cellDimension);
			cellMapShaderUpdate.setFloat("wHeight", *wHeight);
			cellMapShaderUpdate.setFloat("wWidth", *wWidth);
			//std::cout << "Is playing" << std::endl;

			//Read from cellMapTextureRead
			//Check data and write to new texture (cellMapTextureUpdate)
			//copy cellMapTextureUpdate to cellMapTextureRead
			glBindFramebuffer(GL_FRAMEBUFFER, CellFrameBuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cellTextureUpdate, 0);
			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (status == GL_FRAMEBUFFER_COMPLETE)
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				CellMap.UseIdentityMatrix(true);
				CellMap.SetShader(&cellMapShaderUpdate);
				CellMap.DrawEntity(cellTextureRead);
			}
			else
			{
				printf("frame buffer is not ready!\n");
			}
			glCopyImageSubData(cellTextureUpdate, GL_TEXTURE_2D, 0, 0, 0, 0, cellTextureRead, GL_TEXTURE_2D, 0, 0, 0, 0, *wWidth, *wHeight, 1);
		}
		
	}
	if (uiHandler.clearMap)
	{
		uiHandler.clearMap = false;
		uiHandler.isPlaying = false;
		cellMapShaderWrite.use();
		cellMapShaderWrite.setFloat("Dimension", cellDimension);
		cellMapShaderWrite.setFloat("wHeight", *wHeight);
		cellMapShaderWrite.setFloat("wWidth", *wWidth);
		cellMapShaderWrite.setFloat("mouseX", -1.0f);
		cellMapShaderWrite.setFloat("mouseY", -1.0f);
		std::cout << "Map Cleared" << std::endl;
		
		glBindFramebuffer(GL_FRAMEBUFFER, CellFrameBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cellTextureUpdate, 0);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status == GL_FRAMEBUFFER_COMPLETE)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			CellMap.UseIdentityMatrix(true);
			CellMap.SetShader(&cellMapShaderWrite);
			CellMap.DrawEntity(0);
		}
		else
		{
			printf("frame buffer is not ready!\n");
		}
		glCopyImageSubData(cellTextureUpdate, GL_TEXTURE_2D, 0, 0, 0, 0, cellTextureRead, GL_TEXTURE_2D, 0, 0, 0, 0, *wWidth, *wHeight, 1);
	}
	uiPlayButtonShader.use();
	uiPlayButtonShader.setInt("IsPlaying", uiHandler.isPlaying);
	uiPlayButtonShader.setInt("IsHovered", playButton.isHover);
	uiPlayButtonShader.setFloat("Time", glfwGetTime());

	
}
void GameOfLifeScene::DrawScene()
{
	//Render to cellTextureWrite for input
	//Render to cellTextureWrite2 with (cellTextureWrite + cellTextureRead)
	//Copy cellTextureWrite2 to cellTextureRead
	//Render to screen

	glBindFramebuffer(GL_FRAMEBUFFER, CellFrameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cellTextureWrite, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CellMap.UseIdentityMatrix(true);
		CellMap.SetShader(&cellMapShaderWrite);
		CellMap.DrawEntity(0);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	
	//====================//

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cellTextureTemp, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CellMap.UseIdentityMatrix(true);
		CellMap.SetShader(&cellMapShaderErase);
		CellMap.DrawEntity(0);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	
	//====================//

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cellTextureWrite2, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		CellMap.UseIdentityMatrix(true);
		CellMap.SetShader(&cellMapShaderAdd);
		CellMap.DrawEntity(cellTextureWrite, cellTextureTemp, cellTextureRead);
	}
	else
	{
		printf("frame buffer is not ready!\n");
	}
	//====================//
	glCopyImageSubData(cellTextureWrite2, GL_TEXTURE_2D, 0, 0, 0, 0, cellTextureRead, GL_TEXTURE_2D, 0, 0, 0, 0, *wWidth, *wHeight, 1);
	//====================//
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Render Cell Map
	CellMapMain.DrawEntity(cellTextureRead);
	if (uiToggle)
	{
		//Panel
		basicColShader.use();
		ButtonPanel.DrawEntity(0);
		//basicColShader.use();
		BarPanel.DrawEntity(0);
	
		//Render UI
		playButton.DrawButton(textureID[0]);
		basicShader.use();
		basicShader.setInt("IsHovered", clearButton.isHover);
		clearButton.DrawButton(textureID[1]);
		//basicShader.use();
		basicShader.setInt("IsHovered", increaseDimensionsButton.isHover);
		increaseDimensionsButton.DrawButton(textureID[2]);
		//basicShader.use();
		basicShader.setInt("IsHovered", decreaseDimensionsButton.isHover);
		decreaseDimensionsButton.DrawButton(textureID[3]);
		//basicShader.use();
		basicShader.setInt("IsHovered", increaseTimeStepButton.isHover);
		increaseTimeStepButton.DrawButton(textureID[4]);
		//basicShader.use();
		basicShader.setInt("IsHovered", decreaseTimeStepButton.isHover);
		decreaseTimeStepButton.DrawButton(textureID[5]);
		//basicShader.use();
		basicShader.setInt("IsHovered", 0);
		DimensionBar.DrawEntity(0);
		TimestepBar.DrawEntity(0);
		DimensionBarIcon.DrawEntity(textureID[6]);
		TimestepBarIcon.DrawEntity(textureID[7]);
	}
	else
	{
		if (!mouseInWindow)
		{
			basicColShader.use();
			textPanel.DrawEntity(0);
			basicShader.use();
			text1.DrawEntity(textureID[8]);
		}

	}



}

