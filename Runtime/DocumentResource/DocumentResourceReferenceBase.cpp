
#include "Runtime/RuntimeCommon.h"
#include "Runtime/DocumentResource/DocumentResourceBase.h"
#include "Runtime/DocumentResource/DocumentResourceReferenceBase.h"

DocumentResourceReferenceBase::DocumentResourceReferenceBase() :
  m_Resource(nullptr)
{

}

DocumentResourceReferenceBase::DocumentResourceReferenceBase(DocumentResourceBase * resource) :
  m_Resource(resource)
{
  m_Resource->IncRef();
}

DocumentResourceReferenceBase::DocumentResourceReferenceBase(const DocumentResourceReferenceBase & rhs) noexcept
{
  m_Resource = nullptr;
  if (rhs.m_Resource)
  {
    m_Resource = rhs.m_Resource;
    m_Resource->IncRef();
  }
}

DocumentResourceReferenceBase::DocumentResourceReferenceBase(DocumentResourceReferenceBase && rhs) noexcept
{
  m_Resource = rhs.m_Resource;
  rhs.m_Resource = nullptr;
}

DocumentResourceReferenceBase::~DocumentResourceReferenceBase()
{
  Clear();
}

DocumentResourceReferenceBase & DocumentResourceReferenceBase::operator = (const DocumentResourceReferenceBase & rhs) noexcept
{
  Clear();

  if (rhs.m_Resource)
  {
    m_Resource = rhs.m_Resource;
    m_Resource->IncRef();
  }

  return *this;
}

DocumentResourceReferenceBase & DocumentResourceReferenceBase::operator = (DocumentResourceReferenceBase && rhs) noexcept
{
  Clear();

  m_Resource = rhs.m_Resource;
  rhs.m_Resource = nullptr;

  return *this;
}

void DocumentResourceReferenceBase::Clear()
{
  if (m_Resource)
  {
    m_Resource->DecRef();
    m_Resource = nullptr;
  }
}
