#include "camera.h"
#include "renderer.h"

namespace engine
{
	camera::camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType)
	{
		this->currentRenderer = currentRenderer;
		movementType = MOVEMENT_TYPE::FPS;
		yaw = -90.0f;

		setProjetion(projectionType);

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
	void camera::moveCameraFoward(float movementAmount)
	{
		look += movementAmount * glm::normalize(look);
		pos += movementAmount * glm::normalize(look);
		setCameraTransform(pos, look, up);
	}
	void camera::setCameraType(MOVEMENT_TYPE movementType)
	{
		this->movementType = movementType;
	}
	void camera::rotateCamera(glm::vec2 offSet)
	{
		yaw += offSet.x;
		pitch += offSet.y;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		look = glm::normalize(direction);

		setCameraTransform(pos, look, up);
	}
	void camera::setView(glm::vec3 lookPosition)
	{
		look = lookPosition;
		viewMatrix = glm::lookAt(pos, lookPosition, up);
		currentRenderer->setViewMatrix(viewMatrix);
	}
	void camera::setProjetion(PROJECTION projectionType)
	{
		switch (projectionType)
		{
		case engine::PROJECTION::ORTHO:
			projectionMatrix = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 500.0f);
			break;
		case engine::PROJECTION::PERSPECTIVE:
			//fov - aspect ratio - near != 0 (porque si no genera problemas) - far
			projectionMatrix = glm::perspective(glm::radians(45.0f), (float)currentRenderer->getCurrentWindow()->getWidth() / (float)currentRenderer->getCurrentWindow()->getHeight(), 0.1f, 500.0f);
			break;
		default:
			projectionMatrix = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 500.0f);
			break;
		}
	}
	camera::~camera()
	{

	}
}