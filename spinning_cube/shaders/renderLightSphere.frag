#version 330 core

layout (location = 0) out vec4 worldpos;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 albedo;

vec4 white = vec4(1);

void main() {
    worldpos = vec4(0);
    normal = vec4(0);
    albedo = white;
}
