#version 300 es

//! F! Polyline: Opaque

#define TEXTURE texture
#define TEXTURE_CUBE texture
precision highp float;
precision highp int;

const uint kShaderBit_Monochrome = 1u;
const uint kShaderBit_NonUniformColor = 2u;
const uint kShaderBit_OITFlatAlphaWeight = 4u;
const uint kShaderBit_OITScaleOutput = 8u;
const uint kShaderBit_IgnoreNonLocatable = 16u;
uniform float u_shaderFlags;
in vec4 v_lnInfo;
in vec2 v_texc;
uniform vec3 u_frustum;
const float kFrustumType_Ortho2d = 0.0;
const float kFrustumType_Ortho3d = 1.0;
const float kFrustumType_Perspective = 2.0;
uniform sampler2D u_lineCodeTexture;
bool discardByLineCode = false;
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

vec4 finalizeBaseColor(vec4 baseColor) {
  if (v_texc.x >=
      0.0) { // v_texc = (-1,-1) for solid lines - don't bother with any of this
    vec4 texColor = TEXTURE(u_lineCodeTexture, v_texc);
    discardByLineCode = (0.0 == texColor.r);
  }

  if (v_lnInfo.w > 0.5) { // line needs pixel trimming
    // calculate pixel distance from pixel center to expected line center,
    // opposite dir from major
    vec2 dxy = gl_FragCoord.xy - v_lnInfo.xy;
    if (v_lnInfo.w < 1.5) // not x-major
      dxy = dxy.yx;

    float dist = v_lnInfo.z * dxy.x - dxy.y;
    float distA = abs(dist);
    if (distA > 0.5 || (distA == 0.5 && dist < 0.0))
      discardByLineCode = true; // borrow this flag to force discard
  }

  return baseColor;
}

bool checkForDiscard(vec4 baseColor) { return discardByLineCode; }

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
  vec4 baseColor = computeBaseColor();
  baseColor = finalizeBaseColor(baseColor);
  if (checkForDiscard(baseColor)) {
    discard;
    return;
  }
  baseColor = applyMonochrome(baseColor);
  baseColor = reverseWhiteOnWhite(baseColor);
  assignFragData(baseColor);
}
