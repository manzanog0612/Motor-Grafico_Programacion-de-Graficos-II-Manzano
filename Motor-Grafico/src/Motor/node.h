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
		vector<glm::vec3> getLocalAABB(); 

		float getRandomNumber(float min, float max);
		node* getChildWithName(string name);

		void dontDraw();
		void drawDebug();

		void checkIfDrawAsChild();
		void setTransformations(vector<node*> *lastChilds);
		void addBoundsToAABB(vector<glm::vec3> childAABB);
		void draw();
		void drawAsParent();
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
		vector<glm::vec3> localAABB;

		shape* aabbShapes[AMOUNT_BOUNDS];

		bool drawnThisFrame;
		bool drawFirstParent;
	};
}

#endif