#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 matrix_mvp;
uniform mat4 matrix_model;

out VS_FS_INTERFACE {
    // vec3 position;
    vec3 normal;
} vertex;

void main() {
    gl_Position = matrix_mvp * vec4(pos, 1);
    // vertex.position = (matrix_model * vec4(pos, 1)).xyz;
    vertex.normal = (matrix_model * vec4(normal, 0)).xyz;
}
