#version 330 core

layout (location = 0) in vec3 pos;

out VS_FS_INTERFACE {
    vec3 proj;
} vertex;

uniform mat4 mat4_Light_MVP;

void main() {
    vec4 lightSpace = mat4_Light_MVP * vec4(pos, 1);
    vec3 proj = lightSpace.xyz / lightSpace.w;
    proj = proj * 0.5 + 0.5;
    vertex.proj = proj;
    gl_Position = lightSpace;
}
