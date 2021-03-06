#version 330 core

layout (location = 0) out vec4 worldpos;
layout (location = 1) out vec4 normal;
layout (location = 2) out vec4 albedo;

in VS_FS_INTERFACE {
    vec4 worldpos;
    vec3 normal;
    vec2 uv;
} vertex;

uniform sampler2D texture_albedo;

void main() {
    worldpos = vertex.worldpos;
    normal = vec4(vertex.normal, gl_FragCoord.z);
    albedo = texture(texture_albedo, vertex.uv);
}
