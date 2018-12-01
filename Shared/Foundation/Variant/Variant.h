#pragma once

#include <type_traits>

#include "Foundation/Assert/Assert.h"

template <typename TestType, typename ... PossibleTypes>
struct VariantTypeIndex
{
  template <int I>
  static constexpr int GetTypeIndex()
  {
    return -1;
  }
};

template <typename TestType, typename Type, typename ... PossibleTypes>
struct VariantTypeIndex<TestType, Type, PossibleTypes...>
{
  template <int I>
  static constexpr int GetTypeIndex()
  {
    return VariantTypeIndex<TestType, PossibleTypes...>::template GetTypeIndex<I + 1>();
  }
};

template <typename TestType, typename ... PossibleTypes>
struct VariantTypeIndex<TestType, TestType, PossibleTypes...>
{
  template <int I>
  static constexpr int GetTypeIndex()
  {
    return I;
  }
};

typedef void(*VariantCopier)(const void * src, void * dst);
typedef void(*VariantMover)(void * src, void * dst);
typedef void(*VariantDestructor)(void * ptr);

template <typename ... PossibleTypes>
struct VariantInitialize
{
  static void InitCopiers(VariantCopier * copier_list)
  {

  }

  static void InitMovers(VariantMover * mover_list)
  {

  }

  static void InitDestructors(VariantDestructor * destructor_list)
  {

  }
};

template <typename Type, typename ... PossibleTypes>
struct VariantInitialize<Type, PossibleTypes...>
{
  static void InitCopiers(VariantCopier * copier_list)
  {
    *copier_list = [](const void * src, void * dst)
    {
      const Type * src_t = static_cast<const Type *>(src);
      new(dst) Type(*src_t);
    };

    VariantInitialize<PossibleTypes...>::InitCopiers(copier_list + 1);
  }

  static void InitMovers(VariantMover * mover_list)
  {
    *mover_list = [](void * src, void * dst)
    {
      Type * src_t = static_cast<Type *>(src);
      new(dst) Type(std::move(*src_t));
    };

    VariantInitialize<PossibleTypes...>::InitMovers(mover_list + 1);
  }

  static void InitDestructors(VariantDestructor * destructor_list)
  {
    *destructor_list = [](void * ptr)
    {
      Type * ptr_t = static_cast<Type *>(ptr);
      ptr_t->~Type();
    };

    VariantInitialize<PossibleTypes...>::InitDestructors(destructor_list + 1);
  }
};

template <typename ... PossibleTypes>
class Variant
{
public:
  static const int kNumTypes = sizeof...(PossibleTypes);

  Variant() = default;

  Variant(const Variant & rhs) :
    m_TypeIndex(rhs.m_TypeIndex)
  {
    VariantCopier copier = GetCopier();
    copier(&rhs.m_Buffer, &m_Buffer);
  }

  Variant(Variant && rhs) :
    m_TypeIndex(rhs.m_TypeIndex)
  {
    VariantMover mover = GetMover();
    mover(&rhs.m_Buffer, &m_Buffer);
  }

  ~Variant()
  {
    Clear();
  }

  template <typename Type, std::enable_if_t<!std::is_same<std::remove_reference_t<Type>, Variant<PossibleTypes...>>::value> * Enable = nullptr>
  Variant(const Type & type)
  {
    Set<Type, const Type &>(type);
  }

  template <typename Type, std::enable_if_t<!std::is_same<std::remove_reference_t<Type>, Variant<PossibleTypes...>>::value> * Enable = nullptr>
  Variant(Type & type)
  {
    Set<Type, Type &>(type);
  }

  template <typename Type, std::enable_if_t<!std::is_same<std::remove_reference_t<Type>, Variant<PossibleTypes...>>::value> * Enable = nullptr>
  Variant(Type && type)
  {
    Set<Type, Type &&>(std::move(type));
  }

  Variant<PossibleTypes...> & operator = (const Variant<PossibleTypes...> & rhs)
  {
    Clear();
    m_TypeIndex = rhs.m_TypeIndex;

    if (m_TypeIndex != -1)
    {
      VariantCopier copier = GetCopier();
      copier(&rhs.m_Buffer, &m_Buffer);
    }

    return *this;
  }

  Variant<PossibleTypes...> & operator = (Variant<PossibleTypes...> && rhs)
  {
    Clear();
    m_TypeIndex = rhs.m_TypeIndex;

    if (m_TypeIndex != -1)
    {
      VariantMover mover = GetMover();
      mover(&rhs.m_Buffer, &m_Buffer);
    }
    return *this;
  }

  template <typename Type, std::enable_if_t<!std::is_same<std::remove_reference_t<Type>, Variant<PossibleTypes...>>::value> * Enable = nullptr>
  Variant<PossibleTypes...> & operator = (const Type & type)
  {
    Set<std::remove_reference_t<Type>, const Type &>(type);
    return *this;
  }

  template <typename Type, std::enable_if_t<!std::is_same<std::remove_reference_t<Type>, Variant<PossibleTypes...>>::value> * Enable = nullptr>
  Variant<PossibleTypes...> & operator = (Type & type)
  {
    Set<std::remove_reference_t<Type>, Type &>(type);
    return *this;
  }

  template <typename Type, std::enable_if_t<!std::is_same<std::remove_reference_t<Type>, Variant<PossibleTypes...>>::value> * Enable = nullptr>
  Variant<PossibleTypes...> & operator = (Type && type)
  {
    Set<std::remove_reference_t<Type>, Type &&>(std::move(type));
    return *this;
  }

  template <typename Type>
  Type & GetAs()
  {
    int type_index = GetIndexForType<Type>();

    if (type_index == -1 || type_index != m_TypeIndex)
    {
      ASSERT(false, "Attempting to derefrence a variant of the invalid type");
    }

    return *reinterpret_cast<Type *>(&m_Buffer);
  }

  template <typename Type>
  const Type & GetAs() const
  {
    int type_index = GetIndexForType<Type>();

    if (type_index == -1 || type_index != m_TypeIndex)
    {
      ASSERT(false, "Attempting to derefrence a variant of the invalid type");
    }

    return *reinterpret_cast<const Type *>(&m_Buffer);
  }

  template <typename Type>
  NullOptPtr<Type> TryGet()
  {
    int type_index = GetIndexForType<Type>();

    if (type_index == -1 || type_index != m_TypeIndex)
    {
      return nullptr;
    }

    return reinterpret_cast<Type *>(&m_Buffer);
  }

  template <typename Type>
  NullOptPtr<const Type> TryGet() const
  {
    int type_index = GetIndexForType<Type>();

    if (type_index == -1 || type_index != m_TypeIndex)
    {
      return nullptr;
    }

    return *reinterpret_cast<const Type *>(&m_Buffer);
  }

  template <typename Type>
  NullOptPtr<Type> Get()
  {
    int type_index = GetIndexForType<Type>();

    if (type_index == -1 || type_index != m_TypeIndex)
    {
      return nullptr;
    }

    return reinterpret_cast<Type *>(&m_Buffer);
  }

  template <typename Type>
  NullOptPtr<const Type> Get() const
  {
    int type_index = GetIndexForType<Type>();

    if (type_index == -1 || type_index != m_TypeIndex)
    {
      return nullptr;
    }

    return reinterpret_cast<const Type *>(&m_Buffer);
  }

  void Clear()
  {
    if (m_TypeIndex == -1)
    {
      return;
    }

    VariantDestructor destructor = GetDestructor();
    destructor(&m_Buffer);
    m_TypeIndex = -1;
  }

  operator bool()
  {
    return m_TypeIndex != -1;
  }

  template <typename Type>
  constexpr int GetIndexForType() const
  {
    return VariantTypeIndex<std::remove_reference_t<Type>, PossibleTypes...>::template GetTypeIndex<0>();
  }

  int GetCurrentTypeIndex() const
  {
    return m_TypeIndex;
  }

  int GetNumTypes() const
  {
    return sizeof...(PossibleTypes);
  }

private:

  VariantCopier GetCopier()
  {
    static VariantCopier copiers[sizeof...(PossibleTypes)] = {};
    static bool initialized = false;

    if (initialized == false)
    {
      VariantInitialize<PossibleTypes...>::InitCopiers(copiers);
    }

    return copiers[m_TypeIndex];
  }

  VariantMover GetMover()
  {
    static VariantMover movers[sizeof...(PossibleTypes)] = {};
    static bool initialized = false;

    if (initialized == false)
    {
      VariantInitialize<PossibleTypes...>::InitMovers(movers);
    }

    return movers[m_TypeIndex];
  }

  VariantDestructor GetDestructor()
  {
    static VariantDestructor destructor[sizeof...(PossibleTypes)] = {};
    static bool initialized = false;

    if (initialized == false)
    {
      VariantInitialize<PossibleTypes...>::InitDestructors(destructor);
    }

    return destructor[m_TypeIndex];
  }

  template <typename Type, typename ... InitArgs>
  void Set(InitArgs && ... args)
  {
    Clear();
    int type = GetIndexForType<Type>();

    if (type == -1)
    {
      ASSERT(false, "Can't set to invalid type");
    }

    new(&m_Buffer) Type(std::forward<InitArgs>(args)...);
    m_TypeIndex = type;
  }

  int m_TypeIndex = -1;
  std::aligned_union_t<sizeof...(PossibleTypes), PossibleTypes...> m_Buffer;
};
