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
	engine::sprite* imageCampus;
	engine::sprite* container;
	engine::sprite* awesomeface;
	engine::sprite* archer;
	engine::shape* triangle;
	engine::shape* triangle2;
	engine::shape* triangle3;
	engine::shape* quad;
	engine::camera* cam;
	float cameraSpeed = 10.f;

	int archerRunLeftAnimationID;
	int archerRunRightAnimationID;
	int archerRunUpAnimationID;
	int archerRunUpLeftAnimationID;
	int archerRunUpRightAnimationID;
	int archerRunDownAnimationID;
	int archerRunDownLeftAnimationID;
	int archerRunDownRightAnimationID;
	float runSpeed = 12.5f;
};
