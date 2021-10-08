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
	engine::sprite* sprite3;
	engine::sprite* sprite4;
	engine::sprite* megaman;
	engine::shape* triangle;
	engine::shape* quad;
	float megamanSpeed = 12.5f;
	int megamanRunAnimationID;
};
