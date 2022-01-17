#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform mat4 mat4_Camera_MVP;

void main() {
    gl_Position = mat4_Camera_MVP * vec4(pos, 1);
    vertex.uv = uv;
}
