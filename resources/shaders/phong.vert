#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

out vec3 position;
out vec3 normal;
out vec2 UV;


void main(){
    position = vec3(view * model * vec4(inPosition, 1.0));
    UV = inUV;
    normal = mat3(view) * mat3(model) * inNormal;
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}


