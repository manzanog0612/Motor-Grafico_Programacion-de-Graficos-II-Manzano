#include "entity.h"

namespace engine
{
	entity::entity()
	{
		_renderer = NULL;

		v3pos = glm::vec3();
		v3rot = glm::vec3();
		v3scale = glm::vec3();

		model = glm::mat4();

		translate = glm::mat4();
		rotateX = glm::mat4();
		rotateY = glm::mat4();
		rotateZ = glm::mat4();
		scale = glm::mat4();

		color = glm::vec4(1, 1, 1, 1);

		updateModelMatrix();
	}

	entity::~entity()
	{

	}

	void entity::assingRenderer(renderer* _renderer)
	{
		this->_renderer = _renderer;
	}

	void entity::updateModelMatrix()
	{
		model = translate * rotateX * rotateY * rotateZ * scale;
	}

	void entity::setRotX(float x)
	{
		v3rot[0] = x;

		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
		updateModelMatrix();
	}

	void entity::setRotY(float y)
	{
		v3rot[1] = y;

		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
		updateModelMatrix();
	}

	void entity::setRotZ(float z)
	{
		v3rot[2] = z;

		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
		updateModelMatrix();
	}

	void entity::setScale(float x, float y, float z)
	{
		v3scale[0] = x;
		v3scale[1] = y;
		v3scale[2] = z;

		translate = glm::translate(glm::mat4(1.0f), v3pos);
		updateModelMatrix();
	}
	void entity::setColor(glm::vec4 newColor)
	{
		color = newColor;
	}
}