#version 330 core

out vec4 color;

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

uniform sampler2D colorTexture;
uniform sampler2D normalsTexture;

void main() {
    color = texture(normalsTexture, vertex.uv);
}
