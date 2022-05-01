#pragma once
#include "Motor/baseGame.h"

const int colorsArraySize = 8;

class game : public engine::baseGame
{
public:
	game();
	~game();
	void update() override;
	void draw() override;
	void init() override;
	void deInit() override;

private:
	int currentColorIndex = 0;
	glm::vec4 nextColor;
	glm::vec4 colors[colorsArraySize];
	float t = 0;
	float rotationSpeed = 0;
	float timeBetweenChanges = 0;
	//engine::sprite* imageCampus;
	engine::sprite* floor;
	engine::sprite* container[6];
	engine::shape* lightBox;
	engine::sprite* conteiner2;
	engine::pointLight* pointLight[4];
	engine::directionalLight* directionalLight;
	//engine::pointLight* lightSourse;
	engine::shape* cubeEmerald;
	engine::shape* cubePearl;
	engine::shape* cubeBronze;
	engine::shape* cubeGold;
	engine::shape* cubeCyanPlastic;
	engine::shape* cubeRedPlastic;
	engine::shape* cubeGreenRubber;
	engine::shape* cubeYellowRubber;
	//engine::sprite* archer;
	//engine::shape* triangle;
	//engine::shape* triangle2;
	//engine::shape* triangle3;
	//engine::shape* quad;
	engine::camera* actualCam;
	engine::firstPersonCamera* firstPersonCam;
	engine::thirdPersonCamera* thirdPersonCam;
	//engine::tileMap* tileMap;
	float cameraSpeed = 30.f;
	glm::vec3 boxPos = glm::vec3(0, 0, 0);
	//int archerRunLeftAnimationID;
	//int archerRunRightAnimationID;
	//int archerRunUpAnimationID;
	//int archerRunUpLeftAnimationID;
	//int archerRunUpRightAnimationID;
	//int archerRunDownAnimationID;
	//int archerRunDownLeftAnimationID;
	//int archerRunDownRightAnimationID;
	//float runSpeed = 50;
};
