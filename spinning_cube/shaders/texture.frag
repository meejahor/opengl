#version 330 core

layout (location = 0) out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D renderedTexture;

void main() {
    color = texture(renderedTexture, vertex.uv);
    // color = vec4(1);
    // color = vec4(0.1, 0, 0, 1);
    // color = vec4(1);
    // color += 0.5;
    // color.g += 0.5;
    // color.b += 0.5;
    // color.a += 0.5;
    // color = vec4(0.5);
}
