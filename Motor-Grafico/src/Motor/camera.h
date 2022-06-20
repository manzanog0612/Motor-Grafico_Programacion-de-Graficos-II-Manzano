#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{
	enum class PROJECTION { ORTHO, PERSPECTIVE };
	enum class MOVEMENT_TYPE { FPS, THIRD_PERSON };
	enum class MOVEMENT_DIRECTION { FRONT, BACK, RIGHT, LEFT};
	class renderer;

	struct Plan
	{
		// unit vector
		glm::vec3 normal = { 0.f, 1.f, 0.f };

		// distance from origin to the nearest point in the plan
		float     distance = 0.f;

		Plan() = default;

		Plan(const glm::vec3 & p1, const glm::vec3 & norm)
			: normal(glm::normalize(norm)),
			distance(glm::dot(normal, p1))
		{}

		float getSignedDistanceToPlan(glm::vec3 point)
		{
			return glm::dot(normal, point) - distance;
		}
	};

	struct Frustum
	{
		Plan topFace;
		Plan bottomFace;

		Plan rightFace;
		Plan leftFace;

		Plan farFace;
		Plan nearFace;
	};

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
		glm::vec3 getUp();
		glm::vec3 getPos();
		Frustum getFrustrum() { return frustum; };
		//void setCameraType(MOVEMENT_TYPE movementType);
		//MOVEMENT_TYPE getCameraType();
		~camera();
	protected:
		void setProjectionMatrix();
		void setViewMatrix();
		void setCameraPosToRenderer();
		void updateCameraVectors();
		void createFrustumFromCamera(float aspect, float fovY, float zNear, float zFar);
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
		Frustum frustum;
		//MOVEMENT_TYPE movementType;
		float yaw;
		float pitch;
	};

	//EJE X PITCH
	//EJE Y YAW
	//EJE Z ROLL
}
#endif