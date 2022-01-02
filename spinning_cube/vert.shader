#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos, 1.0f);
    // gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
