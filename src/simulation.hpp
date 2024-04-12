#pragma once
#include "core/common.hpp"

namespace simulation {

    struct Object {
        // physics data
        vec3 position;
        glm::quat rotation = {1.0, 0.0, 0.0, 0.0}; // identity quaternion
        vec3 velocity = vec3(0.0f);
        vec3 acceleration = vec3(0.0f);
        float mass; // earth = 1.0
        float radius; // earth = 1.0
        float angular_velocity = 0.2f;
        
        // render data
        vec3 color = COLOR_WHITE;
        int texture_id;
        int mesh_id;
        vec4 material;
    };

    void initialize();

    void cleanup();

    int update(float timestep, int follow_object);

    void render();
}