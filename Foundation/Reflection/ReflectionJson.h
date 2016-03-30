
#include "Foundation\Common.h"

#include <json\json.hpp>

struct member_json_decoder_visitor
{
  member_json_decoder_visitor(nlohmann::json & value)
    : m_Value(value)
  {

  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    decode(f.name(), f.type(), f.get());
  }

  template <class T, typename std::enable_if<std::is_class<T>::value && T::is_reflectable>::type * = 0>
  void decode(const char * name, const char * type, T & value)
  {
    try
    {
      member_json_decoder_visitor decoder(m_Value[name]);
      decoder.operator()(value);
    }
    catch (...) {}
  }

  template <class T, typename std::enable_if<std::is_class<T>::value && T::is_enum>::type * = 0>
  void decode(const char * name, const char * type, T & value)
  {
    try
    {

    }
    catch (...) {}
  }

  template <class T, typename std::enable_if<std::is_integral<T>::value>::type * = 0>
  void decode(const char * name, const char * type, T & value)
  {
    try { value = m_Value[name]; }
    catch (...) {}
  }

  template <class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0>
  void decode(const char * name, const char * type, T & value)
  {
    try { value = m_Value[name]; }
    catch (...) {}
  }

  template <class Enable = void>
  void decode(const char * name, const char * type, r_string & value)
  {
    try { value = m_Value[name]; }
    catch (...) {}
  }

  template <class T>
  void decode(const char * name, const char * type, r_list<T> & value)
  {
    nlohmann::json = m_Value[name];
    for (auto v : value)
    {
      decode(name, type, v);
    }
  }

public:
  nlohmann::json & m_Value;
};

template <typename T, typename std::enable_if<
  std::is_arithmetic<T>::value ||
  std::is_same<T, r_string>::value
>::type * = 0>
nlohmann::json encode_json(const T & value)
{
  return value;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_reflectable
>::type * = 0>
nlohmann::json encode_json(const T & value)
{
  nlohmann::json j_value;
  member_json_encoder_visitor encoder(j_value);

  visit_each(value, encoder);
  return j_value;
}

template <typename T, typename std::enable_if<
  std::is_class<T>::value && T::is_enum
>::type * = 0>
nlohmann::json encode_json(const T & value)
{
  return value._to_string();
}


struct member_json_encoder_visitor
{
  member_json_encoder_visitor(nlohmann::json & value)
    : m_Value(value)
  {

  }

  template <class FieldData, class MemType>
  void operator()(FieldData f)
  {
    encode(f.name(), f.type(), f.get());
  }

  template <class T, typename std::enable_if<std::is_class<T>::value && T::is_reflectable>::type * = 0>
  void encode(const char * name, const char * type, T & value)
  {
    try
    {
      member_json_encoder_visitor encoder(m_Value[name]);
      encoder.operator()(value);
    }
    catch (...) {}
  }

  template <class T, typename std::enable_if<std::is_class<T>::value && T::is_enum>::type * = 0>
  void encode(const char * name, const char * type, T & value)
  {
    try
    {

    }
    catch (...) {}
  }

  template <class T, typename std::enable_if<std::is_integral<T>::value>::type * = 0>
  void encode(const char * name, const char * type, T & value)
  {
    try { m_Value[name] = value }
    catch (...) {}
  }

  template <class T, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0>
  void encode(const char * name, const char * type, T & value)
  {
    try { m_Value[name] = value; }
    catch (...) {}
  }

  template <class Enable = void>
  void encode(const char * name, const char * type, r_string & value)
  {
    try { m_Value[name] = value; }
    catch (...) {}
  }

  template <class T>
  void encode(const char * name, const char * type, r_list<T> & value)
  {
    try 
    {
      for (auto v : value)
      {
        nlohmann::json json_value;
        member_json_encoder_visitor encoder(json_value);

        encoder(name, type, v);
      }
    }
    catch (...) {}
  }

public:
  nlohmann::json & m_Value;
};

