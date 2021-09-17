#include "entity.h"

namespace engine
{
	entity::entity()
	{

	}

	entity::~entity()
	{

	}

	void entity::UpdateModelMatrix()
	{
		model = translate * rotateX * rotateY * rotateZ * scale;
	}

	void entity::SetRotX(float x)
	{
		v3rot[0] = x;

		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
		UpdateModelMatrix();
	}

	void entity::SetRotY(float y)
	{
		v3rot[1] = y;

		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
		UpdateModelMatrix();
	}

	void entity::SetRotZ(float z)
	{
		v3rot[2] = z;

		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
		UpdateModelMatrix();
	}

	void entity::SetScale(float x, float y, float z)
	{
		v3scale[0] = x;
		v3scale[1] = y;
		v3scale[2] = z;

		translate = glm::translate(glm::mat4(1.0f), v3pos);
		UpdateModelMatrix();
	}
}