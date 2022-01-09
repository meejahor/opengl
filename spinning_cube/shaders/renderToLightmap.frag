#version 330 core

in VS_FS_INTERFACE {
    vec3 proj;
} vertex;

void main() {
    // gl_FragDepth = gl_FragCoord.z * 0.5;
    // if (vertex.depth > 0.99999999) {
    //     gl_FragDepth = 1;
    // } else {
    //     gl_FragDepth = 0;
    // }
    // // gl_FragDepth = vertex.depth;
}
