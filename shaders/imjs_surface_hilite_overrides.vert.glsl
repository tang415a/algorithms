#version 300 es

//! V! Surface: Opaque; hilite; overrides

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
uniform mat4 u_proj;
uniform mat4 u_mv;
out float v_surfaceFlags;
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
out vec2 v_texCoord;
uniform vec4 u_qTexCoordParams;
vec3 g_featureIndex;
vec4 g_featureAndMaterialIndex;
const uint kOvrBit_Visibility = 1u;
const uint kOvrBit_Rgb = 2u;
const uint kOvrBit_Alpha = 4u;
const uint kOvrBit_IgnoreMaterial = 8u;
const uint kOvrBit_Flashed = 16u;
const uint kOvrBit_NonLocatable = 32u;
const uint kOvrBit_LineCode = 64u;
const uint kOvrBit_Weight = 128u;
const uint kOvrBit_Hilited = 1u;
const uint kOvrBit_Emphasized = 2u;
vec4 linear_feature_overrides = vec4(0.0);
bool feature_ignore_material = false;
float g_feature_stepX;
vec2 g_feature_center;
vec2 feature_texCoord;
uniform sampler2D u_featureLUT;
uniform vec2 u_featureParams;
out float v_feature_hilited;
const uint kEmphBit_Hilite = 1u;
const uint kEmphBit_Emphasize = 2u;
const uint kEmphBit_Flash = 4u;
const float kEmphFlag_Hilite = 1.0;
const float kEmphFlag_Emphasize = 2.0;
const float kEmphFlag_Flash = 4.0;
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

float computeSurfaceFlags() {
  float flags = u_surfaceFlags;
  if (feature_ignore_material) {
    bool hasTexture =
        0.0 != fract(flags / 2.0); // kSurfaceMask_HasTexture = 1.0...
    if (hasTexture) {
      flags -= kSurfaceMask_HasTexture;
      if (flags >=
          kSurfaceMask_MultiplyAlpha) // NB: This only works if MultiplyAlpha is
                                      // the largest flag!!!
        flags -= kSurfaceMask_MultiplyAlpha;
    }

    flags += kSurfaceMask_IgnoreMaterial;
  }

  return flags;
}

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractSurfaceBit(uint flag) {
  return extractNthBit(floor(v_surfaceFlags + 0.5), flag);
}

bool isSurfaceBitSet(uint flag) { return 0.0 != extractSurfaceBit(flag); }

// params.xy = origin. params.zw = scale.
vec2 unquantize2d(vec2 qpos, vec4 params) {
  return params.xy + params.zw * qpos;
}

vec2 computeTexCoord() {
  vec2 tc = g_vertexBaseCoords;
  tc.x += 3.0 * g_vert_stepX;
  vec4 rgba = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  vec2 qcoords = vec2(decodeUInt16(rgba.xy), decodeUInt16(rgba.zw));
  return mix(vec2(0.0), unquantize2d(qcoords, u_qTexCoordParams),
             extractSurfaceBit(kSurfaceBit_HasTexture));
}

float getFeatureIndex() {
  g_featureIndex = g_featureAndMaterialIndex.xyz;
  ;
  return decodeUInt24(g_featureIndex);
}
vec2 compute_feature_coords(float index) {
  return computeLUTCoords(index, u_featureParams.xy, g_feature_center, 2.0);
}

vec2 computeFeatureTextureCoords() {
  return compute_feature_coords(getFeatureIndex());
}

vec4 getFirstFeatureRgba() {
  feature_texCoord = computeFeatureTextureCoords();
  return TEXTURE(u_featureLUT, feature_texCoord);
}

vec4 computePosition(vec4 rawPos) {
  vec4 pos = MAT_MV * rawPos;

  return u_proj * pos;
}

void computeFeatureOverrides() {
  vec4 value = getFirstFeatureRgba();
  float flags = value.g * 256.0;
  v_feature_hilited =
      kEmphFlag_Hilite * extractNthBit(flags, kOvrBit_Hilited) +
      kEmphFlag_Emphasize * extractNthBit(flags, kOvrBit_Emphasized);
}

bool checkForDiscard() { return 0.0 == v_feature_hilited; }

void main() {
  g_vert_stepX = 1.0 / u_vertParams.x;
  float vert_stepY = 1.0 / u_vertParams.y;
  g_vert_center = vec2(0.5 * g_vert_stepX, 0.5 * vert_stepY);

  g_vertexLUTIndex = decodeUInt24(a_pos);
  g_vertexBaseCoords = compute_vert_coords(g_vertexLUTIndex);

  vec2 tc = g_vertexBaseCoords;
  tc.x += g_vert_stepX * 2.0;
  g_featureAndMaterialIndex = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);

  g_feature_stepX = 1.0 / u_featureParams.x;
  float feature_stepY = 1.0 / u_featureParams.y;
  g_feature_center = vec2(0.5 * g_feature_stepX, 0.5 * feature_stepY);

  vec4 rawPosition = unquantizeVertexPosition(a_pos, u_qOrigin, u_qScale);
  computeFeatureOverrides();
  if (checkForDiscard()) {
    gl_Position = vec4(2.0, 2.0, 2.0, 1.0);
    return;
  }
  gl_Position = computePosition(rawPosition);
  v_surfaceFlags = computeSurfaceFlags();
  v_texCoord = computeTexCoord();
}
