#include "camera.h"
#include "renderer.h"

namespace engine
{
	camera::camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType)
	{
		this->currentRenderer = currentRenderer;
		movementType = MOVEMENT_TYPE::THIRD_PERSON;
		yaw = -90.0f;
		pitch = 0.f;
		distace = 50;

		localPos = glm::vec3(0, 0, 0);
		targetPos = glm::vec3(0, 0, 0);

		setProjetion(projectionType);

		this->currentRenderer->setProjectionMatrix(projectionMatrix);
		setCameraTransform(position, lookPosition, upVector);
	}
	void camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		pos = startingPosition;
		look = lookPosition;
		up = upVector;
		viewMatrix = glm::lookAt(startingPosition, pos + lookPosition, upVector);
		currentRenderer->setViewMatrix(viewMatrix);
	}
	void camera::moveCamera(glm::vec3 movePosition)
	{
		pos += movePosition;
		look += movePosition;
		setCameraTransform(pos, look, up);
	}
	
	void camera::moveCamera(float movementAmount, MOVEMENT_DIRECTION movementDirection)
	{
		switch (movementDirection)
		{
		case engine::MOVEMENT_DIRECTION::FRONT:
			pos += movementAmount * glm::normalize(look);
			break;
		case engine::MOVEMENT_DIRECTION::BACK:
			pos -= movementAmount * glm::normalize(look);
			break;
		case engine::MOVEMENT_DIRECTION::RIGHT:
			pos += glm::normalize(glm::cross(glm::normalize(look), glm::normalize(up))) * movementAmount;
			break;
		case engine::MOVEMENT_DIRECTION::LEFT:
			pos -= glm::normalize(glm::cross(glm::normalize(look), glm::normalize(up))) * movementAmount;
			break;
		default:
			break;
		}
		
		setCameraTransform(pos, look, up);
	}
	void camera::setCameraType(MOVEMENT_TYPE movementType)
	{
		this->movementType = movementType;
	}
	void camera::updateTargetPos(glm::vec3 targetPosition)
	{
		targetPos = targetPosition;
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

		switch (movementType)
		{
		case engine::MOVEMENT_TYPE::FPS:
			look = glm::normalize(direction);
			break;
		case engine::MOVEMENT_TYPE::THIRD_PERSON:
			direction.y = -direction.y;
			localPos = glm::normalize(direction) * distace;
			pos = targetPos + localPos;
			//std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			break;
		default:
			break;
		}
		setCameraTransform(pos, look, up);
	}
	glm::vec3 camera::getForward()
	{
		return look;
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