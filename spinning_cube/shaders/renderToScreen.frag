#version 330 core

layout (location = 0) out vec4 color;

in VS_FS_INTERFACE {
    vec3 normal;
    vec3 proj;
} vertex;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
vec4 black = vec4(0);
vec4 white = vec4(1);
vec4 matColor = vec4(1.0f, 1, 1, 1.0f);

uniform sampler2DShadow lightmap;

void main() {
    float d = dot(vertex.normal, lightDirection);

    float bias = max(0.05 * (1-d), 0.005);  
    vec3 proj = vertex.proj;
    // proj.z -= bias;
    
    float isLit = texture(
        lightmap,
        proj
        // vec3(vertex.proj.xy, vertex.proj.z - 0.0005)
        );

    // d = dot(lightDir, vertex.normal.xyz);

    // d = dot(lightDirection, vertex.normal);
    float facingLight = step(d, 0);
    facingLight = clamp(-d, 0, 1);
    // d = clamp(d, 0, 1);
    color = mix(black, matColor, facingLight * isLit);
    // color = mix(white, color, step(0, vertex.position.x));
    // color = mix(white, color, step(0, vertex.position.y));
} 
