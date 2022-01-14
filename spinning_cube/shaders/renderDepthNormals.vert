#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 mat4_Model;
uniform mat4 mat4_Camera_MVP;

out VS_FS_INTERFACE {
    vec4 normal;
} vertex;

void main() {
    gl_Position = mat4_Camera_MVP * vec4(pos, 1);
    vertex.normal = mat4_Model * vec4(normal, 0);
}
