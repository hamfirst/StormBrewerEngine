#pragma once

#include "Engine/Rendering/ShaderLiteral.h"


static const char * kFrameEditorFragmentShader = SHADER_LITERAL(
  precision highp float;

  varying vec2 v_Position;
  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;
  uniform vec4 u_Color;
  uniform vec2 u_ActualScreenSize;

  void main()
  {
    vec2 frag_coord = floor(v_Position.xy * u_ActualScreenSize * 0.25);
    float x = fract((frag_coord.x + frag_coord.y) * 0.5);

    float a_inv = (1.0 - v_Color.a);
    float a_min = 1.0 - sqrt(a_inv);
    float a_max = 1.0 - a_inv * a_inv;

    float a = (x < 0.5 ? a_min : a_max);

    vec4 color = texture2D(u_Texture, fract(v_TexCoord)) * v_Color * u_Color;

    color.a *= a;
    gl_FragColor = color;
  }
);

