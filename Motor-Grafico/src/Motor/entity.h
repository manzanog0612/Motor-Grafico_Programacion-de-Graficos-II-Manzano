#pragma once
#include "exports.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace engine
{
	class renderer;

	class ENGINE_API entity
	{
	public:
		entity();
		~entity();
		void setPos(float x, float y, float z);
		void setRotX(float x);
		void invertX();
		void setRotY(float y);
		void invertY();
		void setRotZ(float z);
		void invertZ();
		void setScale(float x, float y, float z);
		void setColor(glm::vec4 color);
		glm::vec4 getColor();

		float getPosX();
		float getPosY();
		float getPosZ();

		float getRotX();
		float getRotY();
		float getRotZ();


		float getScaleX();
		float getScaleY();
		float getScaleZ();

		virtual void draw() = 0;

	protected:
		renderer* _renderer;

		glm::vec3 v3pos;
		glm::vec3 v3rot;
		glm::vec3 v3scale;

		glm::mat4 model;

		glm::mat4 translate;
		glm::mat4 rotateX;
		glm::mat4 rotateY;
		glm::mat4 rotateZ;
		glm::mat4 scale;

		glm::vec4 color;

		unsigned int VAO, VBO, EBO, _vertices;
		
		void updateModelMatrix();
	private:
		virtual void setShader() = 0;
	};
}