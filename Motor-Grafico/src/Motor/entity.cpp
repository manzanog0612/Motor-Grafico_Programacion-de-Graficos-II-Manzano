#include "entity.h"
//#include "renderer.h"

namespace engine
{
	entity::entity()
	{
		_renderer = NULL;
		model = glm::mat4(1.0f);
		localModel = glm::mat4(1.0f);
		translate = glm::mat4(1.0f);
		rotateX = glm::mat4(1.0f);
		rotateY = glm::mat4(1.0f);
		rotateZ = glm::mat4(1.0f);			
		scale = glm::mat4(1.0f);

		v3pos = glm::vec3(0.0f);
		v3rot = glm::vec3(0.0f);
		v3scale = glm::vec3(1.0f);

		updateModelMatrix();

		setColor(glm::vec4(1.0f));
	}

	entity::~entity()
	{

	}

	void entity::updateModelMatrix()
	{
		model = translate * rotateX * rotateY * rotateZ * scale;
	}
	void entity::setPos(glm::vec3 pos)
	{
		v3pos = pos;
		translate = glm::translate(glm::mat4(1.0f), v3pos);
		updateModelMatrix();
	}
	void entity::setPos(float x, float y, float z)
	{
		setPos(glm::vec3(x, y, z));
	}
	void entity::setRot(glm::vec3 rot)
	{
		setRotX(rot.x);
		setRotY(rot.y);
		setRotZ(rot.z);
		updateModelMatrix();
	}
	void entity::setRot(float x, float y, float z)
	{
		setRotX(x);
		setRotY(y);
		setRotZ(z);
		updateModelMatrix();
	}
	void entity::setRotX(float x)
	{
		v3rot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	}
	void entity::setRotY(float y)
	{
		v3rot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	}
	void entity::setRotZ(float z)
	{
		v3rot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	}
	void entity::setScale(glm::vec3 scale)
	{
		v3scale = scale;
		this->scale = glm::scale4(glm::mat4(1.0f), v3scale);
		updateModelMatrix();
	}
	void entity::setScale(float x, float y, float z)
	{
		setScale(glm::vec3(x, y, z));
	}
	void entity::setColor(glm::vec4 color)
	{
		this->color = color;
	}
	void entity::setColor(float r, float g, float b, float a)
	{
		color = glm::vec4(r, g, b, a);
	}
	void entity::setLocalModel(glm::mat4 localModel)
	{
		this->localModel = localModel;
	}
	void entity::setModel(glm::mat4 model)
	{
		float magnitude0 = glm::sqrt(model[0].x * model[0].x + model[0].y * model[0].y + model[0].z * model[0].z);
		float magnitude1 = glm::sqrt(model[1].x * model[1].x + model[1].y * model[1].y + model[1].z * model[1].z);
		float magnitude2 = glm::sqrt(model[2].x * model[2].x + model[2].y * model[2].y + model[2].z * model[2].z);

		setPos(model[3]);
		model[3].x = 0;
		model[3].y = 0;
		model[3].z = 0;
		setScale(glm::vec3(magnitude0, magnitude1, magnitude2));

		float theta1 = glm::atan(model[2].y, model[2].z);
		float c2 = glm::sqrt(model[0].x * model[0].x + model[1].x * model[1].x);
		float theta2 = glm::atan(-model[2].x, c2);
		float s1 = glm::sin(theta1);
		float c1 = glm::cos(theta1);
		float theta3 = glm::atan(s1 * model[0].z - c1 * model[0].y, c1 * model[1].y - s1 * model[1].z);
		glm::vec3 rotation = { -theta1, -theta2, -theta3 };

		setRot(rotation);

		this->model = model;
	}
	glm::vec4 entity::getColor()
	{
		return color;
	}
	glm::vec3 entity::getPos()
	{
		return v3pos;
	}
	glm::vec3 entity::getRot()
	{
		return v3rot;
	}
	glm::vec3 entity::getScale()
	{
		return v3scale;
	}
	glm::mat4 entity::getModel()
	{
		return model;
	}
	glm::mat4 entity::getLocalModel()
	{
		return localModel;
	}
	void entity::invertX()
	{
		setRotY(-3.14169265f);
		updateModelMatrix();
	}
	void entity::invertY()
	{
		setRotZ(-3.14169265f);
		updateModelMatrix();
	}
	void entity::invertZ()
	{
		setRotX(-3.14169265f);
		updateModelMatrix();
	}
}