#version 330 core

layout (location = 0) out vec4 lighting;

vec4 white = vec4(1);
vec4 black = vec4(0);

uniform vec3 lightPos;
uniform float lightRadius;
uniform vec2 textureSize;
uniform sampler2D texture_worldPos;

void main() {
    vec3 worldPos = texture(texture_worldPos, gl_FragCoord.xy / textureSize).xyz;
    vec3 offset = worldPos - lightPos;
    float dist = length(offset);
    dist *= 1 / lightRadius;
    dist = min(dist, 1);
    dist *= dist;
    lighting = mix(white, black, dist);
}
