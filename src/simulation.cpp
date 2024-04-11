#include "core/common.hpp"
#include "simulation.hpp"
#include "renderer.hpp"
#include "core/camera.hpp"

namespace simulation {

    static std::vector<Object> objects;

    void initialize(){
        const float AU = 400.0f;
        vec4 mat_sun = vec4(0.0f, 0.0f, 2.5f, 16.0f);
        vec4 mat_earth = vec4(1.5f, 2.3f, 0.15f, 16.0f);
        vec4 mat_rocky = vec4(1.5f, 2.3f, 0.15f, 16.0f);
        vec4 mat_gas = vec4(1.5f, 2.3f, 0.15f, 16.0f);

        int index = 0;
        // sun
        objects.resize(index+1);
        objects[index].position = {0.0f, 0.0f, 0.0f};
        objects[index].velocity = {0.0f, 0.0f, 0.0f};
        objects[index].mass = 333000.0f;
        objects[index].radius = 109.0f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 0;
        objects[index].material = mat_sun; // specular, diffuse, ambient, shininess
        index++;

        // mercury
        objects.resize(index+1);
        objects[index].position = {0.5f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 0.055f;
        objects[index].radius = 0.38f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 1;
        objects[index].material = mat_rocky; // specular, diffuse, ambient, shininess
        index++;

        // venus
        objects.resize(index+1);
        objects[index].position = {0.75f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 0.815f;
        objects[index].radius = 0.9499f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 2;
        objects[index].material = mat_rocky; // specular, diffuse, ambient, shininess
        index++;

        // earth
        objects.resize(index+1);
        objects[index].position = {1.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 1.0f;
        objects[index].radius = 1.0f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 3;
        objects[index].material = mat_earth;  // specular, diffuse, ambient, shininess
        index++;

        // mars
        objects.resize(index+1);
        objects[index].position = {1.25f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 0.107f;
        objects[index].radius = 0.53f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 4;
        objects[index].material = mat_rocky; // specular, diffuse, ambient, shininess
        index++;

        // jupiter
        objects.resize(index+1);
        objects[index].position = {1.5f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 317.8f;
        objects[index].radius = 11.2f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 5;
        objects[index].material = mat_gas; // specular, diffuse, ambient, shininess
        index++;

        // saturn
        objects.resize(index+1);
        objects[index].position = {1.75f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 95.159f;
        objects[index].radius = 9.14f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 6;
        objects[index].material = mat_gas; // specular, diffuse, ambient, shininess
        index++;
        
        // uranus
        objects.resize(index+1);
        objects[index].position = {2.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 14.536f;
        objects[index].radius = 4.0f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 7;
        objects[index].material = mat_gas; // specular, diffuse, ambient, shininess
        index++;

        // neptune
        objects.resize(index+1);
        objects[index].position = {2.25f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 0.0f};
        objects[index].mass = 17.146f;
        objects[index].radius = 3.85f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 8;
        objects[index].material = mat_gas; // specular, diffuse, ambient, shininess
        index++;

        camera::setProjection(80.0f, 0.1f, 1000.0f);
        camera::setPosition({1 * AU, 0.0f, 5.0f});
        renderer::initialize();
    }

    void cleanup(){
        renderer::cleanup();   
    }

    int update(float timestep){
        // do fancy physics
        for(int i = 0; i < objects.size(); i++){
            for(int j = i + 1; j < objects.size(); j++){
                // interaction
            }
        }
        return objects.size();
    }

    void render(){
        renderer::render(objects);
    }
}