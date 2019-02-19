#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "BotMessages.refl.h"
#include "GameData.refl.meta.h"
#include "GameServerMessages.refl.meta.h"


template <>
struct StormReflTypeInfo<BotMessageBase>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageBase"; }
  static constexpr auto GetNameHash() { return 0x96600309; }
  static BotMessageBase & GetDefault() { static BotMessageBase def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageBase>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageBase::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageBase>::field_data<0, Self> : public StormReflTypeInfo<BotMessageBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageBase>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotErrorMessage>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotErrorMessage"; }
  static constexpr auto GetNameHash() { return 0x605B94B4; }
  static BotErrorMessage & GetDefault() { static BotErrorMessage def; return def; }
};

template <>
struct StormReflTypeInfo<BotErrorMessage>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotErrorMessage::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotErrorMessage>::field_data<0, Self> : public StormReflTypeInfo<BotErrorMessage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotErrorMessage>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotErrorMessage>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "err"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x125FDBBD; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotErrorMessage::err; }
};

template <typename Self>
struct StormReflTypeInfo<BotErrorMessage>::field_data<1, Self> : public StormReflTypeInfo<BotErrorMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.err; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.err; }
  void SetDefault() { self.err = StormReflTypeInfo<BotErrorMessage>::GetDefault().err; }
};

template <>
struct StormReflTypeInfo<BotIdentify>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotIdentify"; }
  static constexpr auto GetNameHash() { return 0xE635F8CE; }
  static BotIdentify & GetDefault() { static BotIdentify def; return def; }
};

template <>
struct StormReflTypeInfo<BotIdentify>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotIdentify::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotIdentify>::field_data<0, Self> : public StormReflTypeInfo<BotIdentify>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotIdentify>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotIdentify>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotIdentify::user_name; }
};

template <typename Self>
struct StormReflTypeInfo<BotIdentify>::field_data<1, Self> : public StormReflTypeInfo<BotIdentify>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.user_name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.user_name; }
  void SetDefault() { self.user_name = StormReflTypeInfo<BotIdentify>::GetDefault().user_name; }
};

template <>
struct StormReflTypeInfo<BotIdentify>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "password"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C246D5; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotIdentify::password; }
};

template <typename Self>
struct StormReflTypeInfo<BotIdentify>::field_data<2, Self> : public StormReflTypeInfo<BotIdentify>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.password; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.password; }
  void SetDefault() { self.password = StormReflTypeInfo<BotIdentify>::GetDefault().password; }
};

template <>
struct StormReflTypeInfo<BotIdentify>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "relocation_key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x59F18131; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BotIdentify::relocation_key; }
};

template <typename Self>
struct StormReflTypeInfo<BotIdentify>::field_data<3, Self> : public StormReflTypeInfo<BotIdentify>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.relocation_key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.relocation_key; }
  void SetDefault() { self.relocation_key = StormReflTypeInfo<BotIdentify>::GetDefault().relocation_key; }
};

template <>
struct StormReflTypeInfo<BotMessageUpdate>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageUpdate"; }
  static constexpr auto GetNameHash() { return 0xF60D0CA2; }
  static BotMessageUpdate & GetDefault() { static BotMessageUpdate def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageUpdate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageUpdate::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageUpdate>::field_data<0, Self> : public StormReflTypeInfo<BotMessageUpdate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageUpdate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageUpdate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF3F363; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageUpdate::data; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageUpdate>::field_data<1, Self> : public StormReflTypeInfo<BotMessageUpdate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.data; }
  void SetDefault() { self.data = StormReflTypeInfo<BotMessageUpdate>::GetDefault().data; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelChat>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageChannelChat"; }
  static constexpr auto GetNameHash() { return 0x56271208; }
  static BotMessageChannelChat & GetDefault() { static BotMessageChannelChat def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelChat::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data<0, Self> : public StormReflTypeInfo<BotMessageChannelChat>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageChannelChat>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "user_name"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x24A232CF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelChat::user_name; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data<1, Self> : public StormReflTypeInfo<BotMessageChannelChat>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.user_name; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.user_name; }
  void SetDefault() { self.user_name = StormReflTypeInfo<BotMessageChannelChat>::GetDefault().user_name; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelChat::msg; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data<2, Self> : public StormReflTypeInfo<BotMessageChannelChat>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<BotMessageChannelChat>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelChat::user_id; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data<3, Self> : public StormReflTypeInfo<BotMessageChannelChat>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.user_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.user_id; }
  void SetDefault() { self.user_id = StormReflTypeInfo<BotMessageChannelChat>::GetDefault().user_id; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data_static<4>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "endpoint_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x21AF7E36; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelChat::endpoint_id; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelChat>::field_data<4, Self> : public StormReflTypeInfo<BotMessageChannelChat>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.endpoint_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.endpoint_id; }
  void SetDefault() { self.endpoint_id = StormReflTypeInfo<BotMessageChannelChat>::GetDefault().endpoint_id; }
};

template <>
struct StormReflTypeInfo<BotMessageRelocate>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageRelocate"; }
  static constexpr auto GetNameHash() { return 0x04521E11; }
  static BotMessageRelocate & GetDefault() { static BotMessageRelocate def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageRelocate>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageRelocate::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageRelocate>::field_data<0, Self> : public StormReflTypeInfo<BotMessageRelocate>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageRelocate>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageRelocate>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "new_host"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3BCAA720; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageRelocate::new_host; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageRelocate>::field_data<1, Self> : public StormReflTypeInfo<BotMessageRelocate>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.new_host; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.new_host; }
  void SetDefault() { self.new_host = StormReflTypeInfo<BotMessageRelocate>::GetDefault().new_host; }
};

template <>
struct StormReflTypeInfo<BotMessageRelocate>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "new_port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB77CE911; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotMessageRelocate::new_port; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageRelocate>::field_data<2, Self> : public StormReflTypeInfo<BotMessageRelocate>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.new_port; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.new_port; }
  void SetDefault() { self.new_port = StormReflTypeInfo<BotMessageRelocate>::GetDefault().new_port; }
};

template <>
struct StormReflTypeInfo<BotMessageRelocate>::field_data_static<3>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "relocation_token"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D14BB9E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BotMessageRelocate::relocation_token; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageRelocate>::field_data<3, Self> : public StormReflTypeInfo<BotMessageRelocate>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.relocation_token; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.relocation_token; }
  void SetDefault() { self.relocation_token = StormReflTypeInfo<BotMessageRelocate>::GetDefault().relocation_token; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToChannel>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageSendChatToChannel"; }
  static constexpr auto GetNameHash() { return 0x9407A3C1; }
  static BotMessageSendChatToChannel & GetDefault() { static BotMessageSendChatToChannel def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToChannel>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageSendChatToChannel::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageSendChatToChannel>::field_data<0, Self> : public StormReflTypeInfo<BotMessageSendChatToChannel>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageSendChatToChannel>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToChannel>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageSendChatToChannel::msg; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageSendChatToChannel>::field_data<1, Self> : public StormReflTypeInfo<BotMessageSendChatToChannel>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<BotMessageSendChatToChannel>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelMotd>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageChannelMotd"; }
  static constexpr auto GetNameHash() { return 0x99B585CE; }
  static BotMessageChannelMotd & GetDefault() { static BotMessageChannelMotd def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelMotd>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelMotd::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelMotd>::field_data<0, Self> : public StormReflTypeInfo<BotMessageChannelMotd>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageChannelMotd>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageChannelMotd>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "motd"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAA0F656C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageChannelMotd::motd; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageChannelMotd>::field_data<1, Self> : public StormReflTypeInfo<BotMessageChannelMotd>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.motd; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.motd; }
  void SetDefault() { self.motd = StormReflTypeInfo<BotMessageChannelMotd>::GetDefault().motd; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToUser>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageSendChatToUser"; }
  static constexpr auto GetNameHash() { return 0x0414DF8E; }
  static BotMessageSendChatToUser & GetDefault() { static BotMessageSendChatToUser def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToUser>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageSendChatToUser::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageSendChatToUser>::field_data<0, Self> : public StormReflTypeInfo<BotMessageSendChatToUser>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageSendChatToUser>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToUser>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "msg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x688A5FAF; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageSendChatToUser::msg; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageSendChatToUser>::field_data<1, Self> : public StormReflTypeInfo<BotMessageSendChatToUser>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.msg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.msg; }
  void SetDefault() { self.msg = StormReflTypeInfo<BotMessageSendChatToUser>::GetDefault().msg; }
};

template <>
struct StormReflTypeInfo<BotMessageSendChatToUser>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "user_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA76ED395; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotMessageSendChatToUser::user_id; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageSendChatToUser>::field_data<2, Self> : public StormReflTypeInfo<BotMessageSendChatToUser>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.user_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.user_id; }
  void SetDefault() { self.user_id = StormReflTypeInfo<BotMessageSendChatToUser>::GetDefault().user_id; }
};

template <>
struct StormReflTypeInfo<BotMessageGameResult>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageGameResult"; }
  static constexpr auto GetNameHash() { return 0x39C93421; }
  static BotMessageGameResult & GetDefault() { static BotMessageGameResult def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageGameResult>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageGameResult::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageGameResult>::field_data<0, Self> : public StormReflTypeInfo<BotMessageGameResult>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageGameResult>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageGameResult>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageGameResult::game_id; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageGameResult>::field_data<1, Self> : public StormReflTypeInfo<BotMessageGameResult>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.game_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.game_id; }
  void SetDefault() { self.game_id = StormReflTypeInfo<BotMessageGameResult>::GetDefault().game_id; }
};

template <>
struct StormReflTypeInfo<BotMessageGameResult>::field_data_static<2>
{
  using member_type = GameServerGameResult; // GameServerGameResult
  static constexpr auto GetName() { return "game_info"; }
  static constexpr auto GetType() { return "GameServerGameResult"; }
  static constexpr unsigned GetFieldNameHash() { return 0x209C5D7B; }
  static constexpr unsigned GetTypeNameHash() { return 0x63B1A2A0; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotMessageGameResult::game_info; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageGameResult>::field_data<2, Self> : public StormReflTypeInfo<BotMessageGameResult>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameServerGameResult> & Get() { return self.game_info; }
  std::add_const_t<std::remove_reference_t<GameServerGameResult>> & Get() const { return self.game_info; }
  void SetDefault() { self.game_info = StormReflTypeInfo<BotMessageGameResult>::GetDefault().game_info; }
};

template <>
struct StormReflTypeInfo<BotMessageCreateGame>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "BotMessageCreateGame"; }
  static constexpr auto GetNameHash() { return 0x44FD468B; }
  static BotMessageCreateGame & GetDefault() { static BotMessageCreateGame def; return def; }
};

template <>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "c"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x06B9DF6F; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &BotMessageCreateGame::c; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data<0, Self> : public StormReflTypeInfo<BotMessageCreateGame>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.c; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.c; }
  void SetDefault() { self.c = StormReflTypeInfo<BotMessageCreateGame>::GetDefault().c; }
};

template <>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "server_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1844E6B7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &BotMessageCreateGame::server_id; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data<1, Self> : public StormReflTypeInfo<BotMessageCreateGame>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.server_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.server_id; }
  void SetDefault() { self.server_id = StormReflTypeInfo<BotMessageCreateGame>::GetDefault().server_id; }
};

template <>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "game_id"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48FD905; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &BotMessageCreateGame::game_id; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data<2, Self> : public StormReflTypeInfo<BotMessageCreateGame>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.game_id; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.game_id; }
  void SetDefault() { self.game_id = StormReflTypeInfo<BotMessageCreateGame>::GetDefault().game_id; }
};

template <>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data_static<3>
{
  using member_type = GameInstanceData; // GameInstanceData
  static constexpr auto GetName() { return "game_settings"; }
  static constexpr auto GetType() { return "GameInstanceData"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4E015FE3; }
  static constexpr unsigned GetTypeNameHash() { return 0xC7A440E6; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &BotMessageCreateGame::game_settings; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data<3, Self> : public StormReflTypeInfo<BotMessageCreateGame>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, GameInstanceData> & Get() { return self.game_settings; }
  std::add_const_t<std::remove_reference_t<GameInstanceData>> & Get() const { return self.game_settings; }
  void SetDefault() { self.game_settings = StormReflTypeInfo<BotMessageCreateGame>::GetDefault().game_settings; }
};

template <>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data_static<4>
{
  using member_type = std::vector<std::tuple<DDSKey, DDSKey, int> >; // std::vector<std::tuple<unsigned long long, unsigned long long, int>, std::allocator<std::tuple<unsigned long long, unsigned long long, int> > >
  static constexpr auto GetName() { return "players"; }
  static constexpr auto GetType() { return "std::vector<std::tuple<unsigned long long, unsigned long long, int>, std::allocator<std::tuple<unsigned long long, unsigned long long, int> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x264E43A6; }
  static constexpr unsigned GetTypeNameHash() { return 0x77CA8AFF; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &BotMessageCreateGame::players; }
};

template <typename Self>
struct StormReflTypeInfo<BotMessageCreateGame>::field_data<4, Self> : public StormReflTypeInfo<BotMessageCreateGame>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::tuple<DDSKey, DDSKey, int> >> & Get() { return self.players; }
  std::add_const_t<std::remove_reference_t<std::vector<std::tuple<DDSKey, DDSKey, int> >>> & Get() const { return self.players; }
  void SetDefault() { self.players = StormReflTypeInfo<BotMessageCreateGame>::GetDefault().players; }
};

namespace StormReflFileInfo
{
  struct BotMessages
  {
    static const int types_n = 11;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct BotMessages::type_info<0>
  {
    using type = ::BotMessageBase;
  };

  template <>
  struct BotMessages::type_info<1>
  {
    using type = ::BotErrorMessage;
  };

  template <>
  struct BotMessages::type_info<2>
  {
    using type = ::BotIdentify;
  };

  template <>
  struct BotMessages::type_info<3>
  {
    using type = ::BotMessageUpdate;
  };

  template <>
  struct BotMessages::type_info<4>
  {
    using type = ::BotMessageChannelChat;
  };

  template <>
  struct BotMessages::type_info<5>
  {
    using type = ::BotMessageRelocate;
  };

  template <>
  struct BotMessages::type_info<6>
  {
    using type = ::BotMessageSendChatToChannel;
  };

  template <>
  struct BotMessages::type_info<7>
  {
    using type = ::BotMessageChannelMotd;
  };

  template <>
  struct BotMessages::type_info<8>
  {
    using type = ::BotMessageSendChatToUser;
  };

  template <>
  struct BotMessages::type_info<9>
  {
    using type = ::BotMessageGameResult;
  };

  template <>
  struct BotMessages::type_info<10>
  {
    using type = ::BotMessageCreateGame;
  };

}

