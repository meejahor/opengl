#version 330 core

layout (location = 0) out vec4 color;

in VS_FS_INTERFACE {
    // vec3 position;
    vec3 normal;
    vec2 uv;
    vec4 shadowCoords;
} vertex;

vec3 lightDir = vec3(0, 0, 1);
vec4 black = vec4(0);
vec4 white = vec4(1);
vec4 matColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

uniform sampler2D lightmap;

void main() {
    float shadowDepth = texture(lightmap, vertex.shadowCoords.xy).z;
    float fragmentDepth = vertex.shadowCoords.z;

    float d = dot(lightDir, vertex.normal.xyz);
    d = clamp(d, 0, 1);
    d *= step(fragmentDepth, shadowDepth);
    color = mix(black, matColor, d);
    // color = mix(white, color, step(0, vertex.position.x));
    // color = mix(white, color, step(0, vertex.position.y));
} 
