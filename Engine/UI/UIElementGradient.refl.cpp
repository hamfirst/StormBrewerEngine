
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementGradient.refl.h"

#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"

int UIElementGradient::Type = 2;

UIElementGradient::UIElementGradient(const UIElementGradientInitData & init_data, const UIElementGradientData & data) :
  m_InitData(init_data),
  m_Data(data),
  m_VertexBuffer(true)
{

}

void UIElementGradient::Update()
{
  UIElement::Update();
}

void UIElementGradient::Render(RenderState & render_state, RenderUtil & render_util)
{
  if (m_RenderDelegate)
  {
    m_RenderDelegate(*this, render_state);
  }
  else
  {
    RenderDefault(render_state, render_util);
  }
}

void UIElementGradient::RenderDefault(RenderState & render_state, RenderUtil & render_util)
{
  auto bl = Color(m_Data.m_BLColorR, m_Data.m_BLColorG, m_Data.m_BLColorB, m_Data.m_BLColorA);
  auto tl = Color(m_Data.m_TLColorR, m_Data.m_TLColorG, m_Data.m_TLColorB, m_Data.m_TLColorA);
  auto br = Color(m_Data.m_BRColorR, m_Data.m_BRColorG, m_Data.m_BRColorB, m_Data.m_BRColorA);
  auto tr = Color(m_Data.m_TRColorR, m_Data.m_TRColorG, m_Data.m_TRColorB, m_Data.m_TRColorA);

  VertexInfo verts[6];
  verts[0].m_Color = bl;
  verts[0].m_Position = RenderVec2{ m_Data.m_StartX, m_Data.m_StartY };
  verts[0].m_TexCoord = {};
  verts[1].m_Color = tl;
  verts[1].m_Position = RenderVec2{ m_Data.m_StartX, m_Data.m_EndY };
  verts[1].m_TexCoord = {};
  verts[2].m_Color = tr;
  verts[2].m_Position = RenderVec2{ m_Data.m_EndX, m_Data.m_EndY };
  verts[2].m_TexCoord = {};
  verts[3].m_Color = tl;
  verts[3].m_Position = RenderVec2{ m_Data.m_StartX, m_Data.m_EndY };
  verts[3].m_TexCoord = {};
  verts[4].m_Color = tr;
  verts[4].m_Position = RenderVec2{ m_Data.m_EndX, m_Data.m_EndY };
  verts[4].m_TexCoord = {};
  verts[5].m_Color = br;
  verts[5].m_Position = RenderVec2{ m_Data.m_EndX, m_Data.m_StartY };
  verts[5].m_TexCoord = {};

  gsl::span<VertexInfo> vert_span = gsl::as_span(verts, 6);
  m_VertexBuffer.SetBufferData(vert_span, VertexBufferType::kTriangles);

  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.Bind();

  render_util.GetDefaultTexture().BindTexture(0);

  m_VertexBuffer.Bind();
  m_VertexBuffer.CreateDefaultBinding(shader);
  m_VertexBuffer.Draw();
}

const UIElementGradientInitData & UIElementGradient::GetInitData()
{
  return m_InitData;
}

UIElementGradientData & UIElementGradient::GetData()
{
  return m_Data;
}

void UIElementGradient::SetCustomRenderCallback(Delegate<void, UIElementGradient &, RenderState &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

