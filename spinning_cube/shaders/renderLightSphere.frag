#version 330 core

layout (location = 0) out vec4 lighting;

vec4 white = vec4(1);
vec4 black = vec4(0);

uniform mat4 mat4_Light_VP;

uniform vec3 lightPos;
uniform float lightRadius;
uniform vec2 textureSize;
uniform sampler2D texture_position;
uniform sampler2D texture_normals;
uniform sampler2DShadow texture_lightmap;

void main() {
    vec3 position = texture(texture_position, gl_FragCoord.xy / textureSize).xyz;
    vec3 offset = position - lightPos;
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
    vec3 angleToLight = lightPos - position;
    angleToLight = normalize(angleToLight);
    float d = dot(normal, angleToLight);
    d = clamp(d, 0, 1);
    lighting = mix(black, lighting, d);

    vec4 lightSpace = mat4_Light_VP * vec4(position, 1);
    vec3 lightmap_uv = lightSpace.xyz / lightSpace.w;
    lightmap_uv = lightmap_uv * 0.5 + 0.5;
    float isLit = texture(texture_lightmap, lightmap_uv);
    lighting = mix(lighting, black, isLit);
}
