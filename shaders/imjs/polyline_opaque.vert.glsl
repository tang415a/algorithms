#version 300 es

//! V! Polyline: Opaque

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
const uint kShaderBit_Monochrome = 1u;
const uint kShaderBit_NonUniformColor = 2u;
const uint kShaderBit_OITFlatAlphaWeight = 4u;
const uint kShaderBit_OITScaleOutput = 8u;
const uint kShaderBit_IgnoreNonLocatable = 16u;
uniform float u_shaderFlags;
uniform mat4 u_mvp;
uniform mat4 u_viewportTransformation;
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
uniform mat4 u_proj;
uniform mat4 u_mv;
uniform vec4 u_viewport;
vec4 g_windowPos;
vec4 g_prevPos;
vec4 g_nextPos;
vec2 g_windowDir;
uniform float u_lineWeight;
float g_lineWeight;
float miterAdjust = 0.0;
out vec4 v_lnInfo;
uniform float u_lineCode;
float g_lineCode;
out vec2 v_texc;
uniform vec3 u_frustum;
const float kFrustumType_Ortho2d = 0.0;
const float kFrustumType_Ortho3d = 1.0;
const float kFrustumType_Perspective = 2.0;
uniform vec4 u_color;
out vec4 v_color;
in vec3 a_pos;
in vec3 a_prevIndex;
in vec3 a_nextIndex;
in float a_param;

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

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractShaderBit(uint flag) {
  return extractNthBit(floor(u_shaderFlags + 0.5), flag);
}

bool isShaderBitSet(uint flag) { return 0.0 != extractShaderBit(flag); }

vec4 modelToWindowCoordinates(vec4 position, vec4 next) {
  if (kRenderPass_ViewOverlay == u_renderPass ||
      kRenderPass_Background == u_renderPass) {
    vec4 q = MAT_MVP * position;
    q.xyz /= q.w;
    q.xyz = (u_viewportTransformation * vec4(q.xyz, 1.0)).xyz;
    return q;
  }

  // Negative values are in front of the camera (visible).
  float s_maxZ = -u_frustum.x; // use -near (front) plane for segment drop test
                               // since u_frustum's near & far are pos.
  vec4 q = MAT_MV * position;  // eye coordinates.
  vec4 n = MAT_MV * next;

  if (q.z > s_maxZ) {
    if (n.z > s_maxZ)
      return vec4(0.0, 0.0, 1.0, 0.0); // Entire segment behind eye.

    float t = (s_maxZ - q.z) / (n.z - q.z);

    q.x += t * (n.x - q.x);
    q.y += t * (n.y - q.y);
    q.z = s_maxZ; // q.z + (s_maxZ - q.z) * (s_maxZ - q.z) / n.z - q.z
  }
  q = u_proj * q;
  q.xyz /= q.w; // normalized device coords
  q.xyz = (u_viewportTransformation * vec4(q.xyz, 1.0)).xyz; // window coords
  return q;
}

// params.xy = origin. params.zw = scale.
vec2 unquantize2d(vec2 qpos, vec4 params) {
  return params.xy + params.zw * qpos;
}

float computeLineWeight() { return g_lineWeight; }

void adjustWidth(inout float width, vec2 d2, vec2 org) {
  // calculate slope based width adjustment for non-AA lines, widths 1 to 4
  vec2 d2A = abs(d2);
  const float s_myFltEpsilon =
      0.0001; // limit test resolution to 4 digits in case 24 bit (s16e7) is
              // used in hardware
  if (d2A.y > s_myFltEpsilon && width < 4.5) {
    float len = length(d2A);
    float tan = d2A.x / d2A.y;

    if (width < 1.5) { // width 1
      if (tan <= 1.0)
        width = d2A.y / len;
      else
        width = d2A.x / len;
      // width 1 requires additional adjustment plus trimming in frag shader
      // using v_lnInfo
      width *= 1.01;
      v_lnInfo.xy = org;
      v_lnInfo.w = 1.0; // set flag to do trimming
      // set slope in v_lnInfo.z
      if (d2A.x - d2A.y > s_myFltEpsilon) {
        v_lnInfo.z = d2.y / d2.x;
        v_lnInfo.w += 2.0; // add in x-major flag
      } else
        v_lnInfo.z = d2.x / d2.y;

    } else if (width < 2.5) { // width 2
      if (tan <= 0.5)
        width = 2.0 * d2A.y / len;
      else
        width = (d2A.y + 2.0 * d2A.x) / len;

    } else if (width < 3.5) { // width 3
      if (tan <= 1.0)
        width = (3.0 * d2A.y + d2A.x) / len;
      else
        width = (d2A.y + 3.0 * d2A.x) / len;

    } else { // if (width < 4.5) // width 4
      if (tan <= 0.5)
        width = (4.0 * d2A.y + d2A.x) / len;
      else if (tan <= 2.0)
        width = (3.0 * d2A.y + 3.0 * d2A.x) / len;
      else
        width = (d2A.y + 4.0 * d2A.x) / len;
    }
  }
}

vec4 decodePosition(vec3 baseIndex) {
  float index = decodeUInt24(baseIndex);
  vec2 tc = compute_vert_coords(index);
  vec4 e0 = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  tc.x += g_vert_stepX;
  vec4 e1 = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  vec3 qpos =
      vec3(decodeUInt16(e0.xy), decodeUInt16(e0.zw), decodeUInt16(e1.xy));
  return unquantizePosition(qpos, u_qOrigin, u_qScale);
}
float computeLineCode() { return g_lineCode; }

vec2 computeLineCodeTextureCoords(vec2 windowDir, vec4 projPos, float adjust) {
  vec2 texc;
  float lineCode = computeLineCode();
  if (0.0 == lineCode) {
    // Solid line - tell frag shader not to bother.
    texc = vec2(-1.0, -1.0);
  } else {
    const float imagesPerPixel = 1.0 / 32.0;
    const float textureCoordinateBase =
        8192.0; // Temp workardound for clipping problem in perspective views
                // (negative values don't seem to interpolate correctly).

    if (abs(windowDir.x) > abs(windowDir.y))
      texc.x = textureCoordinateBase +
               imagesPerPixel * (projPos.x + adjust * windowDir.x);
    else
      texc.x = textureCoordinateBase +
               imagesPerPixel * (projPos.y + adjust * windowDir.y);

    const float numLineCodes =
        16.0; // NB: Actually only 10, but texture is 16px tall because it needs
              // to be a power of 2.
    const float rowsPerCode = 1.0;
    const float numRows = numLineCodes * rowsPerCode;
    const float centerY = 0.5 / numRows;
    const float stepY = rowsPerCode / numRows;
    texc.y = stepY * lineCode + centerY;
  }

  return texc;
}

vec4 computePosition(vec4 rawPos) {
  const float kNone = 0.0, kSquare = 1.0 * 3.0, kMiter = 2.0 * 3.0,
              kMiterInsideOnly = 3.0 * 3.0, kJointBase = 4.0 * 3.0,
              kNegatePerp = 8.0 * 3.0, kNegateAlong = 16.0 * 3.0,
              kNoneAdjWt = 32.0 * 3.0;

  v_lnInfo = vec4(0.0, 0.0, 0.0, 0.0); // init and set flag to false

  vec4 pos = MAT_MVP * rawPos;

  vec4 next = g_nextPos;
  g_windowPos = modelToWindowCoordinates(rawPos, next);

  if (g_windowPos.w == 0.0)
    return g_windowPos;

  float param = a_param;
  float weight = computeLineWeight();
  float scale = 1.0, directionScale = 1.0;

  if (param >= kNoneAdjWt)
    param -= kNoneAdjWt;

  if (param >= kNegateAlong) {
    directionScale = -directionScale;
    param -= kNegateAlong;
  }

  if (param >= kNegatePerp) {
    scale = -1.0;
    param -= kNegatePerp;
  }

  vec4 projNext = modelToWindowCoordinates(next, rawPos);
  g_windowDir = projNext.xy - g_windowPos.xy;

  if (param < kJointBase) {
    vec2 dir = (directionScale > 0.0) ? g_windowDir : -g_windowDir;
    vec2 pos = (directionScale > 0.0) ? g_windowPos.xy : projNext.xy;
    adjustWidth(weight, dir, pos);
  }

  if (kNone != param) {
    vec2 delta = vec2(0.0);
    vec4 prev = g_prevPos;
    vec4 projPrev = modelToWindowCoordinates(prev, rawPos);
    vec2 prevDir = g_windowPos.xy - projPrev.xy;
    float thisLength =
        sqrt(g_windowDir.x * g_windowDir.x + g_windowDir.y * g_windowDir.y);
    const float s_minNormalizeLength =
        1.0E-5; // avoid normalizing zero length vectors.
    float dist = weight / 2.0;

    if (thisLength > s_minNormalizeLength) {
      g_windowDir /= thisLength;

      float prevLength = sqrt(prevDir.x * prevDir.x + prevDir.y * prevDir.y);

      if (prevLength > s_minNormalizeLength) {
        prevDir /= prevLength;
        const float s_minParallelDot = -.9999, s_maxParallelDot = .9999;
        float prevNextDot = dot(prevDir, g_windowDir);

        if (prevNextDot < s_minParallelDot ||
            prevNextDot >
                s_maxParallelDot) // No miter if parallel or antiparallel.
          param = kSquare;
      } else
        param = kSquare;
    } else {
      g_windowDir = -normalize(prevDir);
      param = kSquare;
    }

    vec2 perp = scale * vec2(-g_windowDir.y, g_windowDir.x);

    if (param == kSquare) {
      delta = perp;
    } else {
      vec2 bisector = normalize(prevDir - g_windowDir);
      float dotP = dot(bisector, perp);

      if (dotP != 0.0) { // Should never occur - but avoid divide by zero.
        const float maxMiter = 3.0;
        float miterDistance = 1.0 / dotP;

        if (param == kMiter) { // Straight miter.
          delta =
              (abs(miterDistance) > maxMiter) ? perp : bisector * miterDistance;

        } else if (param ==
                   kMiterInsideOnly) { // Miter at inside, square at outside (to
                                       // make room for joint).
          delta = (dotP > 0.0 || abs(miterDistance) > maxMiter)
                      ? perp
                      : bisector * miterDistance;

        } else {
          const float jointTriangleCount = 3.0;
          float ratio = (param - kJointBase) /
                        jointTriangleCount; // 3 triangles per half-joint as
                                            // defined in Graphics.cpp
          delta = normalize((1.0 - ratio) * bisector +
                            (dotP < 0.0 ? -ratio : ratio) *
                                perp); // Miter/Straight combination.
        }
      }
    }

    miterAdjust = dot(g_windowDir, delta) *
                  dist; // Not actually used for hilite shader but meh.
    pos.x += dist * delta.x * 2.0 * pos.w / u_viewport.z;
    pos.y += dist * delta.y * 2.0 * pos.w / u_viewport.w;
  }

  return pos;
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

  g_prevPos = decodePosition(a_prevIndex);
  g_nextPos = decodePosition(a_nextIndex);

  g_lineWeight = u_lineWeight;

  g_lineCode = u_lineCode;

  vec4 rawPosition = unquantizeVertexPosition(a_pos, u_qOrigin, u_qScale);
  vec4 baseColor = computeBaseColor();
  v_color = baseColor;
  gl_Position = computePosition(rawPosition);
  v_texc = computeLineCodeTextureCoords(g_windowDir, g_windowPos, miterAdjust);
}
