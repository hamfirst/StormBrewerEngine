
#include "Engine/EngineCommon.h"
#include "Engine/Text/TextBufferBuilder.h"
#include "Engine/Text/TextManager.h"

TextBufferBuilder::TextBufferBuilder() :
  m_FontId(kInvalidFontId)
{

}

void TextBufferBuilder::Reset()
{
  m_Verts.clear();
  m_Indicies.clear();

  m_FontId = kInvalidFontId;
}