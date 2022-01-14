#version 330 core

layout (location = 0) out float depth;
layout (location = 1) out vec4 normal;

in VS_FS_INTERFACE {
    vec4 normal;
} vertex;

void main() {
    depth = 0.5;
    normal = vec4(0, 1, 0, 1);
    // normal = vertex.normal;
} 
