#version 330 core

layout (location = 0) out vec4 color;
// layout (location = 0) out float fragmentdepth;

void main() {
    color = vec4(0, 1, 0, 1);

    // gl_FragDepth = 0.5;
    // fragmentdepth = 0.5;
    // return;

    // float depth = gl_Position.z / gl_Position.w;
    // depth *= 0.5;
    // depth += 1;
    // fragmentdepth = depth;
    // return;

    // if (depth < 0) {
    //     fragmentdepth = 0;
    // } else {
    //     fragmentdepth = 1;
    // }
}
