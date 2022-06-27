#include "camera.h"
#include "renderer.h"
#include <GLM/glm.hpp>
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

namespace engine
{
	camera::camera()
	{
		currentRenderer = NULL;
		yaw = -90.0f;
		pitch = 0.f;
	}
	camera::camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType)
	{
		this->currentRenderer = currentRenderer;
		yaw = -90.0f;
		pitch = 0.f;
	
		setProjetion(projectionType);
	
		this->currentRenderer->setProjectionMatrix(projectionMatrix);
		setCameraTransform(position, lookPosition, upVector);
	}
	void camera::setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		pos = startingPosition;
		look = lookPosition;
		up = upVector;
	
		viewMatrix = glm::lookAt(pos, look, up);
		currentRenderer->setViewMatrix(viewMatrix);
		setCameraPosToRenderer();

		updateCameraVectors();
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
	glm::vec3 camera::getDirectionByMovement(glm::vec2 mouseMovement)
	{
		yaw += mouseMovement.x;
		pitch += mouseMovement.y;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		
		return direction;
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
			fov = glm::radians(45.0f);
			aspect = (float)currentRenderer->getCurrentWindow()->getWidth() / (float)currentRenderer->getCurrentWindow()->getHeight();
			near = 0.1f;
			far = 500.0f;

			createFrustumFromCamera(aspect, fov, near, far);

			projectionMatrix = glm::perspective(fov, aspect, near, far);
			break;
		default:
			projectionMatrix = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 500.0f);
			break;
		}
	}
	glm::vec3 camera::getFront()
	{
		return Front;
	}
	glm::vec3 camera::getRight()
	{
		return Right;
	}
	glm::vec3 camera::getUp()
	{
		return Up;
	}
	glm::vec3 camera::getPos()
	{
		return pos;
	}
	float camera::getFOV()
	{
		return fov;
	}
	float camera::getNear()
	{
		return near;
	}
	float camera::getFar()
	{
		return far;
	}
	float camera::getAspect()
	{
		return aspect;
	}
	camera::~camera()
	{

	}
	void camera::setProjectionMatrix()
	{
		currentRenderer->setProjectionMatrix(projectionMatrix);
	}
	void camera::setViewMatrix()
	{
		currentRenderer->setViewMatrix(viewMatrix);
	}
	void camera::setCameraPosToRenderer()
	{
		currentRenderer->setViewPosition(pos);
	}

	Frustum camera::createFrustumFromCamera(float aspect, float fovY, float zNear, float zFar)
	{
		Frustum frustum;
		const float halfVSide = zFar * tanf(fovY * .5f);
		const float halfHSide = halfVSide * aspect;
		const glm::vec3 frontMultFar = zFar * Front;

		frustum.nearFace = { Front + zNear * Front, Front };
		frustum.farFace = { getPos() + frontMultFar, Front };
		frustum.rightFace = { getPos(),	glm::cross(Up,frontMultFar + Right * halfHSide) };
		frustum.leftFace = { getPos(), glm::cross(frontMultFar - Right * halfHSide, Up) };
		frustum.topFace = { getPos(), glm::cross(Right, frontMultFar - Up * halfVSide) };
		frustum.bottomFace = { getPos(), glm::cross(frontMultFar + Up * halfVSide, Right) };

		return frustum;
	}

	void camera::updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, { 0,1,0 }));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
}