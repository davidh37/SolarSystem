#pragma once
#include "common.hpp"




struct Mesh {
    struct Vertex {
        vec3 position = vec3(0.0f);
        vec3 color = COLOR_BLACK;
        vec2 uv = vec2(0.0f);
    };
    typedef std::vector<Vertex> VertexBuffer;
    typedef std::vector<uint16_t> IndexBuffer;

    enum Hint {
        STATIC,
        DYNAMIC,
        STREAM
    };

    GLuint vbo = 0, ebo = 0, vao = 0, ivbo;
    uint32_t vbo_capacity = 0, ebo_capacity = 0;
    uint32_t vbo_size = 0, ebo_size = 0;

    uint32_t ivbo_capacity = 0;
    uint32_t ivbo_size = 0;

    void upload(VertexBuffer &vertices, IndexBuffer &indices, Hint hint, bool instanced);
    void uploadInstanceData(std::vector<float> &instance_data, Hint hint);
    void draw();
    void drawLines();
    void drawInstances();
    void destroy();
};

    
