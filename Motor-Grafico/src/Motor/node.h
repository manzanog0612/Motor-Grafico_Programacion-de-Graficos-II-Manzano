#ifndef NODE_H
#define NODE_H

#include "exports.h"
#include "entity.h"
#include <vector>
#include "renderer.h"
#include "shape.h"
#include "camera.h"
#include "aabb.h"
//#include "modelImporter.h"
#include <string>

#define AMOUNT_BOUNDS 8

namespace engine
{
	//struct BoundingVolume
	//{
	//	virtual bool isOnFrustum(const Frustum& camFrustum, const entity& entity) const = 0;
	//
	//	virtual bool isOnOrForwardPlan(const plane& plan) const = 0;
	//
	//	bool isOnFrustum(const Frustum& camFrustum) const
	//	{
	//		return (isOnOrForwardPlan(OcclusionCulling::left) &&
	//			isOnOrForwardPlan(OcclusionCulling::right) &&
	//			isOnOrForwardPlan(OcclusionCulling::up) &&
	//			isOnOrForwardPlan(OcclusionCulling::down) &&
	//			isOnOrForwardPlan(OcclusionCulling::back) &&
	//			isOnOrForwardPlan(OcclusionCulling::front));
	//	};
	//};
	//
	//struct AABB : public BoundingVolume
	//{
	//	glm::vec3 center{ 0.f, 0.f, 0.f };
	//	glm::vec3 extents{ 0.f, 0.f, 0.f };
	//
	//	AABB() {}
	//
	//	AABB(const glm::vec3& min, const glm::vec3& max)
	//		: BoundingVolume{}, center{ (max + min) * 0.5f }, extents{ max.x - center.x, max.y - center.y, max.z - center.z }
	//	{}
	//
	//	AABB(const glm::vec3& inCenter, float iI, float iJ, float iK)
	//		: BoundingVolume{}, center{ inCenter }, extents{ iI, iJ, iK }
	//	{}
	//
	//	//std::array<glm::vec3, 8> getVertice() const
	//	//{
	//	//	std::array<glm::vec3, 8> vertice;
	//	//	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	//	//	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	//	//	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	//	//	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	//	//	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	//	//	vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	//	//	vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	//	//	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	//	//	return vertice;
	//	//}
	//
	//	//see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plan.html
	//	//bool isOnOrForwardPlan(const plane& plan) const final
	//	//{
	//	//	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	//	//	const float r = extents.x * std::abs(plan..x) + extents.y * std::abs(plan.normal.y) +
	//	//		extents.z * std::abs(plan.normal.z);
	//	//
	//	//	return -r <= plan.getSignedDistanceToPlan(center);
	//	//}
	//
	//	//bool isOnFrustum(const Frustum& camFrustum, const entity& transform) const final
	//	//{
	//	//	//Get global scale thanks to our transform
	//	//	const glm::vec3 globalCenter{ transform.getModelConst() * glm::vec4(center, 1.f) };
	//	//
	//	//	// Scaled orientation
	//	//	const glm::vec3 right = transform.getRightConst() * extents.x;
	//	//	const glm::vec3 up = transform.getUpConst() * extents.y;
	//	//	const glm::vec3 forward = transform.getForwardConst() * extents.z;
	//	//
	//	//	const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
	//	//		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
	//	//		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));
	//	//
	//	//	const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
	//	//		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
	//	//		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));
	//	//
	//	//	const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
	//	//		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
	//	//		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));
	//	//
	//	//	const AABB globalAABB(globalCenter, newIi, newIj, newIk);
	//	//
	//	//	return false;
	//	//	/*return (globalAABB.isOnOrForwardPlan(camFrustum.leftFace) &&
	//	//		globalAABB.isOnOrForwardPlan(camFrustum.rightFace) &&
	//	//		globalAABB.isOnOrForwardPlan(camFrustum.topFace) &&
	//	//		globalAABB.isOnOrForwardPlan(camFrustum.bottomFace) &&
	//	//		globalAABB.isOnOrForwardPlan(camFrustum.nearFace) &&
	//	//		globalAABB.isOnOrForwardPlan(camFrustum.farFace));*/
	//	//};
	//};

	class ENGINE_API node : public entity
	{
	public:
		node();
		~node();

		vector<node*> getChildren();
		int getChildrenAmount();

		void setRenderer(renderer* render);
		void setMeshes(vector<Mesh> meshes);
		void setName(string name);
		void setChildren(vector<node*> children);
		void setParent(node* parent);
		void generateVolumeAABB();

		string getName();
		vector<glm::vec3> getLocalAABB(); 

		float getRandomNumber(float min, float max);
		node* getChildWithName(string name);

		bool canDrawThisFrame();
		//void drawDebug();
		void allowDrawThisFrame();
		void updateAABBPositions();

		void setTransformations(Frustum frustum);
		void addBoundsToAABB(vector<glm::vec3> childAABB);
		void draw();
		void drawAsParent(Frustum frustum);
		//bool isOnOrForwardPlan(Plan plan);
		//bool isInsideCamera(Frustum frustum);
		void deinit();
	private:
		vector<node*> children;
		node* parent;

		vector<Mesh> meshes;
		string name;

		void setAABB(vector<Mesh> meshes);

		vector<glm::vec3> aabb;
		vector<glm::vec3> localAABB;
		vector<glm::vec3> aabbPositions;

		engine::aabb* volume;

		shape* aabbShapes[AMOUNT_BOUNDS];

		bool drawThisFrame;
		bool drawFirstParent;

		//AABB generateAABB(const node& node)
		//{
		//	glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
		//	glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
		//	for (auto&& mesh : node.meshes)
		//	{
		//		for (auto&& vertex : mesh.vertices)
		//		{
		//			minAABB.x = std::min(minAABB.x, vertex.Position.x);
		//			minAABB.y = std::min(minAABB.y, vertex.Position.y);
		//			minAABB.z = std::min(minAABB.z, vertex.Position.z);
		//
		//			maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
		//			maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
		//			maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
		//		}
		//	}
		//	return AABB(minAABB, maxAABB);
		//}
		//
		//AABB getGlobalAABB()
		//{
		//	AABB globalAABB = generateAABB(*this);
		//	//Get global scale thanks to our transform
		//	const glm::vec3 globalCenter{ getModelConst() * glm::vec4(globalAABB.center, 1.f)};
		//
		//	// Scaled orientation
		//	const glm::vec3 right = getRightConst() * globalAABB.extents.x;
		//	const glm::vec3 up = getUpConst() * globalAABB.extents.y;
		//	const glm::vec3 forward = getForwardConst() * globalAABB.extents.z;
		//
		//	const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		//		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		//		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));
		//
		//	const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		//		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		//		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));
		//
		//	const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		//		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		//		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));
		//
		//	return AABB(globalCenter, newIi, newIj, newIk);
		//}
	};
}

#endif