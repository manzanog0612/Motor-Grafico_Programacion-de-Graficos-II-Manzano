#pragma once
#include "Motor/baseGame.h"

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
	bool flashingColorsScreen = false;
	bool showingBoth = false;
	engine::shape* quad;
	engine::shape* triangle;
	engine::shape* activeShape;
	engine::sprite* sprite;
	float movementSpeed;
	float rotationSpeed;
};
