#version 330 core

layout (location = 0) out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D texture_albedo;
uniform sampler2D texture_lighting;

void main() {
    vec4 albedo = texture(texture_albedo, vertex.uv);
    vec4 lighting = texture(texture_lighting, vertex.uv);
    color = albedo * lighting;
}
