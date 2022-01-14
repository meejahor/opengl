#version 330 core

out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D depthTexture;
uniform sampler2D normalsTexture;

void main() {
    // color = vec4(0, 0, 1, 1);
    // color = vec4(texture(depthTexture, vertex.uv).r);
    color = texture(normalsTexture, vertex.uv);
    
    // vec4 c = texture(colorTexture, vertex.uv);
    // vec4 d = texture(normalsTexture, vertex.uv);
    // d -= 0.5;
    // d *= 2;
    // color = c*d;
}
