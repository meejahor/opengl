#version 330 core

out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D depthTexture;

void main() {
    vec4 col = vec4(texture(depthTexture, vertex.uv).r);
    color = col;
    // fragmentdepth = gl_FragCoord.z;
}
