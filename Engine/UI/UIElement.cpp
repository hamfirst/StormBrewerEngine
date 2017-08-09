
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIElementExprBlock.h"
#include "Engine/UI/UIElementExprFuncs.h"
#include "Engine/UI/UIElementExprTypes.refl.meta.h"

#include "Foundation/SparseList/SparseList.h"

#include "StormExpr/StormExprEvalBuilder.h"


UIElement::UIElement() :
  m_TimeCreated((float)GetTimeSeconds())
{

}

UIElement::~UIElement()
{

}

void UIElement::Update()
{
  m_AutoBlock.m_TimeAlive = (float)GetTimeSeconds() - m_TimeCreated;

  for (auto & elem : m_BindingList)
  {
    elem.m_Binding.Update(elem.m_FunctionIndex, m_Eval.Value());
  }

  for (auto & elem : m_ChildBindingList)
  {
    if (elem.m_Handle.Resolve())
    {
      elem.m_Binding.Update(elem.m_FunctionIndex, m_Eval.Value());
    }
  }

  m_OnUpdate(this);

  for (auto elem : m_Children)
  {
    elem->Update();
  }
}

void UIElement::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  auto child_offset = offset + m_Offset;
  for (auto child : m_Children)
  {
    if (child->m_Enabled)
    {
      child->Render(render_state, render_util, child_offset);
    }
  }
}

void UIElement::SetActive()
{
  if (m_State == UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kActive);
    m_State = UIElementState::kActive;
  }
}

void UIElement::SetInactive()
{
  if (m_State != UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kInactive);
    m_State = UIElementState::kInactive;
  }
}

void UIElement::SetEnabled()
{
  m_Enabled = true;
  if (m_State == UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kActive);
    m_State = UIElementState::kActive;
  }
}

void UIElement::SetEnabled(bool enabled)
{
  if (enabled)
  {
    SetEnabled();
  }
  else
  {
    SetDisabled();
  }
}

void UIElement::SetDisabled()
{
  m_Enabled = false;
  if (m_State == UIElementState::kPressed || m_State == UIElementState::kHover)
  {
    m_OnStateChange(m_State, UIElementState::kActive);
    m_State = UIElementState::kActive;
  }
}

void UIElement::Destroy()
{
  m_Handle.m_UIManager->UnlinkElement(this);
}

UIElementHandle UIElement::GetHandle()
{
  return m_Handle;
}

UIElementState UIElement::GetState()
{
  return m_State;
}

Optional<Box> UIElement::GetActiveArea()
{
  if (m_State == UIElementState::kInactive)
  {
    return{};
  }

  return m_ActiveArea;
}

NullOptPtr<UIElement> UIElement::GetChild(uint32_t child_name_hash)
{
  for (auto child : m_Children)
  {
    if (child->m_NameHash == child_name_hash)
    {
      return child;
    }
  }

  return nullptr;
}

NullOptPtr<UIElement> UIElement::GetParent()
{
  return m_Parent;
}

void UIElement::SetOnUpdateHandler(UIOnUpdateHandler && handler)
{
  m_OnUpdate = std::move(handler);
}

void UIElement::SetOnClickHandler(UIOnClickHandler && handler)
{
  m_OnClick = std::move(handler);
}

void UIElement::SetOnStateChangeHandler(UIOnStateChangeHandler && handler)
{
  m_OnStateChange = std::move(handler);
}

void UIElement::SetInput(uint32_t variable_name, float val)
{
  for (auto & input : m_InputLookup)
  {
    if (input.first == variable_name)
    {
      m_InputBlock.SetVariable(input.second, val);
      return;
    }
  }
}

void UIElement::SetInput(uint32_t variable_name, const std::string & val)
{
  for (auto & input : m_InputLookup)
  {
    if (input.first == variable_name)
    {
      m_InputBlock.SetVariable(input.second, val);
      return;
    }
  }
}

void UIElement::SetInput(uint32_t variable_name, czstr val)
{
  for (auto & input : m_InputLookup)
  {
    if (input.first == variable_name)
    {
      m_InputBlock.SetVariable(input.second, val);
      return;
    }
  }
}

UIElementExprBindingList UIElement::InitializeExprBlock(
  const UIDef & def, NullOptPtr<StormExprValueInitBlock> parent_block, UIManager & manager, std::vector<std::string> & errors)
{
  UIElementExprBindingList input_values;

  auto local_block = GetLocalBlock();
  auto as_parent_block = GetAsParentBlock();
  UIAddInitBlockForDataType(m_AutoBlock, as_parent_block, "p.");

  auto auto_block = GetAutoBlock();
  auto global_block = UICreateInitBlockForDataType(manager.m_GlobalBlock);
  
  StormExprValueInitBlock input_block;
  for (auto input : def.m_Inputs)
  {
    auto var = m_InputBlock.AddVariable(input.second, input_block);
    input_values.emplace_back(UIElementExprBindingInfo{ input.second.m_VariableName, m_InputBlock.GetBinding(var) });
    m_InputLookup.emplace_back(std::make_pair(crc32(input.second.m_VariableName), var));
  }

  std::vector<StormExprValueInitBlock *> value_blocks = { &input_block, &local_block, &auto_block, &global_block };
  if (parent_block)
  {
    value_blocks.push_back(parent_block);
  }

  for (auto block : value_blocks)
  {
    m_BlockList.emplace_back(*block);
  }

  StormExprValueInitBlockList block_list(std::move(value_blocks));
  StormExprEvalBuilder eval_builder(manager.m_FuncList);
  eval_builder.SetBlockList(block_list);

  auto binding_list = CreateBindingList();

  for (auto binding : binding_list)
  {
    auto var_name_hash = crc32(binding.m_Name);
    for (auto elem : def.m_Equations)
    {
      auto equation_name_hash = crc32(elem.second.m_VariableName.data());
      if (equation_name_hash == var_name_hash)
      {
        czstr error, error_desc;
        auto function_index = eval_builder.ParseExpression(elem.second.m_Equation.data(), error, error_desc);
        if (function_index == -1)
        {
          std::string error_msg = m_Name + "." + binding.m_Name + ": " + error_desc + " at " + error;
          errors.emplace_back(std::move(error_msg));
          break;
        }

        m_BindingList.emplace_back(BindingEvalInfo{ binding.m_Value, function_index });
        break;
      }
    }
  }

  SparseList<std::pair<UIElementHandle, UIElementExprBindingList>> handle_list;
  for (auto child : def.m_Children)
  {
    auto handle = 
      manager.AllocateElementFromInitData(child.second.m_Name.data(), this, child.second.m_UI.m_InitData.GetTypeNameHash(), child.second.m_UI.m_InitData.GetValue());

    auto ui_element = handle.Resolve();
    if (ui_element == nullptr)
    {
      handle_list.EmplaceAt(child.first, std::make_pair(handle, UIElementExprBindingList{}));
      continue;
    }

    auto child_blindings = ui_element->InitializeExprBlock(child.second.m_UI, &as_parent_block, manager, errors);
    handle_list.EmplaceAt(child.first, std::make_pair(handle, std::move(child_blindings)));
  }

  for (auto child_def : def.m_Children)
  {
    auto child_index = child_def.first;
    auto child_info = handle_list.TryGet((std::size_t)child_index);

    if (child_info == nullptr)
    {
      continue;
    }

    auto child = child_info->first.Resolve();
    if (child == nullptr)
    {
      continue;
    }

    for (auto & child_val : child_info->second)
    {
      bool created_binding = false;
      for (auto output : def.m_Outputs)
      {
        if (child_index != output.second.m_ChildIndex)
        {
          continue;
        }

        if (child_val.m_Name == output.second.m_VariableName.ToString())
        {
          created_binding = true;

          czstr error, error_desc;
          auto function_index = eval_builder.ParseExpression(output.second.m_Equation.data(), error, error_desc);
          if (function_index == -1)
          {
            std::string error_msg = m_Name + "." + child->GetName() + "." + child_val.m_Name + ": " + error_desc + " at " + error;
            errors.emplace_back(std::move(error_msg));
            break;
          }

          m_ChildBindingList.emplace_back(ChildBindingEvalInfo{ child_val.m_Value, child->GetHandle(), function_index });
          break;
        }
      }

      if (created_binding == false)
      {
        for (auto input : child_def.second.m_UI.m_Inputs)
        {
          if (input.second.m_VariableName == child_val.m_Name)
          {
            if (input.second.m_DefaultEquation.size() > 0)
            {
              czstr error, error_desc;
              auto function_index = eval_builder.ParseExpression(input.second.m_DefaultEquation.data(), error, error_desc);
              if (function_index == -1)
              {
                std::string error_msg = m_Name + "." + child->GetName() + "." + child_val.m_Name + ": " + error_desc + " at " + error;
                errors.emplace_back(std::move(error_msg));
                break;
              }

              m_ChildBindingList.emplace_back(ChildBindingEvalInfo{ child_val.m_Value, child->GetHandle(), function_index });
            }
            break;
          }
        }
      }
    }
  }

  m_Eval.Emplace(std::move(eval_builder));

  std::vector<StormExprValueBlock *> eval_block_list;
  for (auto & elem : m_BlockList)
  {
    eval_block_list.push_back(&elem);
  }

  m_Eval->SetBlockList(std::move(eval_block_list));
  return input_values;
}

const std::string & UIElement::GetName() const
{
  return m_Name;
}

void UIElement::SetActiveArea(const Box & box)
{
  m_ActiveArea = box;
  m_AutoBlock.m_ScreenX = (float)box.m_Start.x;
  m_AutoBlock.m_ScreenY = (float)box.m_Start.y;

  auto size = box.Size();
  m_AutoBlock.m_Width = (float)size.x;
  m_AutoBlock.m_Height = (float)size.y;
}

void UIElement::SetOffset(const Vector2 & offset)
{
  m_Offset = offset;
}

StormExprValueInitBlock UIElement::GetAutoBlock()
{
  return UICreateInitBlockForDataType(m_AutoBlock);
}

void UIElement::SetHandle(Handle & handle)
{
  Handle & my_handle = m_Handle;
  my_handle = handle;
}

void UIElement::SetIterator(const SkipFieldIterator & itr)
{
  m_Iterator = itr;
}

const SkipFieldIterator & UIElement::GetIterator() const
{
  return m_Iterator;
}
