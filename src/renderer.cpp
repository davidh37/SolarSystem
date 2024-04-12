#include "core/common.hpp"
#include "renderer.hpp"
#include "core/mesh.hpp"
#include "core/shader.hpp"
#include "core/texture.hpp"
#include "core/camera.hpp"
#include "meshloader.hpp"


namespace renderer {
    static Shader s;
    static Texture t;
    static std::vector<meshing::Mesh> m;

    static Shader s_points;
    static meshing::Mesh m_points;

    static Shader s_skybox;
    static Texture t_skybox;
    static meshing::Mesh m_skybox;

    void initialize(){
        s.createAndUpdate("resources/shaders/phong.vert", "resources/shaders/phong.frag");

        t.create(true, 11);
        string path = "resources/2Ktextures/";
        t.update(path + "sun.jpg", true, 0);
        t.update(path + "mercury.jpg", true, 1);
        t.update(path + "venus.jpg", true, 2);
        t.update(path + "earth.jpg", true, 3);
        t.update(path + "mars.jpg", true, 4);
        t.update(path + "jupiter.jpg", true, 5);
        t.update(path + "saturn.jpg", true, 6);
        t.update(path + "uranus.jpg", true, 7);
        t.update(path + "neptune.jpg", true, 8);
        t.update(path + "moon.jpg", true, 9);
        t.update(path + "earth_night.jpg", true, 10);
        t.mipmap();
        
        m.resize(3);
        meshing::VertexBuffer vb;
        
        vb.clear();
        meshloader::addObj(vb, "resources/sphere.obj");
        m[0].create(meshing::STATIC, meshing::TRIANGLE);
        m[0].update(vb);
        
        vb.clear();
        meshloader::addObj(vb, "resources/teapot.obj");
        m[1].create(meshing::STATIC, meshing::TRIANGLE);
        m[1].update(vb);

        vb.clear();
        meshloader::addObj(vb, "resources/bunny.obj");
        m[2].create(meshing::STATIC, meshing::TRIANGLE);
        m[2].update(vb);

        s_points.createAndUpdate("resources/shaders/color.vert", "resources/shaders/color.frag");
        m_points.create(meshing::STREAM, meshing::POINT);
    }

    void cleanup(){
        s.destroy();
        t.destroy();
        for(auto mesh : m){
            mesh.destroy();
        }

        s_points.destroy();
        m_points.destroy();
    }

    void render(std::vector<simulation::Object> const&objects){
        s_points.use();
        s_points.setUniformMat4(0, camera::getProjectionMatrix() * camera::getViewMatrix());
        meshing::VertexBuffer vb = {};
        for(auto obj : objects){
            vb.push_back({obj.position, obj.color, vec2()});
        }
        m_points.update(vb);
        m_points.draw();

        s.use();
        t.use(0);

        for(auto obj : objects){
            assert(obj.texture_id >= 0);
            assert(obj.texture_id < t.getLayerCount());
            assert(obj.mesh_id >= 0);
            assert(obj.mesh_id < m.size());
            

            
            mat4 trans = glm::translate(mat4(1.0f), obj.position);
            mat4 rot = glm::mat4_cast(obj.rotation);
            mat4 scale = glm::scale(mat4(1.0f), vec3(obj.radius));
            mat4 model = trans * rot * scale;

            s.setUniformMat4(0, model);
            s.setUniformMat4(1, camera::getViewMatrix());
            s.setUniformMat4(2, camera::getProjectionMatrix());
            s.setUniformInteger(3, 0);
            s.setUniformVec4(4, obj.material);
            s.setUniformInteger(5, obj.texture_id);

            m[obj.mesh_id].draw();
        }
    }

    
}