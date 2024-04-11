#pragma once
#include "core/common.hpp"
#include "core/mesh.hpp"

namespace renderer {

    void initialize();

    void render(meshing::Mesh &m, mat4 model, mat4 view, mat4 projection, int texture_index, float specular, float diffuse, float ambient, float shininess);

    void cleanup();
}