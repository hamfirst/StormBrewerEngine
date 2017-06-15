#pragma once

struct SkipFieldIterator
{
  alignas(alignof(void *)) char m_Buffer[sizeof(void *) * 3];
};

