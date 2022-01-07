#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 mat4_Model;
uniform mat4 mat4_MVP;
uniform mat4 mat4_LightMVP;

out VS_FS_INTERFACE {
    vec3 normal;
    vec2 uv;
    vec4 shadowCoords;
} vertex;

void main() {
    gl_Position = mat4_MVP * vec4(pos, 1);
    vertex.normal = (mat4_Model * vec4(normal, 0)).xyz;
    vertex.uv = uv;
    vertex.shadowCoords = mat4_LightMVP * vec4(pos, 1);
}
