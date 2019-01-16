
#include "Engine/EngineCommon.h"
#include "Engine/UI/UITextureBinding.h"
#include "Engine/UI/UIManager.h"

UITextureBinding::UITextureBinding() :
  m_UIManager(nullptr),
  m_TextureId(0)
{

}

UITextureBinding::UITextureBinding(NotNullPtr<UIManager> ui_manager, int texture_id, Delegate<NullOptPtr<Texture>> && tex) :
  m_UIManager(ui_manager),
  m_TextureId(texture_id),
  m_TextureFetch(std::move(tex))
{

}

UITextureBinding::UITextureBinding(UITextureBinding && rhs) :
  m_UIManager(rhs.m_UIManager),
  m_TextureId(rhs.m_TextureId),
  m_TextureFetch(std::move(rhs.m_TextureFetch))
{
  rhs.m_UIManager = nullptr;
  rhs.m_TextureId = 0;
  rhs.m_TextureFetch.Clear();

  if(m_UIManager)
  {
    m_UIManager->RelocateTextureBinding(m_TextureId, this);
  }
}

UITextureBinding::~UITextureBinding()
{
  Clear();
}

UITextureBinding & UITextureBinding::operator = (UITextureBinding && rhs)
{
  Clear();

  m_UIManager = rhs.m_UIManager;
  m_TextureId = rhs.m_TextureId;
  m_TextureFetch = std::move(rhs.m_TextureFetch);

  rhs.m_UIManager = nullptr;
  rhs.m_TextureId = 0;
  rhs.m_TextureFetch.Clear();

  if(m_UIManager)
  {
    m_UIManager->RelocateTextureBinding(m_TextureId, this);
  }

  return *this;
}

void UITextureBinding::SetTexture(Delegate<NullOptPtr<Texture>> && tex)
{
  m_TextureFetch = std::move(tex);
}

void UITextureBinding::Clear()
{
  if(m_UIManager)
  {
    m_UIManager->ReleaseTextureBinding(m_TextureId);
    m_UIManager = nullptr;
    m_TextureId = 0;
    m_TextureFetch.Clear();
  }
}
