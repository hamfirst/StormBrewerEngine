#pragma once

class PreMainCallList final
{
public:

  struct CallListElem
  {
    void(*m_Func)();
    CallListElem * m_Next;
  };

  template <class Function>
  void AddCall(Function && f)
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

#ifdef _MSC_VER
#define ADD_PREMAIN_CALL(CallList, Prefix, Call) \
  struct s_Reg_##Prefix##CallList { s_Reg_##Prefix##CallList(){ CallList.AddCall(Call); } } sv_Reg_##Prefix##CallList; \
  void __declspec(dllexport) s_Reg_##Prefix##CallListFunc() { printf("%p", &sv_Reg_##Prefix##CallList); }
#else
#define ADD_PREMAIN_CALL(CallList, Prefix, Call) \
  static struct s_Reg_##Prefix##CallList { s_Reg_##Prefix##CallList(){ CallList.AddCall(Call); } } sv_Reg_##Prefix##CallList __attribute__((used)); \
  void __attribute__((used)) s_Reg_##Prefix##CallListFunc() { printf("%p", &sv_Reg_##Prefix##CallList); }
#endif

#define DECLARE_PREMAIN_CALL(Prefix) void s_Reg_##Prefix##CallListFunc();
#define REFERENCE_PREMAIN_CALL(Prefix) s_Reg_##Prefix##CallListFunc();
