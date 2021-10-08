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
	int currentColorIndex2 = 0;
	glm::vec4 nextColor;
	glm::vec4 nextColor2;
	glm::vec4 colors[colorsArraySize];
	float t = 0;
	float rotationSpeed = 0;
	float timeBetweenChanges = 0;
	engine::sprite* sprite;
	engine::sprite* sprite2;
};
