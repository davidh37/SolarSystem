#include <glad/glad.h>
#include "common.hpp"
#include "mesh.hpp"

namespace meshing {
    void VBO::create(Type t, Hint h){
        type = t;
        hint = h;
        glGenBuffers(1, &vbo);
    }

    void VBO::update(void *data, size_t count, Type t){
        assert(t == type);
        size_t bytes = 0;
        switch(t){
            case FLOAT:
                bytes = sizeof(float);
                break;
            case UINT32:
                bytes = sizeof(uint32_t);
                break;
        }
        assert(bytes != 0);

        GLenum usage = GL_STATIC_DRAW;
        switch(hint){
            case STATIC:
                usage = GL_STATIC_DRAW;
                break;
            case DYNAMIC:
                usage = GL_DYNAMIC_DRAW;
                break;
            case STREAM:
                usage = GL_STREAM_DRAW;
                break;
        }

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        size = count;
        if(count > capacity){
            glBufferData(GL_ARRAY_BUFFER, count * bytes, data, usage);
            capacity = count;
        }else{
            glBufferSubData(GL_ARRAY_BUFFER, 0, count * bytes, data);
        }
    }

    void VBO::use(){
        assert(vbo != 0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }

    void VBO::destroy(){
        glDeleteBuffers(1, &vbo);
        capacity = 0;
        size = 0;
    }    
     


    void Mesh::create(Hint h, Primitive p){
        hint = h;
        primitive = p;

        glGenVertexArrays(1, &vao);
        vertices.create(VBO::FLOAT, h);
        glBindVertexArray(vao);
        vertices.use();
        
        // we hardcode the vertex layout
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, extra));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, extra2));
        glEnableVertexAttribArray(2);
    }

    void Mesh::create(VertexBuffer& vb, Hint h, Primitive p){
        Mesh::create(h, p);
        Mesh::update(vb);
    }
    
    void Mesh::update(VertexBuffer& vb){
        v_count = vb.size();
        vertices.update(vb.data(), sizeof(Vertex) / sizeof(float) * vb.size(), VBO::FLOAT);
    }

    void Mesh::updateInstances(VertexBuffer &instance_buffer, Hint h){
        if(i_count == 0){
            instances.create(meshing::VBO::FLOAT, h);
        
            glBindVertexArray(vao);
            instances.use();
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, extra));
            glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, extra2));
            glEnableVertexAttribArray(3);
            glEnableVertexAttribArray(4);
            glEnableVertexAttribArray(5);
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1); 
            glVertexAttribDivisor(5, 1); 
        }

        instances.update(instance_buffer.data(), sizeof(meshing::Vertex) / sizeof(float) * instance_buffer.size(), meshing::VBO::FLOAT);
        i_count = instance_buffer.size();
    }

    void Mesh::draw(){
        assert(vao != 0);
        glBindVertexArray(vao);
        //vbo bind implicit
        GLenum prim = -1;
        switch(primitive){
            case TRIANGLE:
                prim = GL_TRIANGLES;
                break;
            case LINE:
                prim = GL_LINE;
                break;
            default:
                assert(false);
                break;
        }

        if(i_count > 0){
            glDrawArraysInstanced(prim, 0, v_count, i_count);
        }else{
            glDrawArrays(prim, 0, v_count);
        }
    }
    
    void Mesh::destroy(){
        glDeleteVertexArrays(1, &vao);
        v_count = 0;
    }

}
    