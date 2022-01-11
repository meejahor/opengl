#version 330 core

out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D depthTexture;

void main() {
    float depth = texture(depthTexture, vertex.uv).r;
    float col = depth;// == 1 ? 0 : 1;
    color = vec4(col);
    // fragmentdepth = gl_FragCoord.z;
}
