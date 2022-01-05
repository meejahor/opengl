#version 330 core

in VS_FS_INTERFACE {
    vec2 uv;
} vertex;

out vec3 color;

uniform sampler2D renderedTexture;

void main(){
    color = texture(renderedTexture, vertex.uv.xy).xyz;
    // color = vec3(1);
}
