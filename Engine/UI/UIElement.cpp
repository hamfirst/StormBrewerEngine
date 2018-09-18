
#include "Engine/EngineCommon.h"
#include "Engine/UI/UIElement.h"
#include "Engine/UI/UIManager.h"
#include "Engine/UI/UIElementExprFuncs.h"
#include "Engine/UI/UIElementExprTypes.refl.meta.h"

#include "Foundation/SparseList/SparseList.h"

#include "StormExpr/StormExprEvalBuilder.h"

static auto s_GlobalInitBlock = StormExprCreateInitBlockForDataType<UIGlobalBlock>();
static auto s_AutoInitBlock = StormExprCreateInitBlockForDataType<UIAutoCalculatedBlock>();
static auto s_AsParentAutoInitBlock = StormExprCreateInitBlockForDataType<UIAutoCalculatedBlock>("p.");

UIElement::UIElement() :
  m_TimeCreated((float)GetTimeSeconds())
{

}

UIElement::~UIElement()
{

}

void UIElement::Update(float dt)
{
  m_AutoBlock.m_TimeAlive += dt;

  for (auto & elem : m_BindingList)
  {
    UIResetLerpVals(m_AutoBlock.m_TimeAlive);
    elem.m_Binding.Update(elem.m_FunctionIndex, m_Eval.Value(), elem.m_BasePtr);
  }

  for (auto & elem : m_ChildBindingList)
  {
    if (elem.m_Handle.Resolve())
    {
      UIResetLerpVals(m_AutoBlock.m_TimeAlive);
      elem.m_Binding.Update(elem.m_FunctionIndex, m_Eval.Value(), elem.m_BasePtr);
    }
  }

  m_OnUpdate(this);

  for (auto elem : m_Children)
  {
    elem->Update(dt);
  }

  auto data = GetBaseData();
  if (data->m_Enabled != 0.0f && data->m_Active != 0.0f && m_State == UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kActive);
    m_State = UIElementState::kActive;
  }
  else if ((data->m_Enabled == 0.0f || data->m_Active == 0.0f) && m_State != UIElementState::kInactive)
  {
    m_OnStateChange(m_State, UIElementState::kInactive);
    m_State = UIElementState::kInactive;
  }
}

void UIElement::Render(RenderState & render_state, RenderUtil & render_util, const Vector2 & offset)
{
  auto child_offset = offset + m_Offset;
  for (auto child : m_Children)
  {
    child->Render(render_state, render_util, child_offset);
  }
}

void UIElement::SetActive(bool active)
{
  if (active)
  {
    GetBaseData()->m_Active = 1.0f;
  }
  else
  {
    SetInactive();
  }
}

void UIElement::SetInactive()
{
  GetBaseData()->m_Active = 0.0f;
}

void UIElement::SetEnabled(bool enabled)
{
  if (enabled)
  {
    GetBaseData()->m_Enabled = 1.0f;
  }
  else
  {
    SetDisabled();
  }
}


void UIElement::SetDisabled()
{
  GetBaseData()->m_Enabled = 0.0f;
}

void UIElement::Destroy()
{
  m_Handle.m_UIManager->UnlinkElement(this);
}

UIElementHandle UIElement::GetHandle()
{
  return m_Handle;
}

NotNullPtr<UIManager> UIElement::GetManager()
{
  return m_Handle.m_UIManager;
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

std::vector<std::pair<std::string, StormExprDynamicBlockVariable>> UIElement::InitializeExprBlock(const UIDef & def,
  NullOptPtr<StormExprValueInitBlock> parent_init_block, void * parent_data,
  NullOptPtr<StormExprValueInitBlock> parent_auto_init_block, void * parent_auto_data,
  UIManager & manager, std::vector<std::string> & errors, bool use_default_inputs)
{
  std::vector<std::pair<std::string, StormExprDynamicBlockVariable>> input_values;

  auto base_data_ptr = GetBaseData();

  auto & local_init_block = GetLocalInitBlock();
  auto & as_parent_init_block = GetAsParentInitBlock();

  auto & auto_init_block = s_AutoInitBlock;
  auto & global_init_block = s_GlobalInitBlock;

  StormExprValueInitBlock input_float_block, input_string_block;
  std::vector<StormExprDynamicBlockVariable> input_vars;

  for (auto input : def.m_Inputs)
  {
    StormExprValueType type;
    switch ((UIVariableType)input.second.m_Type)
    {
    default:
    case UIVariableType::kFloat:
      type = StormExprValueType::kFloat;
      break;
    case UIVariableType::kString:
      type = StormExprValueType::kString;
      break;
    }

    auto var = m_InputBlock.AddVariable(type);
    input_vars.push_back(var);
  }

  int input_var_index = 0;
  for(auto input : def.m_Inputs)
  {
    auto & var = input_vars[input_var_index];
    m_InputBlock.Link(var, input.second.m_VariableName.data(), input_float_block, input_string_block);

    input_values.emplace_back(std::make_pair(input.second.m_VariableName, var));
    m_InputLookup.emplace_back(std::make_pair(crc32(input.second.m_VariableName), var));
    input_var_index++;
  }

  m_FloatInputValueBlock.Emplace(input_float_block);
  m_StringInputValueBlock.Emplace(input_string_block);

  std::vector<StormExprValueInitBlock *> value_init_blocks = { &input_float_block, &input_string_block, &local_init_block, &auto_init_block, &global_init_block };
  std::vector<void *> block_base_ptrs = { m_InputBlock.GetBaseFloatPtr(), m_InputBlock.GetBaseStringPtr(), base_data_ptr, &m_AutoBlock, &manager.m_GlobalBlock };

  if (parent_init_block)
  {
    value_init_blocks.push_back(parent_init_block);
    block_base_ptrs.push_back(parent_data);
  }

  if (parent_auto_init_block)
  {
    value_init_blocks.push_back(parent_auto_init_block);
    block_base_ptrs.push_back(parent_auto_data);
  }


  StormExprValueInitBlockList block_list(std::move(value_init_blocks));
  StormExprEvalBuilder eval_builder(manager.m_FuncList);
  eval_builder.SetBlockList(block_list);

  if (use_default_inputs)
  {
    input_var_index = 0;
    for (auto input : def.m_Inputs)
    {
      if (input.second.m_DefaultEquation.size() != 0)
      {
        auto & var = input_vars[input_var_index];

        czstr error, error_desc;
        auto function_index = eval_builder.ParseExpression(input.second.m_DefaultEquation.data(), error, error_desc);
        if (function_index == -1)
        {
          std::string error_msg = m_Name + "." + input.second.m_VariableName.ToString() + ": " + error_desc + " at " + error;
          errors.emplace_back(std::move(error_msg));

          input_var_index++;
          continue;
        }

        m_BindingList.emplace_back(BindingEvalInfo{ m_InputBlock.GetBinding(var), m_InputBlock.GetBasePtr(var), function_index });
      }

      input_var_index++;
    }
  }

  auto binding_list = GetBindingList();

  for (auto binding : binding_list)
  {
    auto var_name_hash = crc32(binding.m_Name);
    for (auto elem : def.m_Equations)
    {
      auto equation_name_hash = crc32(elem.second.m_VariableName.data());
      if (equation_name_hash == var_name_hash && elem.second.m_Equation.size() > 0)
      {
        czstr error, error_desc;
        auto function_index = eval_builder.ParseExpression(elem.second.m_Equation.data(), error, error_desc);
        if (function_index == -1)
        {
          std::string error_msg = m_Name + "." + binding.m_Name + ": " + error_desc + " at " + error;
          errors.emplace_back(std::move(error_msg));
          break;
        }

        m_BindingList.emplace_back(BindingEvalInfo{ binding.m_Value, base_data_ptr, function_index });
        break;
      }
    }
  }

  SparseList<std::pair<UIElementHandle, std::vector<std::pair<std::string, StormExprDynamicBlockVariable>>>> handle_list;
  for (auto child : def.m_Children)
  {
    auto handle = 
      manager.AllocateElementFromInitData(child.second.m_Name.data(), this, child.second.m_UI.m_InitData.GetTypeNameHash(), child.second.m_UI.m_InitData.GetValue());

    auto ui_element = handle.Resolve();
    if (ui_element == nullptr)
    {
      handle_list.EmplaceAt(child.first, std::make_pair(handle, std::vector<std::pair<std::string, StormExprDynamicBlockVariable>>{}));
      continue;
    }

    auto child_blindings = ui_element->InitializeExprBlock(child.second.m_UI,
      &as_parent_init_block, base_data_ptr, 
      &s_AsParentAutoInitBlock, &m_AutoBlock, 
      manager, errors, false);

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

        if (child_val.first == output.second.m_VariableName.ToString() && output.second.m_Equation.size() > 0)
        {
          created_binding = true;

          czstr error, error_desc;
          auto function_index = eval_builder.ParseExpression(output.second.m_Equation.data(), error, error_desc);
          if (function_index == -1)
          {
            std::string error_msg = m_Name + "." + child->GetName() + "." + child_val.first + ": " + error_desc + " at " + error;
            errors.emplace_back(std::move(error_msg));
            break;
          }

          auto binding = child->m_InputBlock.GetBinding(child_val.second);
          auto base_ptr = child->m_InputBlock.GetBasePtr(child_val.second);
          m_ChildBindingList.emplace_back(ChildBindingEvalInfo{ binding, base_ptr, child->GetHandle(), function_index });
          break;
        }
      }

      if (created_binding == false)
      {
        for (auto input : child_def.second.m_UI.m_Inputs)
        {
          if (input.second.m_VariableName == child_val.first)
          {
            if (input.second.m_DefaultEquation.size() > 0)
            {
              czstr error, error_desc;
              auto function_index = eval_builder.ParseExpression(input.second.m_DefaultEquation.data(), error, error_desc);
              if (function_index == -1)
              {
                std::string error_msg = m_Name + "." + child->GetName() + "." + child_val.first + ": " + error_desc + " at " + error;
                errors.emplace_back(std::move(error_msg));
                break;
              }

              auto binding = child->m_InputBlock.GetBinding(child_val.second);
              auto base_ptr = child->m_InputBlock.GetBasePtr(child_val.second);
              m_ChildBindingList.emplace_back(ChildBindingEvalInfo{ binding, base_ptr, child->GetHandle(), function_index });
            }
            break;
          }
        }
      }
    }
  }

  m_Eval.Emplace(std::move(eval_builder));
  for (std::size_t index = 0; index < block_base_ptrs.size(); ++index)
  {
    m_Eval->SetBlockBasePtr(index, block_base_ptrs[index]);
  }

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
