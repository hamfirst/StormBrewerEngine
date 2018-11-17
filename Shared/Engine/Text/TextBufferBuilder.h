#pragma once

#include "Engine/Rendering/VertexDefinition.h"
#include "Engine/Rendering/VertexList.h"

struct GlyphInfo;

class ENGINE_EXPORT TextBufferBuilder
{
public:
  TextBufferBuilder();

  TextBufferBuilder(const TextBufferBuilder & rhs) = delete;
  TextBufferBuilder(TextBufferBuilder && rhs) = delete;

  TextBufferBuilder & operator = (const TextBufferBuilder & rhs) = delete;
  TextBufferBuilder & operator = (TextBufferBuilder && rhs) = delete;

protected:

  friend class TextManager;
  friend class TextRenderer;

private:
  VertexList m_Verts;

  int m_FontId;
};
