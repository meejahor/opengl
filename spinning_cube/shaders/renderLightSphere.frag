#version 330 core

layout (location = 0) out vec4 lighting;

vec4 white = vec4(1);
vec4 black = vec4(0);

uniform vec3 lightPos;
uniform float lightRadius;
uniform vec2 textureSize;
uniform sampler2D texture_worldPos;
uniform sampler2D texture_normals;

void main() {
    vec3 worldPos = texture(texture_worldPos, gl_FragCoord.xy / textureSize).xyz;
    vec3 offset = worldPos - lightPos;
    float dist = length(offset);
    dist /= lightRadius;
    dist = min(dist, 1);
    dist *= dist;
    dist *= dist;
    dist *= dist;
    dist *= dist;
    lighting = mix(white, black, dist);

    vec3 normal = texture(texture_normals, gl_FragCoord.xy / textureSize).rgb;
    normal -= 0.5;
    normal *= 2;
    vec3 angleToLight = lightPos - worldPos;
    angleToLight = normalize(angleToLight);
    float d = dot(normal, angleToLight);
    d = clamp(d, 0, 1);
    lighting = mix(black, lighting, d);
}
