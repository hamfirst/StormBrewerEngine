#pragma once


#include "StormNet/NetReflectionTypeDatabase.h"
#include "StormData/StormDataPath.h"

#include "Foundation/Castable/Castable.h"
#include "Foundation/TypeDatabase/TypeDatabase.h"

class ServerObjectNetBitWriter;
class ServerObjectNetBitReader;

template <typename BaseClass, typename BaseConfig>
class ServerObjectComponent;


struct ServerObjectComponentLogicInfo
{
  uint32_t m_NameHash;
  std::size_t m_TypeId;
  std::size_t m_TypeIndex;
  NotNullPtr<const NetTypeInfo> m_TypeInfo;
};

template <typename DataType, typename LogicType>
struct TypeDatabaseInitLogicInfo<DataType, LogicType, ServerObjectComponentLogicInfo>
{
  static void Process(ServerObjectComponentLogicInfo & logic_type_info)
  {
    logic_type_info.m_NameHash = StormReflTypeInfo<LogicType>::GetNameHash();
    logic_type_info.m_TypeId = typeid(LogicType).hash_code();
    logic_type_info.m_TypeIndex = LogicType::__s_TypeDatabase.template GetClassId<LogicType>();
    logic_type_info.m_TypeInfo = &LogicType::__s_TypeDatabase.template GetTypeInfo<LogicType>();
  }
};

template <typename BaseConfig>
class ServerObjectComponentBase
{
public:
  NullOptPtr<const BaseConfig> GetConfig() const
  {
    return m_Config.Value();
  }

  template <typename T>
  NullOptPtr<const T> GetConfigAs() const
  {
    return m_Config.template CastTo<T>();
  }

  using TypeInfo = ServerObjectComponentLogicInfo;

private:

  template <typename BaseClass, typename BaseConfigT>
  friend class ServerObjectComponent;

  ConstCastable<BaseConfig> m_Config;
};

template <typename BaseClass, typename BaseConfig>
class ServerObjectComponent
{
public:

  static_assert(std::is_base_of_v<ServerObjectComponentBase<BaseConfig>, BaseClass>,
          "Component type must inherit from ServerObjectComponentBase");

  ServerObjectComponent() :
    m_Object(nullptr),
    m_TypeInfo(nullptr)
  {

  }

  ServerObjectComponent(const ServerObjectComponent<BaseClass, BaseConfig> & rhs)
  {
    if(rhs.m_Object == nullptr)
    {
      m_Object = nullptr;
      m_TypeInfo = nullptr;
    }
    else
    {
      m_Object = static_cast<BaseClass *>(rhs.m_TypeInfo->m_HeapCreate());
      m_TypeInfo = rhs.m_TypeInfo;
      m_Config = rhs.m_Config;
      m_Object->m_Config = m_Config;

      m_TypeInfo->m_Copy(m_Object, rhs.m_Object);
    }
  }

  ServerObjectComponent(ServerObjectComponent<BaseClass, BaseConfig> && rhs)
  {
    m_Object = rhs.m_Object;
    m_TypeInfo = rhs.m_TypeInfo;
    m_Config = rhs.m_Config;

    rhs.m_Object = nullptr;
    rhs.m_TypeInfo = nullptr;
    rhs.m_Config = {};
  }

  ~ServerObjectComponent()
  {
    if(m_Object)
    {
      m_TypeInfo->m_HeapDestroy(m_Object);
    }
  }

  ServerObjectComponent<BaseClass, BaseConfig> & operator = (const ServerObjectComponent<BaseClass, BaseConfig> & rhs)
  {
    if(m_TypeInfo == rhs.m_TypeInfo)
    {
      m_Object->m_Config = rhs.m_Object->m_Config;
      m_TypeInfo->m_Copy(m_Object, rhs.m_Object);
      return *this;
    }

    if(m_Object)
    {
      m_TypeInfo->m_HeapDestroy(m_Object);
    }

    if(rhs.m_Object == nullptr)
    {
      m_Object = nullptr;
      m_TypeInfo = nullptr;
    }
    else
    {
      m_Object = static_cast<BaseClass *>(rhs.m_TypeInfo->m_HeapCreate());
      m_TypeInfo = rhs.m_TypeInfo;
      m_Config = rhs.m_Config;
      m_Object->m_Config = rhs.m_Config;

      m_TypeInfo->m_Copy(m_Object, rhs.m_Object);
    }

    return *this;
  }

  ServerObjectComponent<BaseClass, BaseConfig> & operator = (ServerObjectComponent<BaseClass, BaseConfig> && rhs)
  {
    if(m_Object)
    {
      m_TypeInfo->m_HeapDestroy(m_Object);
    }

    m_Object = rhs.m_Object;
    m_TypeInfo = rhs.m_TypeInfo;
    m_Config = rhs.m_Config;

    rhs.m_Object = nullptr;
    rhs.m_TypeInfo = nullptr;
    rhs.m_Config = {};
  }

  void SetFromConfig(NotNullPtr<const BaseConfig> config)
  {
    if(m_Object != nullptr && config == m_Config.Value())
    {
      return;
    }

    for(auto & elem : m_ConfigInfo)
    {
      if(elem.m_Config.Value() == config)
      {
        if(m_Config.Value() == elem.m_Config.Value())
        {
          return;
        }

        m_Object = static_cast<BaseClass *>(elem.m_TypeInfo->m_HeapCreate());
        m_TypeInfo = elem.m_TypeInfo;
        m_Config = elem.m_Config;
        m_Object->m_Config = elem.m_Config;

        return;
      }
    }

    ASSERT(false, "Could not locate config for server object component");

    if(m_Object)
    {
      m_TypeInfo->m_HeapDestroy(m_Object);
      m_Object = nullptr;
      m_TypeInfo = nullptr;
      m_Config = {};
    }
  }

  template <typename ConfigClass>
  static void RegisterConfigType(czstr asset_path, NotNullPtr<const ConfigClass> config,
          const ServerObjectComponentLogicInfo & logic_info)
  {
    auto asset_path_hash = crc32lowercase(asset_path);
    auto data_path_hash = crc32(StormDataGetPath(*config));

    for(auto & elem : m_ConfigInfo)
    {
      if(elem.m_AssetPath == asset_path_hash && elem.m_DataPath == data_path_hash)
      {
        elem.m_Config = ConstCastable<ConfigClass>(*config);
        return;
      }
    }

    ConfigInfo info;
    info.m_AssetPath = asset_path_hash;
    info.m_DataPath = data_path_hash;
    info.m_Config = ConstCastable<ConfigClass>(*config);
    info.m_TypeIndex = logic_info.m_TypeIndex;
    info.m_TypeInfo = logic_info.m_TypeInfo;
    m_ConfigInfo.emplace_back(std::move(info));
  }

  NullOptPtr<const BaseConfig> GetConfig() const
  {
    return m_Config.Value();
  }

  template <typename T>
  NullOptPtr<const T> GetConfigAs() const
  {
    return m_Config.template CastTo<T>();
  }

  void Clear()
  {
    if(m_Object)
    {
      m_TypeInfo->m_HeapDestroy(m_Object);
      m_Object = nullptr;
      m_TypeInfo = nullptr;
      m_Config.Clear();
    }
  }

  void Serialize(ServerObjectNetBitWriter & writer) const
  {
    if(m_Object == nullptr)
    {
      return;
    }

    m_TypeInfo->m_Serialize(m_Object, writer);
  }

  void Deserialize(ServerObjectNetBitReader & reader)
  {
    if(m_Object == nullptr)
    {
      return;
    }

    m_TypeInfo->m_Deserialize(m_Object, reader);
  }

  NullOptPtr<BaseClass> operator -> ()
  {
    return m_Object;
  }

  NullOptPtr<const BaseClass> operator -> () const
  {
    return m_Object;
  }

  BaseClass & operator * ()
  {
    return *m_Object;
  }

  const BaseClass & operator * () const
  {
    return *m_Object;
  }

private:
  NullOptPtr<BaseClass> m_Object;
  NullOptPtr<const NetTypeInfo> m_TypeInfo;
  ConstCastable<BaseConfig> m_Config;

  struct ConfigInfo
  {
    uint32_t m_AssetPath;
    uint32_t m_DataPath;
    ConstCastable<BaseConfig> m_Config;
    std::size_t m_TypeIndex;
    NotNullPtr<const NetTypeInfo> m_TypeInfo;
  };

  static inline std::vector<ConfigInfo> m_ConfigInfo;

};

template <typename BaseConfig>
struct StormReflTypeInfo<ServerObjectComponentBase<BaseConfig>>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "ServerObject"; }
  static constexpr auto GetNameHash() { return COMPILE_TIME_CRC32_STR("ServerObject"); }
  static ServerObject & GetDefault() { static ServerObjectComponentBase<BaseConfig> def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<ServerObjectComponentBase<BaseConfig> *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const ServerObjectComponentBase<BaseConfig> *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<ServerObjectComponentBase<BaseConfig> *>(ptr);
    if(typeid(ServerObjectComponentBase<BaseConfig>).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const ServerObjectComponentBase<BaseConfig> *>(ptr);
    if(typeid(ServerObjectComponentBase<BaseConfig>).hash_code() == type_id_hash) return c;
    return nullptr;
  }
};

template <typename BaseConfig>
struct StormReflFuncInfo<ServerObjectComponentBase<BaseConfig>>
{
  using MyBase = StormRelfEmptyBase;
  static constexpr int funcs_n = 0 + StormReflFuncInfo<MyBase>::funcs_n;
  template <int N> struct func_data_static : public StormReflFuncInfo<MyBase>::func_data_static<N> {};
};
