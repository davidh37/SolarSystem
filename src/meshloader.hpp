#pragma once
#include "core/common.hpp"
#include "core/mesh.hpp"

namespace meshloader {
    /* these functions add to the vertex & index buffers, can therefore be called multiple times before uploading */

    bool addObj(Mesh::VertexBuffer &vb, Mesh::IndexBuffer &ib, string path, vec3 pos = {0.0f, 0.0f, 0.0f}, vec3 fallback_color = COLOR_RED);
    void addCircle(Mesh::VertexBuffer &vb, Mesh::IndexBuffer &ib, int segments, vec3 pos, vec2 scale, vec3 color, vec2 uv_pos, vec2 uv_scale);
    void addSquare(Mesh::VertexBuffer &vb, Mesh::IndexBuffer &ib, vec3 pos, vec2 scale, vec3 color, vec2 uv_pos, vec2 uv_scale);

}