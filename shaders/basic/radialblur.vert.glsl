#version 450
// vk
layout(location = 0) out vec2 outUV;

out gl_PerVertex { vec4 gl_Position; };

// Trick: This shader does not contain any input attributes and generates the
// position and the texture coordinate (passed to the fragment shader) solely
// based on the gl_VertexIndex with the texture coordinates being in the [0..1]
// range for the visible part of the triangle.
// As a triangle, gl_VertexIndex is from 0 to 2 and outUV is: vec2(0, 0),
// vec2(2, 0) and vec2(0, 2) respectively. These three vetices constitue a large
// triangle that covers the full screen.
//    0,0_______       2,0
//     |        |
//     |________|1,1
//
//    0,2
void main() {
  outUV = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
  gl_Position = vec4(outUV * 2.0f - 1.0f, 0.0f, 1.0f);
}