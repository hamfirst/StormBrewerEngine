
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UITextInput.refl.h"
#include "Engine/UI/UIClickable.refl.h"


UITextInput::UITextInput(NotNullPtr<UIManager> manager, std::shared_ptr<TextInputContext> && context) :
  m_Manager(manager),
  m_TextInput(std::move(context))
{
  m_TextInput->SetValidator([this](const char * text){
    if(IsInvalidInput.IsValid())
    {
      bool invalid = IsInvalidInput(text);
      return !invalid;
    }
    else
    {
      return true;
    }
  });

  m_TextInput->SetEnterDelegate([this](const char * text){
    if(OnEnter.IsValid())
    {
      OnEnter();
    }
  });
}

UITextInput::~UITextInput()
{
  m_TextInput->SetValidator({});
  m_TextInput->SetEnterDelegate({});

  if(m_Manager->m_CurrentInputContext == this)
  {
    m_Manager->m_CurrentInputClickable = nullptr;
    m_Manager->m_CurrentInputContext = nullptr;
  }
}

void UITextInput::MakeCurrent(ScriptClassRef<UIClickable> container)
{
  auto box = container->CalculateActiveArea();
  if(box)
  {
    m_TextInput->MakeCurrent(&box.Value());

    m_Manager->m_CurrentInputContext = this;
    m_Manager->m_CurrentInputClickable = container;
  }
}

void UITextInput::MakeNotCurrent()
{
  m_TextInput->Unbind();

  if(m_Manager->m_CurrentInputContext == this)
  {
    m_Manager->m_CurrentInputClickable = nullptr;
    m_Manager->m_CurrentInputContext = nullptr;
  }
}

bool UITextInput::IsCurrent()
{
  return m_TextInput->IsTextInputActive();
}

std::string UITextInput::GetText()
{
  return m_TextInput->GetCurrentInput();
}

void UITextInput::Clear()
{
  m_TextInput->ClearInput();
}

int UITextInput::GetCursorPos()
{
  return (int)m_TextInput->GetCursorPos();
}
