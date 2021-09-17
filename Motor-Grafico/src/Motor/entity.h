#pragma once
#include "exports.h"
#include "renderer.h"

namespace engine
{
	class ENGINE_API entity
	{
	public:
		entity();
		~entity();

	protected:
		renderer* renderer;

		glm::vec3 v3pos;
		glm::vec3 v3rot;
		glm::vec3 v3scale;

		glm::mat4 model;

		glm::mat4 translate;
		glm::mat4 rotateX;
		glm::mat4 rotateY;
		glm::mat4 rotateZ;
		glm::mat4 scale;

		void UpdateModelMatrix();
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		void SetScale(float x, float y, float z);

	private:

	};
}