#pragma once

class PreMainCallList
{
public:

  struct CallListElem
  {
    void(*m_Func)();
    CallListElem * m_Next;
  };

  template <class Function>
  void AddCall(Function & f)
  {
    static Function f_copy = f;
    static CallListElem elem;
    elem.m_Next = m_Head;
    elem.m_Func = []() { f_copy(); };

    m_Head = &elem;
  }

  void CallAll()
  {
    CallListElem * elem = m_Head;
    while (elem)
    {
      elem->m_Func();
      elem = elem->m_Next;
    }
  }

private:
  CallListElem * m_Head;
};

