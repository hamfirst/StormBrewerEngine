
#include "Engine/EngineCommon.h"
#include "Engine/UI/UITextInput.refl.h"
#include "Engine/UI/UIClickable.refl.h"


UITextInput::UITextInput(std::shared_ptr<TextInputContext> && context) :
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
}

void UITextInput::MakeCurrent(ScriptClassRef<UIClickable> container)
{
  auto box = container->CalculateActiveArea();
  if(box)
  {
    m_TextInput->MakeCurrent(&box.Value());
  }
}

std::string UITextInput::GetText()
{
  return m_TextInput->GetCurrentInput();
}
