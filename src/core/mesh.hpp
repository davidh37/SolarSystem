#pragma once
#include "common.hpp"

namespace meshing {
    enum Hint {
        STATIC,
        DYNAMIC,
        STREAM
    };

    class VBO {
        public:
            enum Type {
                FLOAT,
                UINT32
            };
            void create(Type t = FLOAT, Hint h = STATIC);
            void update(void *data, size_t count, Type t);
            void use();
            void destroy();

        private:
            GLuint vbo = -1;
            uint32_t capacity = 0;
            uint32_t size = 0;
            Type type = FLOAT;
            Hint hint = STATIC;
    };




    enum Primitive {
        LINE,
        TRIANGLE
    };

    struct Vertex {
        vec3 position = vec3(0.0f);
        vec3 extra = COLOR_BLACK;
        vec2 extra2 = vec2(0.0f);
    };
    typedef std::vector<Vertex> VertexBuffer;



    /* Default Mesh with default Vertex */
    class Mesh {
        public:
            void create(Hint h = STATIC, Primitive p = TRIANGLE);
            void create(VertexBuffer &vb, Hint h = STATIC, Primitive p = TRIANGLE);
            void update(VertexBuffer &vb);
            void updateInstances(VertexBuffer &instance_buffer, Hint h = DYNAMIC);
            void draw();
            void destroy();

        private:
            VBO vertices, instances;
            
            uint32_t v_count = 0;
            uint32_t i_count = 0;

            GLuint vao = 0;
            Hint hint;
            Primitive primitive;
            
    };
}
    
