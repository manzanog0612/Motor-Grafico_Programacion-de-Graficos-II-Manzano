#include "camera.h"
#include "renderer.h"

namespace engine
{
	camera::camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		this->currentRenderer = currentRenderer;

		//TODO agregar propiedades/posibilidad de camara ortogonal
		projectionMatrix = glm::perspective(glm::radians(90.0f), (float)currentRenderer->getCurrentWindow()->getWidth() / (float)currentRenderer->getCurrentWindow()->getHeight(), 0.1f, 500.0f);
		this->currentRenderer->setProjectionMatrix(projectionMatrix);
		setCameraTransform(position, lookPosition, upVector);
	}
	void camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		pos = startingPosition;
		look = lookPosition;
		up = upVector;
		viewMatrix = glm::lookAt(startingPosition, lookPosition, upVector);
		currentRenderer->setViewMatrix(viewMatrix);
	}
	void camera::moveCamera(glm::vec3 movePosition)
	{
		pos += movePosition;
		look += movePosition;
		setCameraTransform(pos, look, up);
	}
	camera::~camera()
	{

	}
}