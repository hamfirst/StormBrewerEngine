#pragma once

#include "Engine/Rendering/VertexDefinition.h"

struct GlyphInfo;

class TextBufferBuilder
{
public:
  TextBufferBuilder() = default;

  TextBufferBuilder(const TextBufferBuilder & rhs) = delete;
  TextBufferBuilder(TextBufferBuilder && rhs) = default;

  TextBufferBuilder & operator = (const TextBufferBuilder & rhs) = delete;
  TextBufferBuilder & operator = (TextBufferBuilder && rhs) = default;

  void Reset();

protected:

  friend class TextManager;
  friend class TextRenderer;

private:
  std::vector<VertexInfo> m_Verts;
  std::vector<uint16_t> m_Indicies;

  int m_FontId = -1;
};
