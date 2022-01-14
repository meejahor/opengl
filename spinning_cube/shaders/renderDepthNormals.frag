#version 330 core

layout (location=0) out vec4 normal;

in VS_FS_INTERFACE {
    vec4 normal;
} vertex;

void main() {
    normal = vertex.normal;
} 
