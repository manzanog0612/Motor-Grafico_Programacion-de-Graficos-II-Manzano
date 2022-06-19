#ifndef AABB_H
#define AABB_H

#include "exports.h"
#include <GLM/glm.hpp>
#include <vector>

using namespace std;

namespace engine
{
	class ENGINE_API aabb
	{
	public:
		aabb();
		~aabb();

		void setBounds(vector<glm::vec3> vertices);

		void draw();
	private:
		vector<glm::vec3> vertices;
	};
}

#endif