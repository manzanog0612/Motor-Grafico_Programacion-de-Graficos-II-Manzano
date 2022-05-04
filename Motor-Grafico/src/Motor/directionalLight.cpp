#include "directionalLight.h"
#include "renderer.h"

namespace engine
{
	directionalLight::directionalLight(renderer* render)
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

		values.ambient = glm::vec3(0.2f);
		values.diffuse = glm::vec3(0.5f);
		values.specular = glm::vec3(1);

		setInitialValues();
	}
	void directionalLight::setInitialValues()
	{
		values.ambient = { 0.05f, 0.05f, 0.05f };
		values.diffuse = { 0.4f, 0.4f, 0.4f };
		values.specular = { 0.5f, 0.5f, 0.5f };

		direction = { -1.0f, -1.0f, -1.0f };
	}
	void directionalLight::processIndividualValues()
	{

		values.color = { getColor().r, getColor().g, getColor().b };
		_renderer->processDirectionalLight(direction, values);
	}
	void directionalLight::setDirection(glm::vec3 direction, bool normalized)
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
}
