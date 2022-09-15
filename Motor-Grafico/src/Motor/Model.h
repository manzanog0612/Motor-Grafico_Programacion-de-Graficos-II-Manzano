#ifndef MODEL_H
#define MODEL_H

//#include <vector>
//#include <string>
//#include "glm/glm.hpp"
//#include "shader.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include ""

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "exports.h"
#include "node.h"

using namespace std;

namespace engine
{
    class ENGINE_API Model
    {
    public:
        Model(string path)
        {
            loadModel(path);
        }
        node* GetBaseNode() { return sceneNode; };
        vector<node*> GetNodes() { return nodes; };
        vector<node*> GetBSPPlanes() { return bspPlanes; };

    private:
        // model data
        vector<Texture> textures_loaded;
        string directory;
        node* sceneNode;
        vector <node*> nodes;
        vector <node*> bspPlanes;

        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene, engine::node* parent, glm::mat4 mat);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
            string typeName);
    };
}

#endif