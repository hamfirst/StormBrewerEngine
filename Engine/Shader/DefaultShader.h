#pragma once

#include "Engine/Rendering/ShaderLiteral.h"

static const char * kDefaultVertexShader = SHADER_LITERAL(

  attribute vec2 a_Position;
  attribute vec2 a_TexCoord;
  attribute vec4 a_Color;

  varying vec2 v_Position;
  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform vec2 u_ScreenSize;
  uniform vec2 u_Offset;
  uniform vec4 u_Matrix;

  void main()
  {
    vec2 position = vec2(dot(u_Matrix.xy, a_Position), dot(u_Matrix.zw, a_Position));
    position += u_Offset;
    position /= u_ScreenSize;
    position *= 2.0;

    gl_Position = vec4(position, 0, 1);
    v_Position = position;
    v_TexCoord = vec2(a_TexCoord.x, 1.0 - a_TexCoord.y);
    v_Color = a_Color;
  }
);

static const char * kDefaultFragmentShader = SHADER_LITERAL(
  precision highp float;

  varying vec2 v_Position;
  varying vec2 v_TexCoord;
  varying vec4 v_Color;

  uniform sampler2D u_Texture;
  uniform vec4 u_Color;

  void main()
  {
    vec4 color = texture2D(u_Texture, fract(v_TexCoord)) * v_Color * u_Color;
    gl_FragColor = vec4(color.rgb,color.a);
  }
);

