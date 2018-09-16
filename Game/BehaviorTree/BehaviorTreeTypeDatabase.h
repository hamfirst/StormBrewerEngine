#pragma once

#include "Game/GameCommon.h"

#include "Foundation/CallList/CallList.h"

#include "Runtime/ServerObject/ServerObjectSerialize.h"

struct BehaviorTreeTypeInfo
{
    void (*m_Serialize)(const void * ptr, ServerObjectNetBitWriter & writer);
    void (*m_Deserialize)(void * ptr, ServerObjectNetBitReader & reader);
    bool m_SerializeIfNotActive;
};

class BehaviorTreeTypeDatabase
{
public:
    template <typename Type>
    void RegisterType()
    {
        BehaviorTreeTypeInfo type_info;
        type_info.m_Serialize = [](const void * ptr, ServerObjectNetBitWriter & writer)
        {
            auto type = static_cast<const Type *>(ptr);
            NetSerializeValue(*type, writer);
        };

        type_info.m_Deserialize = [](void * ptr, ServerObjectNetBitReader & reader)
        {
            auto type = static_cast<Type *>(ptr);
            NetDeserializeValue(*type, reader);
        };

        type_info.m_SerializeIfNotActive = false;
        m_TypeInfo.emplace(std::make_pair(typeid(Type).hash_code(), std::move(type_info)));
    }

    bool SerializeType(void * ptr, std::size_t hash_code, bool active, ServerObjectNetBitWriter & writer);
    bool DeserializeType(void * ptr, std::size_t hash_code, bool active, ServerObjectNetBitReader & reader);

private:
    std::unordered_map<std::size_t, BehaviorTreeTypeInfo> m_TypeInfo;
};

#define REGISTER_BEHAVIORTREE_TYPE(BehaviorTreeType) \
  ADD_PREMAIN_CALL(g_BehaviorTreeRegisterCallList, BehaviorTreeType, ([]() { g_BehaviorTreeTypeDatabase.RegisterType<BehaviorTreeType>(); }));   

extern BehaviorTreeTypeDatabase g_BehaviorTreeTypeDatabase;
extern PreMainCallList g_BehaviorTreeRegisterCallList;
