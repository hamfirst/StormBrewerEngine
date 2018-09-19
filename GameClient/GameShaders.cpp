
#include "GameClient/GameClientCommon.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Rendering/ShaderLiteral.h"


auto kFuturisticGridEffectLayerVertexShader = SHADER_LITERAL(
  attribute vec2 a_Position;
  attribute vec2 a_TexCoord;
  attribute vec4 a_Color;

  void main()
  {
    gl_Position = vec4(a_Position, 0, 1);
  }
);

auto kFuturisticGridEffectLayerFragmentShader = SHADER_LITERAL(

  uniform float iTime;

  float hash(float n)
  {
    return fract(sin(n)*43758.5453);
  }

  vec3 hash(vec3 p)
  {
    float n = cos(dot(p, vec3(17, 1257, 1143)));
    return fract(vec3(2097152, 262144, 32768)*n);
  }

  float noise(float g)
  {
    float p = floor(g);
    float f = fract(g);

    return mix(hash(p), hash(p + 1.0), f);
  }

  float voronoi(vec3 x) {
    vec3 p = floor(x);
    vec3 f = fract(x);

    vec2 res = vec2(5.0);

    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        for (int k = -1; k <= 1; k++)
        {
          vec3 g = vec3(float(i), float(j), float(k));
          vec3 r = g + hash(p + g) - f;

          float d = max(abs(r.x), max(abs(r.y), abs(r.z)));

          if (d < res.x)
          {
            res.y = res.x;
            res.x = d;
          }
          else if (d < res.y)
          {
            res.y = d;
          }
        }
      }
    }

    return res.y - res.x;
  }

  vec3 material(vec3 p)
  {
    float v = 0.1;
    float a = 0.4, f = 0.02;

    for (int i = 0; i < 2; i++)
    {
      float v1 = voronoi(p*f + 5.0);
      float v2 = 0.0;

      if (i == 1)
      {
        v2 = voronoi(p*f*0.3 + 20.0 + 0.1*iTime);

        float va = 0.0, vb = 0.0;
        va = 1.0 - smoothstep(0.0, 0.1, v1);
        vb = 1.0 - smoothstep(0.0, 0.1, v2);
        v += a*pow(abs(va*(0.1 + vb)), 10.0) * 0.3;
      }

      v1 = 1.0 - smoothstep(0.0, 0.2, v1);
      v2 = a*noise(v1*5.5 + 0.1) * float(i == 0 ? 1 : 2);

      v += v2;

      f *= 3.0;
      a *= 0.5;
    }

    return vec3(pow(v, 8.0) + 0.1, pow(v, 7.0) + 0.1, pow(v, 3.0) + 0.1);
  }

  void main() 
  {
    vec4 c = vec4(material(vec3(gl_FragCoord.xy, 0)), 1);
    gl_FragColor = c;
  }
);

void RegisterGameplayShaders()
{
  g_ShaderManager.RegisterShader(kFuturisticGridEffectLayerVertexShader, kFuturisticGridEffectLayerFragmentShader, "FuturisticGrid");
  g_ShaderManager.RegisterShader(SHADER_LITERAL(

      precision highp float;

      varying vec2 v_Position;
      varying vec2 v_TexCoord;
      varying vec4 v_Color;

      uniform sampler2D u_Texture;
      uniform vec4 u_Color;

      void main()
      {
        ivec2 tex_size = textureSize(u_Texture, 0);
        vec2 offset = vec2(1.0 / float(tex_size.x), 1.0 / float(tex_size.y));

        vec2 tex_pos = fract(v_TexCoord);
        vec4 color = texture2D(u_Texture, tex_pos) * v_Color * u_Color;
        vec4 t1 = texture2D(u_Texture, tex_pos + vec2(offset.x, 0));
        vec4 t2 = texture2D(u_Texture, tex_pos - vec2(offset.x, 0));
        vec4 t3 = texture2D(u_Texture, tex_pos + vec2(0, offset.y));
        vec4 t4 = texture2D(u_Texture, tex_pos - vec2(0, offset.y));

        if ((t1.a == 0 || t2.a == 0 || t3.a == 0 || t4.a == 0) && color.a != 0)
        {
          color += vec4(0.5, 0.5, 0.5, 0);
          color.a *= 0.5;
        }
        else
        {
          color *= 0.5;
        }

        gl_FragColor = color;
      }
    ), "EdgeGlow");
}

