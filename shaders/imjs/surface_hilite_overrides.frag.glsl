#version 300 es

//! F! Surface: Opaque; hilite; overrides

#define TEXTURE texture
#define TEXTURE_CUBE texture
precision highp float;
precision highp int;

in float v_surfaceFlags;
const uint kSurfaceBit_HasTexture = 1u;
const uint kSurfaceBit_ApplyLighting = 2u;
const uint kSurfaceBit_HasNormals = 4u;
const uint kSurfaceBit_IgnoreMaterial = 8u;
const uint kSurfaceBit_TransparencyThreshold = 16u;
const uint kSurfaceBit_BackgroundFill = 32u;
const uint kSurfaceBit_HasColorAndNormal = 64u;
const uint kSurfaceBit_OverrideAlpha = 128u;
const uint kSurfaceBit_OverrideRgb = 256u;
const uint kSurfaceBit_NoFaceFront = 512u;
const uint kSurfaceBit_MultiplyAlpha = 1024u;
const float kSurfaceMask_None = 0.0;
const float kSurfaceMask_HasTexture = 1.0;
const float kSurfaceMask_ApplyLighting = 2.0;
const float kSurfaceMask_HasNormals = 4.0;
const float kSurfaceMask_IgnoreMaterial = 8.0;
const float kSurfaceMask_TransparencyThreshold = 16.0;
const float kSurfaceMask_BackgroundFill = 32.0;
const float kSurfaceMask_HasColorAndNormal = 64.0;
const float kSurfaceMask_OverrideAlpha = 128.0;
const float kSurfaceMask_OverrideRgb = 256.0;
const float kSurfaceMask_NoFaceFront = 512.0;
const float kSurfaceMask_MultiplyAlpha = 1024.0;
uniform float u_surfaceFlags;
in vec2 v_texCoord;
uniform sampler2D s_texture;
in float v_feature_hilited;
const uint kEmphBit_Hilite = 1u;
const uint kEmphBit_Emphasize = 2u;
const uint kEmphBit_Flash = 4u;
const float kEmphFlag_Hilite = 1.0;
const float kEmphFlag_Emphasize = 2.0;
const float kEmphFlag_Flash = 4.0;
out vec4 FragColor;

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractSurfaceBit(uint flag) {
  return extractNthBit(floor(v_surfaceFlags + 0.5), flag);
}

bool isSurfaceBitSet(uint flag) { return 0.0 != extractSurfaceBit(flag); }

vec4 sampleSurfaceTexture() { return TEXTURE(s_texture, v_texCoord); }

vec4 computeBaseColor() {
  if (isSurfaceBitSet(kSurfaceBit_HasTexture) &&
      TEXTURE(s_texture, v_texCoord).a <= 0.15)
    return vec4(0.0);

  float flags = floor(v_feature_hilited + 0.5);
  float hilited = extractNthBit(flags, kEmphBit_Hilite);
  float emphasized = (1.0 - hilited) * extractNthBit(flags, kEmphBit_Emphasize);
  return vec4(hilited, emphasized, 0.0, 0.0);
}

void assignFragData(vec4 baseColor) { FragColor = baseColor; }

void main() {
  vec4 baseColor = computeBaseColor();
  assignFragData(baseColor);
}
