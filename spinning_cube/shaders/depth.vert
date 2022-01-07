#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 mat4_LightMVP;

void main() {
    gl_Position = mat4_LightMVP * vec4(pos, 1);
}
