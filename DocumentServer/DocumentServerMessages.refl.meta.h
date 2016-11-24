#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DocumentServerMessages.refl.h"


template <>
struct StormReflEnumInfo<DocumentServerMessageType>
{
  static constexpr int elems_n = 18;
  static constexpr auto GetName() { return "DocumentServerMessageType"; }
  static constexpr auto GetNameHash() { return 0x2984BE49; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kUnknown"; }
  static constexpr auto GetNameHash() { return 0x175422A1; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kUnknown; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kInitComplete"; }
  static constexpr auto GetNameHash() { return 0x17A8C35F; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kInitComplete; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kCreateRequest"; }
  static constexpr auto GetNameHash() { return 0x99CC2F42; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kCreateRequest; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kCreateError"; }
  static constexpr auto GetNameHash() { return 0x8F964E55; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kCreateError; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kOpenRequest"; }
  static constexpr auto GetNameHash() { return 0x2B3F79C7; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kOpenRequest; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kOpenError"; }
  static constexpr auto GetNameHash() { return 0xD6B8A3B7; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kOpenError; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kOpenData"; }
  static constexpr auto GetNameHash() { return 0x7654DF39; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kOpenData; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kOpenFinalizeRequest"; }
  static constexpr auto GetNameHash() { return 0x2540522B; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kOpenFinalizeRequest; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kOpenFinalizeReponse"; }
  static constexpr auto GetNameHash() { return 0x41610373; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kOpenFinalizeReponse; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<9>
{
  static constexpr auto GetName() { return "kSetEditorData"; }
  static constexpr auto GetNameHash() { return 0xA0BE7250; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kSetEditorData; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<10>
{
  static constexpr auto GetName() { return "kChangeRequest"; }
  static constexpr auto GetNameHash() { return 0xAB7C7C64; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kChangeRequest; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<11>
{
  static constexpr auto GetName() { return "kApplyChange"; }
  static constexpr auto GetNameHash() { return 0x3BB4F4B2; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kApplyChange; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<12>
{
  static constexpr auto GetName() { return "kChangeState"; }
  static constexpr auto GetNameHash() { return 0x93AEF40D; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kChangeState; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<13>
{
  static constexpr auto GetName() { return "kUndo"; }
  static constexpr auto GetNameHash() { return 0x4AC67A91; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kUndo; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<14>
{
  static constexpr auto GetName() { return "kRedo"; }
  static constexpr auto GetNameHash() { return 0xDB44ADC9; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kRedo; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<15>
{
  static constexpr auto GetName() { return "kSave"; }
  static constexpr auto GetNameHash() { return 0xFCD0FBBD; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kSave; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<16>
{
  static constexpr auto GetName() { return "kSaveError"; }
  static constexpr auto GetNameHash() { return 0x10AC55F7; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kSaveError; }
};

template <>
struct StormReflEnumInfo<DocumentServerMessageType>::elems<17>
{
  static constexpr auto GetName() { return "kClose"; }
  static constexpr auto GetNameHash() { return 0xC71307E7; }
  static constexpr auto GetValue() { return DocumentServerMessageType::kClose; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageState>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageState"; }
  static constexpr auto GetNameHash() { return 0xEE84E94A; }
  static DocumentServerMessageState & GetDefault() { static DocumentServerMessageState def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageState>::field_data_static<0>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_HasUndo"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAF1B2519; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageState::m_HasUndo; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageState>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageState>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_HasUndo; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_HasUndo; }
  void SetDefault() { self.m_HasUndo = StormReflTypeInfo<DocumentServerMessageState>::GetDefault().m_HasUndo; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageState>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_HasRedo"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3E99F241; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageState::m_HasRedo; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageState>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageState>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_HasRedo; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_HasRedo; }
  void SetDefault() { self.m_HasRedo = StormReflTypeInfo<DocumentServerMessageState>::GetDefault().m_HasRedo; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageState>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_IsModified"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4ED08082; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageState::m_IsModified; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageState>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageState>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_IsModified; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_IsModified; }
  void SetDefault() { self.m_IsModified = StormReflTypeInfo<DocumentServerMessageState>::GetDefault().m_IsModified; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageInitComplete>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageInitComplete"; }
  static constexpr auto GetNameHash() { return 0xC10385BF; }
  static DocumentServerMessageInitComplete & GetDefault() { static DocumentServerMessageInitComplete def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageInitComplete>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AEEA616; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageInitComplete::m_Version; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageInitComplete>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageInitComplete>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Version; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Version; }
  void SetDefault() { self.m_Version = StormReflTypeInfo<DocumentServerMessageInitComplete>::GetDefault().m_Version; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageCreateRequest"; }
  static constexpr auto GetNameHash() { return 0x3910667C; }
  static DocumentServerMessageCreateRequest & GetDefault() { static DocumentServerMessageCreateRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageCreateRequest::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageCreateRequest>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageCreateRequest::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageCreateRequest>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageCreateRequest::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageCreateRequest>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DocumentServerMessageCreateRequest>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateError>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageCreateError"; }
  static constexpr auto GetNameHash() { return 0xF27346F5; }
  static DocumentServerMessageCreateError & GetDefault() { static DocumentServerMessageCreateError def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateError>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageCreateError::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageCreateError>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageCreateError>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageCreateError>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateError>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageCreateError::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageCreateError>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageCreateError>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageCreateError>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageCreateError>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageCreateError::m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageCreateError>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageCreateError>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Error; }
  void SetDefault() { self.m_Error = StormReflTypeInfo<DocumentServerMessageCreateError>::GetDefault().m_Error; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenRequest>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageOpenRequest"; }
  static constexpr auto GetNameHash() { return 0x56DA7167; }
  static DocumentServerMessageOpenRequest & GetDefault() { static DocumentServerMessageOpenRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenRequest>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpenRequest::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpenRequest>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageOpenRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageOpenRequest>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenRequest>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpenRequest::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpenRequest>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageOpenRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageOpenRequest>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenError>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageOpenError"; }
  static constexpr auto GetNameHash() { return 0xF8D3387E; }
  static DocumentServerMessageOpenError & GetDefault() { static DocumentServerMessageOpenError def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenError>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpenError::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpenError>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageOpenError>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageOpenError>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenError>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpenError::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpenError>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageOpenError>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageOpenError>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpenError>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpenError::m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpenError>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageOpenError>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Error; }
  void SetDefault() { self.m_Error = StormReflTypeInfo<DocumentServerMessageOpenError>::GetDefault().m_Error; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>
{
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageOpen"; }
  static constexpr auto GetNameHash() { return 0x012A6AC4; }
  static DocumentServerMessageOpen & GetDefault() { static DocumentServerMessageOpen def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpen::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageOpen>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpen::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageOpen>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpen::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageOpen>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpen::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data<3, Self> : public StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DocumentServerMessageOpen>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_EditorData"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDEC45CEE; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpen::m_EditorData; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data<4, Self> : public StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_EditorData; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_EditorData; }
  void SetDefault() { self.m_EditorData = StormReflTypeInfo<DocumentServerMessageOpen>::GetDefault().m_EditorData; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<5>
{
  using member_type = DocumentServerMessageState; // DocumentServerMessageState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "DocumentServerMessageState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xEE84E94A; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageOpen::m_State; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageOpen>::field_data<5, Self> : public StormReflTypeInfo<DocumentServerMessageOpen>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DocumentServerMessageState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<DocumentServerMessageState>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<DocumentServerMessageOpen>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageFinalizeRequest"; }
  static constexpr auto GetNameHash() { return 0xAF702339; }
  static DocumentServerMessageFinalizeRequest & GetDefault() { static DocumentServerMessageFinalizeRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageFinalizeRequest::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageFinalizeRequest::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageFinalizeRequest::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DocumentServerMessageFinalizeRequest>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageFinalizeResponse"; }
  static constexpr auto GetNameHash() { return 0x015AEA8A; }
  static DocumentServerMessageFinalizeResponse & GetDefault() { static DocumentServerMessageFinalizeResponse def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileType"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB8E8BB5A; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageFinalizeResponse::m_FileType; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileType; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileType; }
  void SetDefault() { self.m_FileType = StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::GetDefault().m_FileType; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_FileName"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6A159275; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageFinalizeResponse::m_FileName; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_FileName; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_FileName; }
  void SetDefault() { self.m_FileName = StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::GetDefault().m_FileName; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageFinalizeResponse::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DocumentServerMessageFinalizeResponse>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSetEditorData>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageSetEditorData"; }
  static constexpr auto GetNameHash() { return 0x00623B6E; }
  static DocumentServerMessageSetEditorData & GetDefault() { static DocumentServerMessageSetEditorData def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSetEditorData>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageSetEditorData::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageSetEditorData>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageSetEditorData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageSetEditorData>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSetEditorData>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_EditorData"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDEC45CEE; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageSetEditorData::m_EditorData; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageSetEditorData>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageSetEditorData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_EditorData; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_EditorData; }
  void SetDefault() { self.m_EditorData = StormReflTypeInfo<DocumentServerMessageSetEditorData>::GetDefault().m_EditorData; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageChangeRequest>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageChangeRequest"; }
  static constexpr auto GetNameHash() { return 0x0BA0355A; }
  static DocumentServerMessageChangeRequest & GetDefault() { static DocumentServerMessageChangeRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageChangeRequest>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageChangeRequest::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageChangeRequest>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageChangeRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageChangeRequest>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageChangeRequest>::field_data_static<1>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_Changes"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB5D2CDE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageChangeRequest::m_Changes; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageChangeRequest>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageChangeRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_Changes; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_Changes; }
  void SetDefault() { self.m_Changes = StormReflTypeInfo<DocumentServerMessageChangeRequest>::GetDefault().m_Changes; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageApplyChange"; }
  static constexpr auto GetNameHash() { return 0x4651FC12; }
  static DocumentServerMessageApplyChange & GetDefault() { static DocumentServerMessageApplyChange def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageApplyChange::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageApplyChange>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data_static<1>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_Changes"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB5D2CDE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageApplyChange::m_Changes; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_Changes; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_Changes; }
  void SetDefault() { self.m_Changes = StormReflTypeInfo<DocumentServerMessageApplyChange>::GetDefault().m_Changes; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data_static<2>
{
  using member_type = DocumentServerMessageState; // DocumentServerMessageState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "DocumentServerMessageState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xEE84E94A; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageApplyChange::m_State; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data<2, Self> : public StormReflTypeInfo<DocumentServerMessageApplyChange>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DocumentServerMessageState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<DocumentServerMessageState>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<DocumentServerMessageApplyChange>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageChangeState>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageChangeState"; }
  static constexpr auto GetNameHash() { return 0xEE4BFCAD; }
  static DocumentServerMessageChangeState & GetDefault() { static DocumentServerMessageChangeState def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageChangeState>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageChangeState::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageChangeState>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageChangeState>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageChangeState>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageChangeState>::field_data_static<1>
{
  using member_type = DocumentServerMessageState; // DocumentServerMessageState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "DocumentServerMessageState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xEE84E94A; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageChangeState::m_State; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageChangeState>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageChangeState>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DocumentServerMessageState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<DocumentServerMessageState>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<DocumentServerMessageChangeState>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageUndo>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageUndo"; }
  static constexpr auto GetNameHash() { return 0x462A5292; }
  static DocumentServerMessageUndo & GetDefault() { static DocumentServerMessageUndo def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageUndo>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageUndo::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageUndo>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageUndo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageUndo>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageRedo>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageRedo"; }
  static constexpr auto GetNameHash() { return 0xD7A885CA; }
  static DocumentServerMessageRedo & GetDefault() { static DocumentServerMessageRedo def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageRedo>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageRedo::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageRedo>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageRedo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageRedo>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSave>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageSave"; }
  static constexpr auto GetNameHash() { return 0xF03CD3BE; }
  static DocumentServerMessageSave & GetDefault() { static DocumentServerMessageSave def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSave>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageSave::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageSave>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageSave>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageSave>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSaveError>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageSaveError"; }
  static constexpr auto GetNameHash() { return 0x3EC7CE3E; }
  static DocumentServerMessageSaveError & GetDefault() { static DocumentServerMessageSaveError def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSaveError>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageSaveError::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageSaveError>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageSaveError>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageSaveError>::GetDefault().m_DocumentId; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageSaveError>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Error"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0EB2C11; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageSaveError::m_Error; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageSaveError>::field_data<1, Self> : public StormReflTypeInfo<DocumentServerMessageSaveError>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Error; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Error; }
  void SetDefault() { self.m_Error = StormReflTypeInfo<DocumentServerMessageSaveError>::GetDefault().m_Error; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageClose>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DocumentServerMessageClose"; }
  static constexpr auto GetNameHash() { return 0x5E16BA75; }
  static DocumentServerMessageClose & GetDefault() { static DocumentServerMessageClose def; return def; }
};

template <>
struct StormReflTypeInfo<DocumentServerMessageClose>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DocumentId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD40CC618; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DocumentServerMessageClose::m_DocumentId; }
};

template <typename Self>
struct StormReflTypeInfo<DocumentServerMessageClose>::field_data<0, Self> : public StormReflTypeInfo<DocumentServerMessageClose>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DocumentId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DocumentId; }
  void SetDefault() { self.m_DocumentId = StormReflTypeInfo<DocumentServerMessageClose>::GetDefault().m_DocumentId; }
};

namespace StormReflFileInfo
{
  struct DocumentServerMessages
  {
    static const int types_n = 18;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DocumentServerMessages::type_info<0>
  {
    using type = ::DocumentServerMessageState;
  };

  template <>
  struct DocumentServerMessages::type_info<1>
  {
    using type = ::DocumentServerMessageInitComplete;
  };

  template <>
  struct DocumentServerMessages::type_info<2>
  {
    using type = ::DocumentServerMessageCreateRequest;
  };

  template <>
  struct DocumentServerMessages::type_info<3>
  {
    using type = ::DocumentServerMessageCreateError;
  };

  template <>
  struct DocumentServerMessages::type_info<4>
  {
    using type = ::DocumentServerMessageOpenRequest;
  };

  template <>
  struct DocumentServerMessages::type_info<5>
  {
    using type = ::DocumentServerMessageOpenError;
  };

  template <>
  struct DocumentServerMessages::type_info<6>
  {
    using type = ::DocumentServerMessageOpen;
  };

  template <>
  struct DocumentServerMessages::type_info<7>
  {
    using type = ::DocumentServerMessageFinalizeRequest;
  };

  template <>
  struct DocumentServerMessages::type_info<8>
  {
    using type = ::DocumentServerMessageFinalizeResponse;
  };

  template <>
  struct DocumentServerMessages::type_info<9>
  {
    using type = ::DocumentServerMessageSetEditorData;
  };

  template <>
  struct DocumentServerMessages::type_info<10>
  {
    using type = ::DocumentServerMessageChangeRequest;
  };

  template <>
  struct DocumentServerMessages::type_info<11>
  {
    using type = ::DocumentServerMessageApplyChange;
  };

  template <>
  struct DocumentServerMessages::type_info<12>
  {
    using type = ::DocumentServerMessageChangeState;
  };

  template <>
  struct DocumentServerMessages::type_info<13>
  {
    using type = ::DocumentServerMessageUndo;
  };

  template <>
  struct DocumentServerMessages::type_info<14>
  {
    using type = ::DocumentServerMessageRedo;
  };

  template <>
  struct DocumentServerMessages::type_info<15>
  {
    using type = ::DocumentServerMessageSave;
  };

  template <>
  struct DocumentServerMessages::type_info<16>
  {
    using type = ::DocumentServerMessageSaveError;
  };

  template <>
  struct DocumentServerMessages::type_info<17>
  {
    using type = ::DocumentServerMessageClose;
  };

}

