#version 330 core
#extension GL_ARB_explicit_uniform_location : require

in vec3 position;
in vec3 normal;
in vec2 UV;
out vec4 out_Color;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
layout(location = 3) uniform sampler2DArray tex;
layout(location = 4) uniform vec4 material;
layout(location = 5) uniform int texture_id;

const vec3 light_color = vec3(1.0f, 1.0f, 1.0f);
const vec3 light_origin = vec3(0.0f, 0.0f, 0.0f);

void main(){
    float specularScalar = material[0];
    float diffuseScalar = material[1];
    float ambientScalar = material[2];
    float shininessScalar = material[3];

    float ambient = ambientScalar;

    vec3 view_light_origin = vec3(view * vec4(light_origin, 1.0f));
    vec3 to_light = normalize(view_light_origin - position);
    vec3 norm = normalize(normal);
    float diffuse = diffuseScalar * max(dot(norm, to_light), 0.0);

    vec3 to_camera = normalize(- position);
    vec3 reflect_direction = reflect(-to_light, norm);
    float specular = specularScalar * pow(max(dot(to_camera, reflect_direction), 0.0), shininessScalar);

    vec4 tex_color = texture(tex, vec3(UV, texture_id));
    vec3 object_color = (ambient + diffuse + specular) * light_color * tex_color.xyz;
    out_Color = vec4(object_color.xyz, tex_color.a);
}
