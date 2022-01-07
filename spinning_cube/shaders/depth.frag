#version 330 core

// layout (location = 0) out float fragmentdepth;

void main() {
    gl_FragDepth = 1;
    // fragmentdepth = 0;
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
