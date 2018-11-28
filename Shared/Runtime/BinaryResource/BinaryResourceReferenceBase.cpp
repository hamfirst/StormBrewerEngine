
#include "Runtime/RuntimeCommon.h"
#include "Runtime/BinaryResource/BinaryResourceBase.h"
#include "Runtime/BinaryResource/BinaryResourceReferenceBase.h"

BinaryResourceReferenceBase::BinaryResourceReferenceBase() :
  m_Resource(nullptr)
{

}

BinaryResourceReferenceBase::BinaryResourceReferenceBase(BinaryResourceBase * resource) :
  m_Resource(resource)
{
  m_Resource->IncRef();
}

BinaryResourceReferenceBase::BinaryResourceReferenceBase(const BinaryResourceReferenceBase & rhs) noexcept
{
  m_Resource = nullptr;
  if (rhs.m_Resource)
  {
    m_Resource = rhs.m_Resource;
    m_Resource->IncRef();
  }
}

BinaryResourceReferenceBase::BinaryResourceReferenceBase(BinaryResourceReferenceBase && rhs) noexcept
{
  m_Resource = rhs.m_Resource;
  rhs.m_Resource = nullptr;
}

BinaryResourceReferenceBase::~BinaryResourceReferenceBase()
{
  Clear();
}

BinaryResourceReferenceBase & BinaryResourceReferenceBase::operator = (const BinaryResourceReferenceBase & rhs) noexcept
{
  if (m_Resource == rhs.m_Resource)
  {
    return *this;
  }

  Clear();

  if (rhs.m_Resource)
  {
    m_Resource = rhs.m_Resource;
    m_Resource->IncRef();
  }

  return *this;
}

BinaryResourceReferenceBase & BinaryResourceReferenceBase::operator = (BinaryResourceReferenceBase && rhs) noexcept
{
  Clear();

  m_Resource = rhs.m_Resource;
  rhs.m_Resource = nullptr;

  return *this;
}

void BinaryResourceReferenceBase::Clear()
{
  if (m_Resource)
  {
    m_Resource->DecRef();
    m_Resource = nullptr;
  }
}
