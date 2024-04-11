#version 330 core
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_Texcoord;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

out vec2 Texcoord;
out vec3 normal;

void main(){
    Texcoord = in_Texcoord;
    normal = in_Normal;
    gl_Position = projection * view * model * vec4(in_Position, 1.0);
}


