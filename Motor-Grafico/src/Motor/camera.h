#pragma once
#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{
	class renderer;

	class ENGINE_API camera
	{
	public:
		camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector);
		void setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
		void moveCamera(glm::vec3 movePosition);
		~camera();
	private:
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec3 pos;
		glm::vec3 look;
		glm::vec3 up;
		renderer* currentRenderer;
	};
}