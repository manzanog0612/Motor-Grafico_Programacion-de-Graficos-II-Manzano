#include "aabb.h"
#include "GLEW/glew.h"
#include <GLFW/glfw3.h>

namespace engine
{
	aabb::aabb()
	{
	}

	aabb::~aabb()
	{
	}

	void aabb::setBounds(vector<glm::vec3> vertices)
	{
		this->vertices = vertices;
	}

	void aabb::draw()
	{
	}
}