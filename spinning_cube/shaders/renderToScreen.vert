#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 mat4_Model;
uniform mat4 mat4_Camera_MVP;
uniform mat4 mat4_Light_MVP;

out VS_FS_INTERFACE {
    vec3 normal;
    vec3 proj;
} vertex;

void main() {
    vec4 lightSpace = mat4_Light_MVP * vec4(pos, 1);
    vec3 proj = lightSpace.xyz / lightSpace.w;
    proj = proj * 0.5 + 0.5;
    vertex.proj = proj;
    gl_Position = mat4_Camera_MVP * vec4(pos, 1);
    vertex.normal = (mat4_Model * vec4(normal, 0)).xyz;
}
