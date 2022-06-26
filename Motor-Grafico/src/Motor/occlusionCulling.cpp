#include "occlusionCulling.h"

namespace engine
{
	camera* OcclusionCulling::cam = nullptr;

	glm::vec3 OcclusionCulling::pointBack = glm::vec3();
	glm::vec3 OcclusionCulling::pointFront = glm::vec3();
	glm::vec3 OcclusionCulling::pointTopLeft = glm::vec3();
	glm::vec3 OcclusionCulling::pointTopRight = glm::vec3();
	glm::vec3 OcclusionCulling::pointBottomLeft = glm::vec3();
	glm::vec3 OcclusionCulling::pointBottomRight = glm::vec3();

	plane OcclusionCulling::up = plane();
	plane OcclusionCulling::down = plane();
	plane OcclusionCulling::left = plane();
	plane OcclusionCulling::right = plane();
	plane OcclusionCulling::front = plane();
	plane OcclusionCulling::back = plane();

	OcclusionCulling::OcclusionCulling()
	{
		cam = nullptr;

		pointBack = glm::vec3();
		pointFront = glm::vec3();
		pointTopLeft = glm::vec3();
		pointTopRight = glm::vec3();
		pointBottomLeft = glm::vec3();
		pointBottomRight = glm::vec3();

		up = plane();
		down = plane();
		left = plane();
		right = plane();
		front = plane();
		back = plane();
	}

	OcclusionCulling::~OcclusionCulling()
	{
	}

	void OcclusionCulling::Init(camera* camera)
	{
		cam = camera;
	}

	void OcclusionCulling::Update()
	{
		float fov = cam->getFOV();
		float aspect = cam->getAspect();

		float halfheight = cam->getFar() * tan(fov * .5f);
		float halfWidth = halfheight * aspect;
		glm::vec3 frontFar = cam->getFar() * cam->getFront();

		back.SetPositionAndNormal(cam->getPos() + cam->getNear() * cam->getFront(), cam->getFront());
		front.SetPositionAndNormal(cam->getPos() + frontFar, -cam->getFront());
		right.SetPositionAndNormal(cam->getPos(), glm::cross(cam->getUp(), frontFar + cam->getRight() * halfWidth));
		left.SetPositionAndNormal(cam->getPos(), glm::cross(frontFar - cam->getRight() * halfWidth, cam->getUp()));
		up.SetPositionAndNormal(cam->getPos(), glm::cross(cam->getRight(), frontFar - cam->getUp() * halfheight));
		down.SetPositionAndNormal(cam->getPos(), glm::cross(frontFar + cam->getUp() * halfheight, cam->getRight()));
	}


	bool OcclusionCulling::IsOnView(std::vector<glm::vec3> aabb)
	{
		std::vector<glm::vec3> positions;

		positions.push_back(glm::vec3(aabb[0].x, aabb[1].y, aabb[1].z));
		positions.push_back(glm::vec3(aabb[1].x, aabb[1].y, aabb[1].z));
		positions.push_back(glm::vec3(aabb[0].x, aabb[0].y, aabb[1].z));
		positions.push_back(glm::vec3(aabb[1].x, aabb[0].y, aabb[1].z));
		positions.push_back(glm::vec3(aabb[0].x, aabb[1].y, aabb[0].z));
		positions.push_back(glm::vec3(aabb[1].x, aabb[1].y, aabb[0].z));
		positions.push_back(glm::vec3(aabb[0].x, aabb[0].y, aabb[0].z));
		positions.push_back(glm::vec3(aabb[1].x, aabb[0].y, aabb[0].z));

		for (short i = 0; i < positions.size(); i++)
		{
			if (!back.GetSide(positions[i]) || !front.GetSide(positions[i]) || !right.GetSide(positions[i])
				|| !left.GetSide(positions[i]) || !up.GetSide(positions[i]) || !down.GetSide(positions[i]))
			{
				return false;
			}
		}

		return true;
	}

	void OcclusionCulling::SetCamera(camera* camera)
	{
		cam = camera;
	}
}