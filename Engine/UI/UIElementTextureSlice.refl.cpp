
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElementTextureSlice.refl.meta.h"

#include "Engine/Rendering/VertexBufferBuilder.h"
#include "Engine/Rendering/RenderState.h"
#include "Engine/Rendering/RenderUtil.h"
#include "Engine/Shader/ShaderManager.h"

#include "Runtime/UI/UIElementTypeRegister.h"

STORM_DATA_DEFAULT_CONSTRUCTION_IMPL(UIElementTextureSliceInitData);
REGISTER_UIELEMENT_DATA(UIElementTextureSlice, UIElementTextureSliceInitData, UIElementTextureSliceData);

UIElementType UIElementTextureSlice::Type = UIElementType::kTextureSlice;

static auto s_LocalInitBlock = StormExprCreateInitBlockForDataType<UIElementTextureSliceData>();
static auto s_AsParentInitBlock = StormExprCreateInitBlockForDataType<UIElementTextureSliceData>("p.");
static auto s_BindingList = StormExprGetBindingList<UIElementTextureSliceData>();

UIElementTextureSlice::UIElementTextureSlice(const UIElementTextureSliceInitData & init_data, const UIElementTextureSliceData & data) :
  m_InitData(init_data),
  m_Data(data),
  m_Texture(TextureAsset::Load(m_InitData.m_SpriteFile.data()))
{

}

void UIElementTextureSlice::Update(float dt)
{
  SetActiveArea(Box::FromPoints(Vector2(m_Data.m_StartX, m_Data.m_StartY), Vector2(m_Data.m_EndX, m_Data.m_EndY)));
  SetOffset(Vector2(m_Data.m_StartX, m_Data.m_StartY));
  UIElement::Update(dt);
  SetActiveArea(Box::FromPoints(Vector2(m_Data.m_StartX, m_Data.m_StartY), Vector2(m_Data.m_EndX, m_Data.m_EndY)));
  SetOffset(Vector2(m_Data.m_StartX, m_Data.m_StartY));
}

void UIElementTextureSlice::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  if (m_Data.m_Enabled == 0)
  {
    return;
  }

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

void UIElementTextureSlice::RenderDefault(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  if ((bool)m_Texture == false || m_Texture->IsLoaded() == false)
  {
    return;
  }

  QuadVertexBufferBuilder buffer_builder;
  Color color = Color(m_Data.m_ColorR, m_Data.m_ColorG, m_Data.m_ColorB, m_Data.m_ColorA);

  QuadVertexBuilderInfo quad;
  quad.m_Color = color;
  quad.m_TextureSize = m_Texture->GetSize();

  if (m_InitData.m_SliceHorizontally && m_InitData.m_SliceVertically)
  {
    // Bottom left
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_StartCutX, m_InitData.m_StartCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_StartCutX, m_InitData.m_StartCutY };
    buffer_builder.AddQuad(quad);

    // Top left
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_EndY - m_InitData.m_EndCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_StartCutX, m_InitData.m_EndCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_EndY - m_InitData.m_EndCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_StartCutX, m_InitData.m_EndCutY };
    buffer_builder.AddQuad(quad);

    // Bottom right
    quad.m_Position.m_Start = Vector2{ m_Data.m_EndX - m_InitData.m_EndCutX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_EndCutX, m_InitData.m_StartCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_EndX - m_InitData.m_EndCutX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_EndCutX, m_InitData.m_StartCutY };
    buffer_builder.AddQuad(quad);

    // Top right
    quad.m_Position.m_Start = Vector2{ m_Data.m_EndX - m_InitData.m_EndCutX, m_Data.m_EndY - m_InitData.m_EndCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_EndCutX, m_InitData.m_EndCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_EndX - m_InitData.m_EndCutX, m_InitData.m_EndY - m_InitData.m_EndCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_EndCutX, m_InitData.m_EndCutY };
    buffer_builder.AddQuad(quad);

    int repeat_width = (int)(m_Data.m_EndX - m_Data.m_StartX - m_InitData.m_StartCutX - m_InitData.m_EndCutX);
    int repeat_height = (int)(m_Data.m_EndY - m_Data.m_StartY - m_InitData.m_StartCutY - m_InitData.m_EndCutY);

    int repeat_texture_width = (int)(m_InitData.m_EndX - m_InitData.m_StartX - m_InitData.m_StartCutX - m_InitData.m_EndCutX);
    int repeat_texture_height = (int)(m_InitData.m_EndX - m_InitData.m_StartX - m_InitData.m_StartCutX - m_InitData.m_EndCutX);

    // Left side
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_StartY + m_InitData.m_StartCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_StartCutX, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_StartY + m_InitData.m_StartCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_EndCutX, repeat_texture_height };
    buffer_builder.AddRepeatingQuad(quad);

    // Right side
    quad.m_Position.m_Start = Vector2{ m_Data.m_EndX - m_InitData.m_EndCutX, m_Data.m_StartY + m_InitData.m_StartCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_EndCutX, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_EndX - m_InitData.m_EndCutX, m_InitData.m_StartY + m_InitData.m_StartCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_EndCutX, repeat_texture_height };
    buffer_builder.AddRepeatingQuad(quad);

    // Bottom side
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX + m_InitData.m_StartCutX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, m_InitData.m_StartCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX + m_InitData.m_StartCutX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, m_InitData.m_StartCutY };
    buffer_builder.AddRepeatingQuad(quad);

    // Top side
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX + m_InitData.m_StartCutX, m_Data.m_EndY - m_InitData.m_EndCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, m_InitData.m_EndCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX + m_InitData.m_StartCutX, m_InitData.m_EndY - m_InitData.m_EndCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, m_InitData.m_EndCutY };
    buffer_builder.AddRepeatingQuad(quad);

    // Center
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX + m_InitData.m_StartCutX, m_Data.m_StartY + m_InitData.m_StartCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX + m_InitData.m_StartCutX, m_InitData.m_StartY + m_InitData.m_StartCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, repeat_texture_height };
    buffer_builder.AddRepeatingQuad(quad);
  }
  else if (m_InitData.m_SliceHorizontally)
  {
    int height = (int)(m_Data.m_EndY - m_Data.m_StartY);
    int texture_height = (int)(m_InitData.m_EndY - m_InitData.m_StartY);

    int repeat_width = (int)(m_Data.m_EndX - m_Data.m_StartX - m_InitData.m_StartCutX - m_InitData.m_EndCutX);
    int repeat_texture_width = (int)(m_Data.m_EndX - m_Data.m_StartX - m_InitData.m_StartCutX - m_InitData.m_EndCutX);

    // Left side
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_StartCutX, height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_StartCutX, texture_height };
    buffer_builder.AddQuad(quad);

    // Center
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX + m_InitData.m_StartCutX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ repeat_width, height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX + m_InitData.m_StartCutX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ repeat_texture_width, texture_height };
    buffer_builder.AddQuad(quad);

    // Right side
    quad.m_Position.m_Start = Vector2{ m_Data.m_EndX - m_InitData.m_EndCutX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ m_InitData.m_EndCutX, height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_EndX - m_InitData.m_EndCutX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ m_InitData.m_EndCutX, texture_height };
    buffer_builder.AddQuad(quad);
  }
  else if (m_InitData.m_SliceVertically)
  {
    int width = (int)(m_Data.m_EndX - m_Data.m_StartX);
    int texture_width = (int)(m_InitData.m_EndX - m_InitData.m_StartX);

    int repeat_height = (int)(m_Data.m_EndY - m_Data.m_StartY - m_InitData.m_StartCutY - m_InitData.m_EndCutY);
    int repeat_texture_height = (int)(m_Data.m_EndY - m_Data.m_StartY - m_InitData.m_StartCutY - m_InitData.m_EndCutY);

    // Bottom side
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_StartY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ width, m_InitData.m_StartCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_StartY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ texture_width, m_InitData.m_StartCutY };
    buffer_builder.AddQuad(quad);

    // Center
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_StartY + m_InitData.m_StartCutX };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ width, repeat_height };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_StartY + m_InitData.m_StartCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ texture_width, repeat_texture_height };
    buffer_builder.AddQuad(quad);

    // Top side
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_EndY - m_InitData.m_EndCutY };
    quad.m_Position.m_End = quad.m_Position.m_Start + Vector2{ width, m_InitData.m_EndCutY };
    quad.m_TexCoords.m_Start = Vector2{ m_InitData.m_StartX, m_InitData.m_EndY - m_InitData.m_EndCutY };
    quad.m_TexCoords.m_End = quad.m_TexCoords.m_Start + Vector2{ texture_width, m_InitData.m_EndCutY };
    buffer_builder.AddQuad(quad);
  }
  else
  {
    quad.m_Position.m_Start = Vector2{ m_Data.m_StartX, m_Data.m_StartY };
    quad.m_Position.m_End = Vector2{ m_Data.m_EndX, m_Data.m_EndY };
    quad.m_TexCoords.m_Start = Vector2{ 0, 0 };
    quad.m_TexCoords.m_End = m_Texture->GetSize();
    buffer_builder.AddRepeatingQuad(quad);
  }

  auto & vertex_buffer = render_util.GetScratchBuffer();
  buffer_builder.FillVertexBuffer(vertex_buffer);

  auto & shader = g_ShaderManager.GetDefaultShader();
  shader.Bind();
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Offset"), (RenderVec2)offset);
  shader.SetUniform(COMPILE_TIME_CRC32_STR("u_Matrix"), RenderVec4{ 1, 0, 0, 1 });

  m_Texture->GetTexture().BindTexture(0);

  vertex_buffer.Bind();
  vertex_buffer.CreateDefaultBinding(shader);
  vertex_buffer.Draw();
}

const UIElementTextureSliceInitData & UIElementTextureSlice::GetInitData()
{
  return m_InitData;
}

UIElementTextureSliceData & UIElementTextureSlice::GetData()
{
  return m_Data;
}

NotNullPtr<UIElementDataBase> UIElementTextureSlice::GetBaseData()
{
  return &m_Data;
}

NullOptPtr<UIElementDataFrameCenter> UIElementTextureSlice::GetFrameCenterData()
{
  return nullptr;
}

NullOptPtr<UIElementDataStartEnd> UIElementTextureSlice::GetStartEndData()
{
  return &m_Data;
}

void UIElementTextureSlice::SetCustomRenderCallback(Delegate<void, UIElementTextureSlice &, RenderState &, const Vector2 &> && render_callback)
{
  m_RenderDelegate = std::move(render_callback);
}

AssetReference<TextureAsset> & UIElementTextureSlice::GetTextureAsset()
{
  return m_Texture;
}

StormExprValueInitBlock & UIElementTextureSlice::GetLocalInitBlock()
{
  return s_LocalInitBlock;
}

StormExprValueInitBlock & UIElementTextureSlice::GetAsParentInitBlock()
{
  return s_AsParentInitBlock;
}

StormExprBindingList & UIElementTextureSlice::GetBindingList()
{
  return s_BindingList;
}


