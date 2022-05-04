#include "spotLight.h"
#include "renderer.h"

namespace engine
{
	spotLight::spotLight()
	{
		
	}
	spotLight::spotLight(renderer* render)
	{
		VAO = 0;
		_renderer = render;

		model = glm::mat4(1.0f);
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

		setInitialValues();
	}
	spotLight::~spotLight()
	{
	}
	void spotLight::setInitialValues()
	{
		values.ambient = { 0.0f, 0.0f, 0.0f };
		values.diffuse = { 1.0f, 1.0f, 1.0f };
		values.specular = { 1.0f, 1.0f, 1.0f };

		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;

		direction = { 0.0f, -1.0f, 0.0f };

		cutOff = glm::cos(glm::radians(12.5f));
		outerCutOff = glm::cos(glm::radians(15.0f));
	}
	void spotLight::setDirection(glm::vec3 direction, bool normalized)
	{
		if (normalized)
		{
			this->direction = direction;
		}
		else
		{
			this->direction = { direction.x / 180, direction.y / 180, direction.z / 180 };
		}
	}
	void spotLight::processIndividualValues()
	{
		values.color = { getColor().r, getColor().g, getColor().b };
		_renderer->processSpotLight(direction, constant, linear, quadratic, getPos(), values, cutOff, outerCutOff);
	}
}
