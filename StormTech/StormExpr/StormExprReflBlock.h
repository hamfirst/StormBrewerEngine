#pragma once

#include "StormExprValueInitBlock.h"
#include "StormExprBinding.h"

#include "StormRefl/StormReflMetaFuncs.h"


template <typename FieldType>
void StormExprAddToInitBlock(czstr name, void * base_ptr, FieldType & field, StormExprValueInitBlock & init_block)
{

}

template <>
inline void StormExprAddToInitBlock<float>(czstr name, void * base_ptr, float & field, StormExprValueInitBlock & init_block)
{
  init_block.AddValue(name, StormExprValueProvider(base_ptr, &field));
}

template <>
inline void StormExprAddToInitBlock<std::string>(czstr name, void * base_ptr, std::string & field, StormExprValueInitBlock & init_block)
{
  init_block.AddValue(name, StormExprValueProvider(base_ptr, &field));
}

template <typename DataType>
StormExprValueInitBlock StormExprCreateInitBlockForDataType(czstr prefix = "")
{
  StormExprValueInitBlock init_block;

  DataType * base_ptr = nullptr;

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

    StormExprAddToInitBlock(val_name.data(), base_ptr, f.Get(), init_block);
  };

  StormReflVisitEach(*base_ptr, visitor);
  return init_block;
}

template <typename FieldType>
void StormExprAddToBindingList(czstr name, void * base_ptr, FieldType & field, StormExprBindingList & binding_list)
{

}

template <>
inline void StormExprAddToBindingList<float>(czstr name, void * base_ptr, float & field, StormExprBindingList & binding_list)
{
  binding_list.emplace_back(StormExprBindingInfo{ name, StormExprBinding(base_ptr, &field) });
}

template <>
inline void StormExprAddToBindingList<std::string>(czstr name, void * base_ptr, std::string & field, StormExprBindingList & binding_list)
{
  binding_list.emplace_back(StormExprBindingInfo{ name, StormExprBinding(base_ptr, &field) });
}

template <typename DataType>
StormExprBindingList StormExprGetBindingList()
{
  StormExprBindingList binding_list;

  DataType * base_ptr = nullptr;

  auto visitor = [&](auto f)
  {
    StormExprAddToBindingList(f.GetName(), base_ptr, f.Get(), binding_list);
  };

  StormReflVisitEach(*base_ptr, visitor);
  return binding_list;
}
