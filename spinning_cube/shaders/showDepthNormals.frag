#version 330 core

out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D depthNormalsTexture;

void main() {
    // color = vec4(texture(depthNormalsTexture, vertex.uv).a);
    color = vec4(texture(depthNormalsTexture, vertex.uv).rgb, 1);
}
