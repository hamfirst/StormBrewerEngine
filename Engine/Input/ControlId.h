#pragma once


enum class ControlType
{
  kInvalid,
  kKeyboard,
  kMouse,
};


struct ControlId
{
  ControlType m_Type;
  int m_Index;
  int m_SubIndex;
};

ControlId CreateKeyboardBinding(int scan_code);
