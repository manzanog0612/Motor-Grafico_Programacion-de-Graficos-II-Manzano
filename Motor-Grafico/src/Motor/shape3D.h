#pragma once
#include "exports.h"
#include "entity3D.h"

namespace engine
{
	enum shapeType {cube, other};

	class ENGINE_API shape3D : public entity3D
	{
	public:
		shape3D(renderer* render, shapeType shape);
		~shape3D();
		void draw() override;
	private:
		void setShader();
	};
}