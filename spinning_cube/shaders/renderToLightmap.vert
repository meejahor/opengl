#version 330 core

layout (location = 0) in vec3 pos;

out VS_FS_INTERFACE {
    float depth;
} vertex;

uniform mat4 mat4_Light_MVP;

void main() {
    vec4 lightSpace = mat4_Light_MVP * vec4(pos, 1);
    vec3 proj = lightSpace.xyz / lightSpace.w;
    proj = proj * 0.5 + 0.5;
    vertex.depth = proj.z;
    gl_Position = lightSpace;
}
