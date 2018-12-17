
#include "Engine/EngineCommon.h"
#include "Engine/UI/UITextInput.refl.h"
#include "Engine/UI/UIClickable.refl.h"


UITextInput::UITextInput(std::shared_ptr<TextInputContext> && context) :
  m_TextInput(std::move(context))
{

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
