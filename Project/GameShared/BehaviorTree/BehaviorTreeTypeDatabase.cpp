
#include "GameShared/BehaviorTree/BehaviorTreeTypeDatabase.h"

BehaviorTreeTypeDatabase g_BehaviorTreeTypeDatabase;
PreMainCallList g_BehaviorTreeRegisterCallList;

bool BehaviorTreeTypeDatabase::SerializeType(void * ptr, std::size_t hash_code, bool active, ServerObjectNetBitWriter & writer)
{
    auto itr = m_TypeInfo.find(hash_code);
    if(itr == m_TypeInfo.end())
    {
        return false;
    }

    auto & type_info = itr->second;
    if(active || type_info.m_SerializeIfNotActive)
    {
        type_info.m_Serialize(ptr, writer);
    }

    return true;
}

bool BehaviorTreeTypeDatabase::DeserializeType(void * ptr, std::size_t hash_code, bool active, ServerObjectNetBitReader & reader)
{
    auto itr = m_TypeInfo.find(hash_code);
    if(itr == m_TypeInfo.end())
    {
        return false;
    }

    auto & type_info = itr->second;
    if(active || type_info.m_SerializeIfNotActive)
    {
        type_info.m_Deserialize(ptr, reader);
    }

    return true;
}


