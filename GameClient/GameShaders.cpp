
#include "GameClient/GameClientCommon.h"

#include "Engine/Shader/ShaderManager.h"
#include "Engine/Rendering/ShaderLiteral.h"

void RegisterGameplayShaders()
{
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

