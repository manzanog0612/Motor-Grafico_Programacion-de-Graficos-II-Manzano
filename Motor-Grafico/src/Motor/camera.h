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
		glm::vec3 pos; //donde esta parada
		glm::vec3 look; //a donde esta mirando
		glm::vec3 up; //el up de la camara
		renderer* currentRenderer;
	};

	//EJE X PITCH
	//EJE Y YAW
	//EJE Z ROLL

	// Camara en primera persona (FPS) y en tercera persona (Over the shoulder)

	//local - mundo - vista - perspectiva

	// Tarea
	// 1) hacer camara funcional
	// 2) fps y 3ra persona
}