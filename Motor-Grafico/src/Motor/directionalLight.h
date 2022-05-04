#pragma once
#include "light.h";

namespace engine
{
	class ENGINE_API directionalLight : public light
	{
	public:
		directionalLight(renderer* render);
		void setInitialValues() override;
		void processIndividualValues() override;
		void setDirection(glm::vec3 direction, bool normalized);
	private:
		glm::vec3 direction;
	};
}