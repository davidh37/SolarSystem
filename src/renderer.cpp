#include "core/common.hpp"
#include "renderer.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"

namespace renderer {
    static Shader s;
    static Texture t;

    void initialize(){
        s.createAndUpdate("resources/shaders/phong.vert", "resources/shaders/phong.frag");
        t.create(true, 1);
        t.update("resources/textures/earth/2k_earth_daymap.jpg", true, 0);
        //t.update("resources/test2.png", false, 1);
    }

    void render(meshing::Mesh &m, mat4 model, mat4 view, mat4 projection, int texture_index, float specular, float diffuse, float ambient, float shininess){
        s.use();
        t.use(0);
        s.setUniformMat4(0, model);
        s.setUniformMat4(1, view);
        s.setUniformMat4(2, projection);
        s.setUniformInteger(3, 0);
        s.setUniformVec4(4, vec4(specular, diffuse, ambient, shininess));
        m.draw();
    }

    void cleanup(){
        s.destroy();
        t.destroy();
    }
}