#version 300 es

//! V! PointString: Opaque

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
float g_vertexLUTIndex;
vec2 g_vertexBaseCoords;
vec2 g_vertexData2;
uniform sampler2D u_vertLUT;
uniform vec4 u_vertParams;
float g_vert_stepX;
vec2 g_vert_center;
uniform mat4 u_mvp;
uniform float u_lineWeight;
float g_lineWeight;
out float v_roundCorners;
const uint kShaderBit_Monochrome = 1u;
const uint kShaderBit_NonUniformColor = 2u;
const uint kShaderBit_OITFlatAlphaWeight = 4u;
const uint kShaderBit_OITScaleOutput = 8u;
const uint kShaderBit_IgnoreNonLocatable = 16u;
uniform float u_shaderFlags;
uniform vec4 u_color;
out vec4 v_color;
in vec3 a_pos;

vec4 unquantizePosition(vec3 pos, vec3 origin, vec3 scale) {
  return vec4(origin + scale * pos, 1.0);
}

float decodeUInt24(vec3 v) {
  v = v * vec3(1.0, 256.0, 256.0 * 256.0); // v.y <<= 8; v.z <<= 16
  return dot(v, vec3(1.0));                // v.x+v.y+v.z => v.x | v.y | v.z
}

float decodeUInt16(vec2 v) {
  v = v * vec2(1.0, 256.0); // v.y <<= 8
  return dot(v, vec2(1.0)); // v.x+v.y => v.x | v.y
}

vec4 unquantizeVertexPosition(vec3 encodedIndex, vec3 origin, vec3 scale) {
  vec2 tc = g_vertexBaseCoords;
  vec4 enc1 = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  tc.x += g_vert_stepX;
  vec4 enc2 = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  vec3 qpos =
      vec3(decodeUInt16(enc1.xy), decodeUInt16(enc1.zw), decodeUInt16(enc2.xy));
  g_vertexData2 = enc2.zw;
  return unquantizePosition(qpos, origin, scale);
}

vec2 computeLUTCoords(float index, vec2 dimensions, vec2 center, float mult) {
  float baseIndex = index * mult;

  // Fix precision issues wherein mod(x,y) => y instead of 0 when x is multiple
  // of y...
  float epsilon = 0.5 / dimensions.x;
  float yId = floor(baseIndex / dimensions.x + epsilon);
  float xId = baseIndex - dimensions.x * yId; // replaces mod()...

  return center + vec2(xId / dimensions.x, yId / dimensions.y);
}

vec2 compute_vert_coords(float index) {
  return computeLUTCoords(index, u_vertParams.xy, g_vert_center,
                          u_vertParams.z);
}

float computeLineWeight() { return g_lineWeight; }

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractShaderBit(uint flag) {
  return extractNthBit(floor(u_shaderFlags + 0.5), flag);
}

bool isShaderBitSet(uint flag) { return 0.0 != extractShaderBit(flag); }

vec4 computePosition(vec4 rawPos) {
  float lineWeight = computeLineWeight();
  lineWeight +=
      0.5 * float(lineWeight > 4.0); // fudge factor for rounding fat points...
  gl_PointSize = lineWeight;
  return MAT_MVP * rawPos;
}

vec4 computeBaseColor() {
  float colorTableStart =
      u_vertParams.z * u_vertParams.w; // num rgba per-vertex times num vertices
  float colorIndex = decodeUInt16(g_vertexData2);
  vec2 tc = computeLUTCoords(colorTableStart + colorIndex, u_vertParams.xy,
                             g_vert_center, 1.0);
  vec4 lutColor = TEXTURE(u_vertLUT, tc);
  lutColor.rgb /= max(0.0001, lutColor.a);
  vec4 color =
      mix(u_color, lutColor, extractShaderBit(kShaderBit_NonUniformColor));

  return color;
}

void main() {
  g_vert_stepX = 1.0 / u_vertParams.x;
  float vert_stepY = 1.0 / u_vertParams.y;
  g_vert_center = vec2(0.5 * g_vert_stepX, 0.5 * vert_stepY);

  g_vertexLUTIndex = decodeUInt24(a_pos);
  g_vertexBaseCoords = compute_vert_coords(g_vertexLUTIndex);

  g_lineWeight = u_lineWeight;

  vec4 rawPosition = unquantizeVertexPosition(a_pos, u_qOrigin, u_qScale);
  vec4 baseColor = computeBaseColor();
  v_color = baseColor;
  gl_Position = computePosition(rawPosition);
  v_roundCorners = gl_PointSize > 4.0 ? 1.0 : 0.0;
}
