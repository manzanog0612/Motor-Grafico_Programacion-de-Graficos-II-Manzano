#ifndef NODE_H
#define NODE_H

#include "exports.h"
#include "entity.h"
#include <vector>
#include "renderer.h"
#include "shape.h"
#include "camera.h"
//#include "modelImporter.h"
#include <string>

#define AMOUNT_BOUNDS 8

namespace engine
{
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

		string getName();

		float getRandomNumber(float min, float max);
		node* getChildWithName(string name);

		bool isOnOrForwardPlan(Plan plan);
		bool isInsideCamera(Frustum frustum);

		void checkIfDrawAsChild(Frustum frustum);
		void setTransformations(vector<node*> *lastChilds);
		void draw();
		void drawAsParent(Frustum frustum);
		void drawAsChild();
		void deinit();
	private:
		vector<Mesh> meshes;

		vector<node*> children;
		node* parent;

		vector<node*> *lastChilds;

		string name;

		void setAABB(vector<Mesh> meshes);

		vector<glm::vec3> aabb;

		shape* aabbShapes[AMOUNT_BOUNDS];

		bool drawnThisFrame;
	};
}

#endif