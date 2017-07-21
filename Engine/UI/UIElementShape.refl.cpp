
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementShape.refl.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"

int UIElementShape::Type = 6;

UIElementShape::UIElementShape(const UIElementShapeInitData & init_data, const UIElementShapeData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementShape::Update()
{
  UIElement::Update();
  SetActiveArea(Box::FromPoints(Vector2(m_Data.m_StartX, m_Data.m_StartY), Vector2(m_Data.m_EndX, m_Data.m_EndY)));
  SetOffset(Vector2(m_Data.m_StartX, m_Data.m_StartY));
}

void UIElementShape::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  if (m_RenderDelegate)
  {
    m_RenderDelegate(*this, render_state, offset);
  }
  else
  {
    RenderDefault(render_state, render_util, offset);
  }

  UIElement::Render(render_state, render_util, offset);
}

void UIElementShape::RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  GeometryVertexBufferBuilder builder;
  auto c = Color(m_Data.m_ColorR, m_Data.m_ColorG, m_Data.m_ColorB, m_Data.m_ColorA);

  if (m_Data.m_Shape == kUIElementShapeRectangle)
  {
    builder.Rectangle(Vector2f(m_Data.m_StartX, m_Data.m_StartY), Vector2f(m_Data.m_EndX, m_Data.m_EndY), m_Data.m_EdgeWidth, c);
  }
  else if (m_Data.m_Shape == kUIElementShapeFilledRectangle)
  {
    builder.FilledRectangle(Vector2f(m_Data.m_StartX, m_Data.m_StartY), Vector2f(m_Data.m_EndX, m_Data.m_EndY), c);
  }
  else if (m_Data.m_Shape == kUIElementShapeCircle)
  {
    auto center_x = (m_Data.m_StartX + m_Data.m_EndX) / 2.0f;
    auto center_y = (m_Data.m_StartY + m_Data.m_EndY) / 2.0f;

    auto size_x = m_Data.m_EndX - m_Data.m_StartX;
    auto size_y = m_Data.m_EndY - m_Data.m_StartY;

    builder.Ellipse(Vector2f(center_x, center_y), size_x, size_y, m_Data.m_EdgeWidth, c, 20);
  }
  else if (m_Data.m_Shape == kUIElementShapeFilledCircle)
  {
    auto center_x = (m_Data.m_StartX + m_Data.m_EndX) / 2.0f;
    auto center_y = (m_Data.m_StartY + m_Data.m_EndY) / 2.0f;

    auto size_x = m_Data.m_EndX - m_Data.m_StartX;
    auto size_y = m_Data.m_EndY - m_Data.m_StartY;

    builder.FilledEllipse(Vector2f(center_x, center_y), size_x, size_y, c, 20);
  }

  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), (RenderVec2)offset);

  render_util.GetDefaultTexture().BindTexture(0);

  builder.DrawDefault(render_state, render_util, &shader);
}

const UIElementShapeInitData & UIElementShape::GetInitData()
{
  return m_InitData;
}

UIElementShapeData & UIElementShape::GetData()
{
  return m_Data;
}

void UIElementShape::SetCustomRenderCallback(Delegate<void, UIElementShape &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

