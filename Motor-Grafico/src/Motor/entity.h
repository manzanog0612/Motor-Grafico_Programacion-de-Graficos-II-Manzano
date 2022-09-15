#ifndef ENTITY
#define ENTITY

#include <GLM/glm.hpp>
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "exports.h"
#include <vector>


namespace engine
{
	class renderer;

	struct Transform
	{
		/*SPACE INFORMATION*/
		//Local space information
		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		glm::vec3 eulerRot = { 0.0f, 0.0f, 0.0f };
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		//Global space information concatenate in matrix
		glm::mat4 modelMatrix = glm::mat4(1.0f);
	};

	class ENGINE_API entity
	{
	public:
		entity();
		~entity();
		void setPos(glm::vec3 pos);
		void setPos(float x, float y, float z);
		void setRot(glm::vec3 rot);
		void setRotRadians(glm::vec3 rot);
		void setRot(float x, float y, float z);
		void setScale(glm::vec3 localScale);
		void setScale(float x, float y, float z);
		void setColor(glm::vec4 color);
		void setColor(float r, float g, float b, float a);
		void setWorldModelWithParentModel(glm::mat4 localModel);
		void invertX();
		void invertY();
		void invertZ();
		void setMatrix(glm::mat4 mat);

		void UseLocalMatrix();

		glm::vec4 getColor();
		glm::vec3 getPos();
		glm::vec3 getPosFromTransformMatrix();
		glm::vec3 getRot();
		glm::vec3 getScale();
		glm::mat4 getModelConst() const
		{
			return worldModel;
		}
		glm::vec3 getRightConst() const
		{
			return worldModel[0];
		}
		glm::vec3 getUpConst() const
		{
			return worldModel[1];
		}
		glm::vec3 getForwardConst() const
		{
			return worldModel[2];
		}
		glm::vec3 getForward();
		glm::vec3 getPos(glm::mat4 mat);
		glm::vec3 getRot(glm::mat4 mat);
		glm::vec3 getScale(glm::mat4 mat);

		glm::vec3 toEulerRad(glm::quat rot);
		glm::vec3 normalizeAngles(glm::vec3 angles);
		float normalizeAngle(float angle);
		glm::quat getRotationByMatrix(glm::mat4 mat);
		glm::quat eulerToQuat(glm::vec3 euler);
		glm::vec3 quatToVec(glm::quat quat, glm::vec3 vec);

		glm::mat4 getModel();
		glm::mat4 getLocalModel();

		virtual void draw() = 0;

	protected:
		renderer* _renderer;

		Transform transform;

		glm::vec3 v3localPos;
		glm::vec3 v3localRot;
		glm::vec3 v3localScale;

		glm::mat4 worldModel;
		glm::mat4 localModel;
		glm::mat4 parentModel;

		glm::mat4 localTranslate;
		glm::mat4 localRotateX;
		glm::mat4 localRotateY;
		glm::mat4 localRotateZ;
		glm::mat4 localScale;

		glm::vec4 color;

		unsigned int VAO, VBO, EBO, _vertices;
		
		void updateModelMatrix();
	private:
		void setRotX(float x);
		void setRotY(float y);
		void setRotZ(float z);

		bool useLocalMatrix;
	};
}
#endif // !ENTITY