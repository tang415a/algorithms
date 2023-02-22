#version 300 es

//! F! PointString: Opaque

#define TEXTURE texture
#define TEXTURE_CUBE texture
precision highp float;
precision highp int;

in float v_roundCorners;
const uint kShaderBit_Monochrome = 1u;
const uint kShaderBit_NonUniformColor = 2u;
const uint kShaderBit_OITFlatAlphaWeight = 4u;
const uint kShaderBit_OITScaleOutput = 8u;
const uint kShaderBit_IgnoreNonLocatable = 16u;
uniform float u_shaderFlags;
in vec4 v_color;
uniform float u_reverseWhiteOnWhite;
uniform vec4 u_monoRgb;
uniform float u_renderPass;
const float kRenderPass_Background = 0.0;
const float kRenderPass_OpaqueLinear = 1.0;
const float kRenderPass_OpaquePlanar = 2.0;
const float kRenderPass_OpaqueGeneral = 3.0;
const float kRenderPass_Classification = 4.0;
const float kRenderPass_Translucent = 5.0;
const float kRenderPass_HiddenEdge = 6.0;
const float kRenderPass_Hilite = 7.0;
const float kRenderPass_WorldOverlay = 8.0;
const float kRenderPass_ViewOverlay = 9.0;
const float kRenderPass_PlanarClassification = 15.0;
out vec4 FragColor;

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractShaderBit(uint flag) {
  return extractNthBit(floor(u_shaderFlags + 0.5), flag);
}

bool isShaderBitSet(uint flag) { return 0.0 != extractShaderBit(flag); }

vec4 computeBaseColor() { return v_color; }

/*
gl_PointCoord — contains the coordinate of a fragment within a point

Declaration
in vec2 gl_PointCoord ;

gl_PointCoord is a fragment language input variable that contains the
two-dimensional coordinates indicating where within a point primitive the
current fragment is located. If the current primitive is not a point, then
values read from gl_PointCoord are undefined.

gl_PointCoord.s ranges from 0.0 to 1.0 across the point horizontally from left
to right. If GL_POINT_SPRITE_COORD_ORIGIN is GL_LOWER_LEFT, gl_PointCoord.t
varies from 0.0 to 1.0 vertically from bottom to top. Otherwise, if
GL_POINT_SPRITE_COORD_ORIGIN is GL_UPPER_LEFT then gl_PointCoord.t varies from
0.0 to 1.0 vertically from top to bottom. The default value of
GL_POINT_SPRITE_COORD_ORIGIN is GL_UPPER_LEFT.
*/

bool checkForEarlyDiscard() {
  const vec2 center = vec2(0.5, 0.5); // the center of screen
  vec2 vt = gl_PointCoord - center;
  return dot(vt, vt) * v_roundCorners >=
         0.25; // meets or exceeds radius of circle
}

vec4 applyMonochrome(vec4 baseColor) {
  // Compute lit monochrome color
  vec3 litRgb = baseColor.rgb;
  litRgb = vec3(dot(litRgb, vec3(.222, .707, .071)));
  litRgb *= u_monoRgb.rgb;

  // Select lit or unlit based on u_monoColor.a
  vec4 monoColor = vec4(mix(u_monoRgb.rgb, litRgb, u_monoRgb.a), baseColor.a);

  // Select monochrome or element color based on shader flag
  return mix(baseColor, monoColor, extractShaderBit(kShaderBit_Monochrome));
}

vec4 reverseWhiteOnWhite(vec4 baseColor) {
  const vec3 white = vec3(1.0);
  const vec3 epsilon = vec3(0.0001);
  vec3 color = baseColor.rgb;
  vec3 delta = (color + epsilon) - white;
  vec4 wowColor =
      vec4(baseColor.rgb *
               vec3(float(delta.x <= 0.0 || delta.y <= 0.0 || delta.z <= 0.0)),
           baseColor.a); // set to black if almost white
  return mix(baseColor, wowColor, floor(u_reverseWhiteOnWhite + 0.5));
}

void assignFragData(vec4 baseColor) {
  if (u_renderPass >= kRenderPass_OpaqueLinear &&
      u_renderPass <= kRenderPass_OpaqueGeneral)
    baseColor.a = 1.0;
  else
    baseColor = vec4(baseColor.rgb * baseColor.a, baseColor.a);

  FragColor = baseColor;
}

void main() {
  if (checkForEarlyDiscard()) {
    discard;
    return;
  }
  vec4 baseColor = computeBaseColor();
  baseColor = applyMonochrome(baseColor);
  baseColor = reverseWhiteOnWhite(baseColor);
  assignFragData(baseColor);
}
