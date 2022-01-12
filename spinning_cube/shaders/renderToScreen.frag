#version 330 core

layout (location = 0) out vec4 color;

in VS_FS_INTERFACE {
    vec3 normal;
    vec3 proj;
} vertex;

vec3 lightPosition;
vec3 lightDirection;
vec4 black = vec4(0);
vec4 white = vec4(1);
vec4 matColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

uniform sampler2DShadow lightmap;

void main() {
    vec3 proj = vertex.proj;
    float d = dot(vertex.normal, lightDirection);

    float bias = max(0.01 * (1.0 - d), 0.005);  
    proj.z -= bias;
    
    float isLit = texture(
        lightmap,
        proj
        // vec3(vertex.proj.xy, vertex.proj.z - 0.0005)
        );

    // d = dot(lightDir, vertex.normal.xyz);

    // d = dot(lightDirection, vertex.normal);
    d = step(d, 0);
    // d = clamp(d, 0, 1);
    color = mix(black, matColor, d * isLit);
    // color = mix(white, color, step(0, vertex.position.x));
    // color = mix(white, color, step(0, vertex.position.y));
} 
