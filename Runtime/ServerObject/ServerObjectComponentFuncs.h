#pragma once

#include "StormRefl/StormRefl.h"
#include "StormRefl/StormReflMetaFuncs.h"

#include "Foundation/TypeDatabase/TypeDatabase.h"

#include "Runtime/ServerObject/ServerObjectComponent.h"

//ServerObjectComponent<ProjectileMotionBase, ProjectileMotionBaseConfig> m_Motion;
//RPolymorphic<ProjectileMotionBaseConfig, ProjectileMotionBase> m_MotionConfig;

template <typename MemberType, uint32_t member_name_hash, typename Config>
struct ServerObjectInitComponentField
{
  static void Process(MemberType & member, const Config * config)
  {

  }
};


template <typename BaseClass, typename BaseConfig, uint32_t member_name_hash, typename Config>
struct ServerObjectInitComponentField<ServerObjectComponent<BaseClass, BaseConfig>, member_name_hash, Config>
{
  static void Process(ServerObjectComponent<BaseClass, BaseConfig> & member, const Config * config)
  {
    auto visitor = [&](auto f)
    {
      using FieldInfoType = decltype(f);
      using MemberType = typename FieldInfoType::member_type;

      if constexpr (std::template is_same_v<MemberType, RPolymorphic<BaseConfig, BaseClass>> &&
              member_name_hash == FieldInfoType::GetFieldNameHash())
      {
        member.SetFromConfig(f.Get().GetValue());
      }
    };

    StormReflVisitEach(*config, visitor);
  }
};

template <typename ServerObject, typename Config>
void ServerObjectInitComponents(ServerObject * object, const Config * config)
{
  auto visitor = [&](auto f)
  {
    using FieldInfoType = decltype(f);
    using MemberType = typename FieldInfoType::member_type;
    ServerObjectInitComponentField<MemberType, FieldInfoType::GetFieldNameHash(), Config>::Process(f.Get(), config);
  };

  StormReflVisitEach(*object, visitor);
}
