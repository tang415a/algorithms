#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main(void) {
  vec2 p = (gl_FragCoord.xy);
  float g = p.y + (time);
  float f = cos(p.x) + 0.004;
  g = -mod(g, f);
  gl_FragColor = vec4(0.0, g, 0.0, 1.0);
}