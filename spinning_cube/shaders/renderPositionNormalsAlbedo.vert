#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 mat4_Model;
uniform mat4 mat4_Camera_MVP;

out VS_FS_INTERFACE {
    vec4 worldpos;
    vec3 normal;
} vertex;

void main() {
    vertex.worldpos = mat4_Model * vec4(pos, 1);
    gl_Position = mat4_Camera_MVP * vec4(pos, 1);
    vec3 n = (mat4_Model * vec4(normal, 1)).xyz;
    n *= 0.5;
    n += 0.5;
    vertex.normal = n;
}
