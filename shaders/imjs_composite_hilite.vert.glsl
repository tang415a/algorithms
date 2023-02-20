#version 300 es

//! V! Composite-Hilite

#define TEXTURE texture
#define TEXTURE_CUBE texture
#define MAT_NORM g_nmx
#define MAT_MV u_mv
#define MAT_MVP u_mvp
#define MAT_MODEL u_modelMatrix
precision highp float;
precision highp int;

uniform vec3 u_qScale;
uniform vec3 u_qOrigin;
out vec2 v_texCoord;
in vec3 a_pos;

vec4 unquantizePosition(vec3 pos, vec3 origin, vec3 scale) {
  return vec4(origin + scale * pos, 1.0);
}

vec4 unquantizeVertexPosition(vec3 pos, vec3 origin, vec3 scale) {
  return unquantizePosition(pos, origin, scale);
}

vec4 computePosition(vec4 rawPos) { return rawPos; }

void main() {
  vec4 rawPosition = unquantizeVertexPosition(a_pos, u_qOrigin, u_qScale);
  gl_Position = computePosition(rawPosition);
  v_texCoord = (rawPosition.xy + 1.0) * 0.5;
}
