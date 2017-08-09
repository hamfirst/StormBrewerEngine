#pragma once

#include "StormExpr/StormExprValueInitBlock.h"
#include "StormRefl/StormReflMetaFuncs.h"

#include "Engine/UI/UIElementExprBinding.h"

#include "Runtime/UI/UIDef.refl.h"


struct UIElementExprDynamicBlockVariable
{
  uint16_t m_Index;
  UIVariableType m_Type;
};

class UIElementExprDynamicBlock
{
public:

  UIElementExprDynamicBlockVariable AddVariable(const UIDefInputVariable & var, StormExprValueInitBlock & init_block);

  void SetVariable(const UIElementExprDynamicBlockVariable & var, float val);
  void SetVariable(const UIElementExprDynamicBlockVariable & var, const std::string & val);
  void SetVariable(const UIElementExprDynamicBlockVariable & var, czstr val);

  UIElementExprBinding GetBinding(UIElementExprDynamicBlockVariable var);

private:

  std::vector<float> m_Floats;
  std::vector<std::string> m_Strings;
};

template <typename FieldType>
void UIAddToInitBlock(czstr name, FieldType & field, StormExprValueInitBlock & init_block)
{

}

template <>
inline void UIAddToInitBlock<float>(czstr name, float & field, StormExprValueInitBlock & init_block)
{
  init_block.AddValue(name, StormExprValueProvider(&field));
}

template <>
inline void UIAddToInitBlock<std::string>(czstr name, std::string & field, StormExprValueInitBlock & init_block)
{
  init_block.AddValue(name, StormExprValueProvider(&field));
}

template <typename DataType>
StormExprValueInitBlock UICreateInitBlockForDataType(DataType & data, czstr prefix = "")
{
  StormExprValueInitBlock init_block;

  auto visitor = [&](auto f)
  {
    using MemberType = typename decltype(f)::member_type;

    auto name = f.GetName();
    std::string val_name = prefix;

    if (name[0] == 'm' && name[1] == '_')
    {
      val_name += name + 2;
    }
    else
    {
      val_name += name;
    }

    UIAddToInitBlock(val_name.data(), f.Get(), init_block);
  };

  StormReflVisitEach(data, visitor);
  return init_block;
}

template <typename DataType>
void UIAddInitBlockForDataType(DataType & data, StormExprValueInitBlock & init_block, czstr prefix = "")
{
  auto visitor = [&](auto f)
  {
    using MemberType = typename decltype(f)::member_type;

    auto name = f.GetName();
    std::string val_name = prefix;

    if (name[0] == 'm' && name[1] == '_')
    {
      val_name += name + 2;
    }
    else
    {
      val_name += name;
    }

    UIAddToInitBlock(val_name.data(), f.Get(), init_block);
  };

  StormReflVisitEach(data, visitor);
}

template <typename FieldType>
void UIAddToBindingList(czstr name, FieldType & field, UIElementExprBindingList & binding_list)
{

}

template <>
inline void UIAddToBindingList<float>(czstr name, float & field, UIElementExprBindingList & binding_list)
{
  binding_list.emplace_back(UIElementExprBindingInfo{ name, UIElementExprBinding(&field) });
}

template <>
inline void UIAddToBindingList<std::string>(czstr name, std::string & field, UIElementExprBindingList & binding_list)
{
  binding_list.emplace_back(UIElementExprBindingInfo{ name, UIElementExprBinding(&field) });
}

template <typename DataType>
UIElementExprBindingList UICreateBindingList(DataType & data)
{
  UIElementExprBindingList binding_list;
  auto visitor = [&](auto f)
  {
    UIAddToBindingList(f.GetName(), f.Get(), binding_list);
  };

  StormReflVisitEach(data, visitor);
  return binding_list;
}