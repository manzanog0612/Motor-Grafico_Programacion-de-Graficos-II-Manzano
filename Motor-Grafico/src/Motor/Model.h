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
        void Draw(Shader& shader, glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
    private:
        // model data
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;

        void loadModel(string path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
            string typeName);
    };
}

#endif