
#include "Engine/EngineCommon.h"
#include "Engine/Text/TextManager.h"
#include "Foundation/Profiling/Profiling.h"

void RenderProfilerData(RenderState & render_state)
{
  std::string profiler_data = GetProfilerText();
  g_TextManager.SetTextPos(Vector2f(5, render_state.GetRenderHeight() - 10));
  g_TextManager.SetPrimaryColor();
  g_TextManager.SetShadowColor();
  g_TextManager.SetTextMode(TextRenderMode::kOutlined);
  g_TextManager.ClearTextBounds();
  g_TextManager.RenderText(profiler_data.data(), -1, 1, render_state);
}
