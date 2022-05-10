#pragma once
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "../shader.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include ""

using namespace std;

namespace engine
{
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

    struct Texture {
        unsigned int id;
        string type;
    };

    class Mesh {
    public:
        // mesh data
        vector<Vertex>       vertices;
        vector<unsigned int> indices;
        vector<Texture>      textures;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader& shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
    };
}