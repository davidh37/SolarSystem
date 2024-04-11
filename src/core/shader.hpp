#pragma once

#include <glad/glad.h>
#include "common.hpp"

class Shader {
    public:
        void createAndUpdate(string const& vert_location, string const& frag_location);
        void use();
        void setUniformInteger(int location, int val);
        void setUniformMat4(int location, mat4 val);
        void setUniformVec4(int location, vec4 val);
        void destroy();

    private:
        GLuint id;
        GLuint vert_id, frag_id;
};


