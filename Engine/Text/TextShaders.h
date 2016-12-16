#pragma once

#include "Engine/Rendering/ShaderLiteral.h"

static const char * kBasicTextVertexShader = SHADER_LITERAL(

  attribute vec2 a_Position;
  attribute vec2 a_TexCoord;
  attribute vec4 a_Color;

  varying vec2 v_Position;
  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform vec2 u_ScreenSize;

  void main()
  {
    vec2 position = a_Position;
    position /= u_ScreenSize;
    position -= vec2(0.5, 0.5);
    position *= 2.0;

    gl_Position = vec4(position, 0, 1);
    v_Position = position;
    v_TexCoord = a_TexCoord;
    v_Color = a_Color;
  }
);

static const char * kBasicTextFragmentShader = SHADER_LITERAL(

  varying vec2 v_Position;
  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_GlyphTexture;

  uniform vec4 u_Bounds;

  void main()
  {
    bool oob =
      v_Position.x < u_Bounds.x ||
      v_Position.y < u_Bounds.y ||
      v_Position.x > u_Bounds.z ||
      v_Position.y > u_Bounds.w;

    vec4 color = texture2D(u_GlyphTexture, v_TexCoord).rrrr * v_Color;
    gl_FragColor = oob ? vec4(0, 0, 0, 0) : color;
  }
);
