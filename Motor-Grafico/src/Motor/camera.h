#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include <array> 
//#include <memory> //std::unique_ptr

namespace engine
{
	enum class PROJECTION { ORTHO, PERSPECTIVE };
	enum class MOVEMENT_TYPE { FPS, THIRD_PERSON };
	enum class MOVEMENT_DIRECTION { FRONT, BACK, RIGHT, LEFT};
	class renderer;

	class ENGINE_API camera
	{
	public:
		camera();
		camera(renderer* currentRenderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector, PROJECTION projectionType);
		virtual void setCameraTransform(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector) = 0;
		virtual void rotateCamera(glm::vec2 mouseMovement) = 0;
		void moveCamera(glm::vec3 movePosition);
		void moveCamera(float movementAmount, MOVEMENT_DIRECTION movementDirection);
		void setView(glm::vec3 lookPosition);
		void setProjetion(PROJECTION projectionType);
		glm::vec3 getFront();
		glm::vec3 getRight();
		glm::vec3 getUp();
		glm::vec3 getPos();
		float getFOV();
		float getNear();
		float getFar();
		float getAspect();
	
		//void setCameraType(MOVEMENT_TYPE movementType);
		//MOVEMENT_TYPE getCameraType();
		~camera();
	protected:
		void setProjectionMatrix();
		void setViewMatrix();
		void setCameraPosToRenderer();
		void updateCameraVectors();
		glm::vec3 getDirectionByMovement(glm::vec2 mouseMovement);
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec3 pos; //donde esta parada
		glm::vec3 look; //a donde esta mirando
		glm::vec3 up; //el up de la camara
		glm::vec3 Front;
		glm::vec3 Right;
		glm::vec3 Up;
		renderer* currentRenderer;
		//MOVEMENT_TYPE movementType;
		float yaw;
		float pitch;
		float fov;
		float aspect;
		float near;
		float far;
	};

	//EJE X PITCH
	//EJE Y YAW
	//EJE Z ROLL
}
#endif