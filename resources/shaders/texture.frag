#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec2 Texcoord;
in vec3 color;
out vec4 out_Color;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
layout(location = 3) uniform sampler2DArray tex;

void main(){
    vec4 tex_color = texture(tex, vec3(Texcoord, 0));
    out_Color = tex_color;
}
