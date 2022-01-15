#version 330 core

layout (location = 0) out vec4 normal;

in VS_FS_INTERFACE {
    vec3 normal;
} vertex;

void main() {
    normal = vec4(vertex.normal, gl_FragCoord.z);
}
