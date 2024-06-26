#pragma once

#include <string>

class StormExprValueProvider;

enum class StormExprValueType
{
  kFloat,
  kString,
  kNothing,
};

class StormExprValue
{
public:
  StormExprValue();

  StormExprValue(float val);
  StormExprValue(const char * str);
  StormExprValue(const char * str1, const char * str2);

  StormExprValue(const StormExprValue & rhs);
  StormExprValue(StormExprValue && rhs);

  ~StormExprValue();

  StormExprValue & operator = (const StormExprValue & rhs);
  StormExprValue & operator = (StormExprValue && rhs);

  bool operator == (const StormExprValue & rhs) const;
  bool operator != (const StormExprValue & rhs) const;

  void Clear();

  void CopyQuick(const StormExprValue & value);
  StormExprValue DuplicateQuick() const;

  StormExprValueType GetType() const;
  float GetFloatVal() const;
  const char * GetStringVal() const;
  std::size_t GetStringLength() const;

  operator float();
  operator const char *();
  operator std::string();

private:


  StormExprValue(StormExprValueType type, float val);

  StormExprValueType m_Type;


  union
  {
    struct
    {
      char * m_String;
      std::size_t m_StrLen;
    };

    float m_Float;
  };
};
