
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementShape.refl.meta.h"
#include "Engine/Rendering/GeometryVertexBufferBuilder.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementShapeInitData);
REGISTER_UIELEMENT_DATA(UIElementShape, UIElementShapeInitData, UIElementShapeData);

UIElementType UIElementShape::Type = UIElementType::kShape;

static auto s_LocalInitBlock = StormExprCreateInitBlockForDataType<UIElementShapeData>();
static auto s_AsParentInitBlock = StormExprCreateInitBlockForDataType<UIElementShapeData>("p.");
static auto s_BindingList = StormExprGetBindingList<UIElementShapeData>();

UIElementShape::UIElementShape(const UIElementShapeInitData & init_data, const UIElementShapeData & data) :
  m_InitData(init_data),
  m_Data(data)
{

}

void UIElementShape::Update(float dt)
{
  SetActiveArea(Box::FromPoints(Vector2(m_Data.m_StartX, m_Data.m_StartY), Vector2(m_Data.m_EndX, m_Data.m_EndY)));
  SetOffset(Vector2(m_Data.m_StartX, m_Data.m_StartY));

  UIElement::Update(dt);
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
  if (m_Data.m_Enabled == 0)
  {
    return;
  }

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

    builder.Ellipse(Vector2f(center_x, center_y), size_x / 2.0f, size_y / 2.0f, m_Data.m_EdgeWidth, c, 50);
  }
  else if (m_Data.m_Shape == kUIElementShapeFilledCircle)
  {
    auto center_x = (m_Data.m_StartX + m_Data.m_EndX) / 2.0f;
    auto center_y = (m_Data.m_StartY + m_Data.m_EndY) / 2.0f;

    auto size_x = m_Data.m_EndX - m_Data.m_StartX;
    auto size_y = m_Data.m_EndY - m_Data.m_StartY;

    builder.FilledEllipse(Vector2f(center_x, center_y), size_x / 2.0f, size_y / 2.0f, c, 50);
  }

  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), (RenderVec2)offset);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });

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

NotNullPtr<UIElementDataBase> UIElementShape::GetBaseData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataFrameCenter> UIElementShape::GetFrameCenterData()
{
  return nullptr;
}

NullOptPtr<UIElementDataStartEnd> UIElementShape::GetStartEndData()
{
  return &m_Data;
}

void UIElementShape::SetCustomRenderCallback(Delegate<void, UIElementShape &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

StormExprValueInitBlock & UIElementShape::GetLocalInitBlock()
{
  return s_LocalInitBlock;
}

StormExprValueInitBlock & UIElementShape::GetAsParentInitBlock()
{
  return s_AsParentInitBlock;
}

StormExprBindingList & UIElementShape::GetBindingList()
{
  return s_BindingList;
}


