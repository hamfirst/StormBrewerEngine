
#include "Engine/EngineCommon.h"
#include "Engine/Rendering/ShaderProgram.h"
#include "Engine/Rendering/VertexAttrib.h"
#include "Engine/Rendering/VertexDefinition.h"

#include "External/gl3w/gl3w.h"

VertexAttrib g_DefaultVertexSpecData[] = 
{
  {
    "a_Position",
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(VertexInfo),
    (void *)offsetof(VertexInfo, m_Position)
  },
  {
    "a_TexCoord",
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(VertexInfo),
    (void *)offsetof(VertexInfo, m_TexCoord)
  },
  {
    "a_Color",
    4,
    GL_FLOAT,
    GL_FALSE,
    sizeof(VertexInfo),
    (void *)offsetof(VertexInfo, m_Color)
  },
};

VertexAttribSpec g_DefaultVertexSpec = 
{
  sizeof(g_DefaultVertexSpecData) / sizeof(g_DefaultVertexSpecData[0]),
  &g_DefaultVertexSpecData[0]
};

