#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "exports.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

namespace engine
{

    class ENGINE_API Shader
    {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setVec3(const std::string& name, const glm::vec3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;

    private:
        void checkCompileErrors(unsigned int shader, std::string type);
    };

}