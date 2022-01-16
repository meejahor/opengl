#version 330 core

out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D depthTexture;

void main() {
    float depth = texture(depthTexture, vertex.uv).r;
    color = vec4(depth);
    // fragmentdepth = gl_FragCoord.z;
}
