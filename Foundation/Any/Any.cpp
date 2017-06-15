
#include "Foundation/Common.h"
#include "Foundation/Any/Any.h"

Any::Any() :
  m_Ptr(nullptr),
  m_Type(0)
{

}

Any::Any(Any && rhs)
{
  m_Ptr = rhs.m_Ptr;
  m_Type = rhs.m_Type;
  m_Deleter = rhs.m_Deleter;

  rhs.m_Ptr = nullptr;
  rhs.m_Type = 0;
  rhs.m_Deleter = nullptr;
}

Any & Any::operator = (Any && rhs)
{
  Clear();
  m_Ptr = rhs.m_Ptr;
  m_Type = rhs.m_Type;
  m_Deleter = rhs.m_Deleter;

  rhs.m_Ptr = nullptr;
  rhs.m_Type = 0;
  rhs.m_Deleter = nullptr;
  return *this;
}

Any::~Any()
{
  Clear();
}

void Any::Clear()
{
  if (m_Ptr)
  {
    m_Deleter(m_Ptr);
    m_Ptr = nullptr;
    m_Type = 0;
  }
}

AnyPtr::AnyPtr() :
  m_Ptr(nullptr),
  m_Type(0)
{

}

AnyPtr::AnyPtr(const AnyPtr & rhs)
{
  m_Ptr = rhs.m_Ptr;
  m_Type = rhs.m_Type;
}

AnyPtr::AnyPtr(AnyPtr && rhs)
{
  m_Ptr = rhs.m_Ptr;
  m_Type = rhs.m_Type;
}

AnyPtr & AnyPtr::operator = (const AnyPtr & any)
{
  m_Ptr = any.m_Ptr;
  m_Type = any.m_Type;
  return *this;
}

AnyPtr & AnyPtr::operator = (AnyPtr && any)
{
  m_Ptr = any.m_Ptr;
  m_Type = any.m_Type;
  return *this;
}

AnyPtr::~AnyPtr()
{

}

void AnyPtr::Clear()
{
  m_Ptr = nullptr;
  m_Type = 0;
}
