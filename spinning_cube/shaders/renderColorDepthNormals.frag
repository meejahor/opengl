#version 330 core

layout (location=0) out vec4 color;
layout (location=1) out vec4 normal;

in VS_FS_INTERFACE {
    vec4 normal;
} vertex;

void main() {
    color = vec4(1);
    normal = vertex.normal;
} 
