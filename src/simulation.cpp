#include "core/common.hpp"
#include "simulation.hpp"
#include "renderer.hpp"
#include "core/camera.hpp"

namespace simulation {

    static std::vector<Object> objects;

    void initialize(){
        const float AU = 250.0f;
        const float EARTH_SPEED = 40.0f;

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
        objects[index].angular_velocity = 0.005f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 0;
        objects[index].material = mat_sun; 
        index++;

        // mercury
        objects.resize(index+1);
        objects[index].position = {0.7f * AU, 0.0f, 0.0f};
        objects[index].velocity = {0.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 0.055f;
        objects[index].radius = 0.38f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 1;
        objects[index].material = mat_rocky; 
        index++;

        // venus
        objects.resize(index+1);
        objects[index].position = {0.85f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 0.815f;
        objects[index].radius = 0.9499f;

        objects[index].color = COLOR_ORANGE;
        objects[index].mesh_id = 0;
        objects[index].texture_id = 2;
        objects[index].material = mat_rocky; 
        index++;

        // earth
        objects.resize(index+1);
        objects[index].position = {1.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 1.0f;
        objects[index].radius = 1.0f;

        objects[index].color = COLOR_BLUE;
        objects[index].mesh_id = 0;
        objects[index].texture_id = 3;
        objects[index].material = mat_earth;  
        index++;

        // mars
        objects.resize(index+1);
        objects[index].position = {1.15f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 0.107f;
        objects[index].radius = 0.53f;

        objects[index].color = COLOR_ORANGE;
        objects[index].mesh_id = 0;
        objects[index].texture_id = 4;
        objects[index].material = mat_rocky; 
        index++;

        // jupiter
        objects.resize(index+1);
        objects[index].position = {2.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 317.8f;
        objects[index].radius = 11.2f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 5;
        objects[index].material = mat_gas; 
        index++;

        // saturn
        objects.resize(index+1);
        objects[index].position = {3.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 95.159f;
        objects[index].radius = 9.14f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 6;
        objects[index].material = mat_gas;
        index++;
        
        // uranus
        objects.resize(index+1);
        objects[index].position = {4.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 14.536f;
        objects[index].radius = 4.0f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 7;
        objects[index].material = mat_gas; 
        index++;

        // neptune
        objects.resize(index+1);
        objects[index].position = {5.0f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, EARTH_SPEED};
        objects[index].mass = 17.146f;
        objects[index].radius = 3.85f;

        objects[index].mesh_id = 0;
        objects[index].texture_id = 8;
        objects[index].material = mat_gas; 
        index++;

        // russels teapot
        objects.resize(index+1);
        objects[index].position = {2.6f * AU, 0.0f, 0.0f};
        objects[index].velocity = {1.0f, 0.0f, 1.0f * EARTH_SPEED};
        objects[index].mass = 0.01f;
        objects[index].radius = 0.5f;
         objects[index].angular_velocity = 0.0f;

        objects[index].color = COLOR_ORANGE;
        objects[index].mesh_id = 1;
        objects[index].texture_id = 0;
        objects[index].material = vec4(1.2f, 0.4f, 0.1f, 32.0f); // specular, diffuse, ambient, shininess
        index++;

        camera::setProjection(80.0f, 0.15f, 3000.0f);
        camera::setPosition({1 * AU, 0.0f, 5.0f});
        renderer::initialize();
    }

    void cleanup(){
        renderer::cleanup();   
    }

    int update(float dt, int follow_object){
        if(follow_object > 0 && follow_object < objects.size()){
            Object &obj = objects[follow_object];
            camera::setPosition(vec3(obj.position.x + 2.0f * obj.radius, obj.position.y + 2.0f * obj.radius, obj.position.z + 2.0f * obj.radius));
        }

        // gravity interaction
        const float GRAVITY = 0.005f;

        for(auto i = 0; i < objects.size(); i++){
            objects[i].acceleration = vec3(0.0f);
        }
        for(auto i = 0; i < objects.size(); i++){
            for(auto j = i + 1; j < objects.size(); j++){
                vec3 i_to_j = objects[j].position - objects[i].position;
                float i_to_j_len2 = glm::length2(i_to_j);
                assert(i_to_j_len2 != 0.0f);
                float force_modifier = GRAVITY / i_to_j_len2;
                objects[i].acceleration += i_to_j * objects[j].mass * force_modifier;
                objects[j].acceleration += -1 * i_to_j * objects[i].mass * force_modifier;
            }
        }

        // euler integration
        for(auto i = 0; i < objects.size(); i++){
            vec3 newVel = objects[i].velocity + objects[i].acceleration * dt;
            objects[i].position += 0.5f * (objects[i].velocity + newVel) * dt;
            objects[i].velocity = newVel;
            glm::quat rot = glm::angleAxis(glm::radians(objects[i].angular_velocity), glm::vec3(0.f, 1.f, 0.f));
            objects[i].rotation *= rot;
        }

        return objects.size();
    }

    void render(){
        renderer::render(objects);
    }
}