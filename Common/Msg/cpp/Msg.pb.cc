// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "Msg.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* Msg_Login_C2S_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Msg_Login_C2S_reflection_ = NULL;
const ::google::protobuf::Descriptor* Msg_Login_S2C_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Msg_Login_S2C_reflection_ = NULL;
const ::google::protobuf::Descriptor* Msg_Connect_S2C_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Msg_Connect_S2C_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* MsgType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_Msg_2eproto() {
  protobuf_AddDesc_Msg_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "Msg.proto");
  GOOGLE_CHECK(file != NULL);
  Msg_Login_C2S_descriptor_ = file->message_type(0);
  static const int Msg_Login_C2S_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_C2S, msgid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_C2S, conmethod_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_C2S, szname_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_C2S, szpassword_),
  };
  Msg_Login_C2S_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Msg_Login_C2S_descriptor_,
      Msg_Login_C2S::default_instance_,
      Msg_Login_C2S_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_C2S, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_C2S, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Msg_Login_C2S));
  Msg_Login_S2C_descriptor_ = file->message_type(1);
  static const int Msg_Login_S2C_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_S2C, msgid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_S2C, logintimestamp_),
  };
  Msg_Login_S2C_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Msg_Login_S2C_descriptor_,
      Msg_Login_S2C::default_instance_,
      Msg_Login_S2C_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_S2C, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Login_S2C, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Msg_Login_S2C));
  Msg_Connect_S2C_descriptor_ = file->message_type(2);
  static const int Msg_Connect_S2C_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Connect_S2C, msgid_),
  };
  Msg_Connect_S2C_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Msg_Connect_S2C_descriptor_,
      Msg_Connect_S2C::default_instance_,
      Msg_Connect_S2C_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Connect_S2C, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Msg_Connect_S2C, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Msg_Connect_S2C));
  MsgType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_Msg_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Msg_Login_C2S_descriptor_, &Msg_Login_C2S::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Msg_Login_S2C_descriptor_, &Msg_Login_S2C::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Msg_Connect_S2C_descriptor_, &Msg_Connect_S2C::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_Msg_2eproto() {
  delete Msg_Login_C2S::default_instance_;
  delete Msg_Login_C2S_reflection_;
  delete Msg_Login_S2C::default_instance_;
  delete Msg_Login_S2C_reflection_;
  delete Msg_Connect_S2C::default_instance_;
  delete Msg_Connect_S2C_reflection_;
}

void protobuf_AddDesc_Msg_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\tMsg.proto\"j\n\rMsg_Login_C2S\022\"\n\005MsgID\030\001 "
    "\001(\0162\010.MsgType:\tLOGIN_C2S\022\021\n\tconMethod\030\002 "
    "\002(\005\022\016\n\006szName\030\003 \002(\t\022\022\n\nszPassWord\030\004 \002(\t\""
    "K\n\rMsg_Login_S2C\022\"\n\005MsgID\030\001 \001(\0162\010.MsgTyp"
    "e:\tLOGIN_S2C\022\026\n\016LoginTimeStamp\030\002 \002(\003\"7\n\017"
    "Msg_Connect_S2C\022$\n\005MsgID\030\001 \001(\0162\010.MsgType"
    ":\013Connect_S2C*8\n\007MsgType\022\r\n\tLOGIN_C2S\020\000\022"
    "\r\n\tLOGIN_S2C\020\001\022\017\n\013Connect_S2C\020\002", 311);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "Msg.proto", &protobuf_RegisterTypes);
  Msg_Login_C2S::default_instance_ = new Msg_Login_C2S();
  Msg_Login_S2C::default_instance_ = new Msg_Login_S2C();
  Msg_Connect_S2C::default_instance_ = new Msg_Connect_S2C();
  Msg_Login_C2S::default_instance_->InitAsDefaultInstance();
  Msg_Login_S2C::default_instance_->InitAsDefaultInstance();
  Msg_Connect_S2C::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_Msg_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_Msg_2eproto {
  StaticDescriptorInitializer_Msg_2eproto() {
    protobuf_AddDesc_Msg_2eproto();
  }
} static_descriptor_initializer_Msg_2eproto_;
const ::google::protobuf::EnumDescriptor* MsgType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MsgType_descriptor_;
}
bool MsgType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int Msg_Login_C2S::kMsgIDFieldNumber;
const int Msg_Login_C2S::kConMethodFieldNumber;
const int Msg_Login_C2S::kSzNameFieldNumber;
const int Msg_Login_C2S::kSzPassWordFieldNumber;
#endif  // !_MSC_VER

Msg_Login_C2S::Msg_Login_C2S()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Msg_Login_C2S::InitAsDefaultInstance() {
}

Msg_Login_C2S::Msg_Login_C2S(const Msg_Login_C2S& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Msg_Login_C2S::SharedCtor() {
  _cached_size_ = 0;
  msgid_ = 0;
  conmethod_ = 0;
  szname_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  szpassword_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Msg_Login_C2S::~Msg_Login_C2S() {
  SharedDtor();
}

void Msg_Login_C2S::SharedDtor() {
  if (szname_ != &::google::protobuf::internal::kEmptyString) {
    delete szname_;
  }
  if (szpassword_ != &::google::protobuf::internal::kEmptyString) {
    delete szpassword_;
  }
  if (this != default_instance_) {
  }
}

void Msg_Login_C2S::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Msg_Login_C2S::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Msg_Login_C2S_descriptor_;
}

const Msg_Login_C2S& Msg_Login_C2S::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Msg_2eproto();
  return *default_instance_;
}

Msg_Login_C2S* Msg_Login_C2S::default_instance_ = NULL;

Msg_Login_C2S* Msg_Login_C2S::New() const {
  return new Msg_Login_C2S;
}

void Msg_Login_C2S::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    msgid_ = 0;
    conmethod_ = 0;
    if (has_szname()) {
      if (szname_ != &::google::protobuf::internal::kEmptyString) {
        szname_->clear();
      }
    }
    if (has_szpassword()) {
      if (szpassword_ != &::google::protobuf::internal::kEmptyString) {
        szpassword_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Msg_Login_C2S::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .MsgType MsgID = 1 [default = LOGIN_C2S];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::MsgType_IsValid(value)) {
            set_msgid(static_cast< ::MsgType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_conMethod;
        break;
      }

      // required int32 conMethod = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_conMethod:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &conmethod_)));
          set_has_conmethod();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_szName;
        break;
      }

      // required string szName = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_szName:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_szname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->szname().data(), this->szname().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_szPassWord;
        break;
      }

      // required string szPassWord = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_szPassWord:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_szpassword()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->szpassword().data(), this->szpassword().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Msg_Login_C2S::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .MsgType MsgID = 1 [default = LOGIN_C2S];
  if (has_msgid()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->msgid(), output);
  }

  // required int32 conMethod = 2;
  if (has_conmethod()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->conmethod(), output);
  }

  // required string szName = 3;
  if (has_szname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->szname().data(), this->szname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->szname(), output);
  }

  // required string szPassWord = 4;
  if (has_szpassword()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->szpassword().data(), this->szpassword().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->szpassword(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Msg_Login_C2S::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .MsgType MsgID = 1 [default = LOGIN_C2S];
  if (has_msgid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->msgid(), target);
  }

  // required int32 conMethod = 2;
  if (has_conmethod()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->conmethod(), target);
  }

  // required string szName = 3;
  if (has_szname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->szname().data(), this->szname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->szname(), target);
  }

  // required string szPassWord = 4;
  if (has_szpassword()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->szpassword().data(), this->szpassword().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->szpassword(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Msg_Login_C2S::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .MsgType MsgID = 1 [default = LOGIN_C2S];
    if (has_msgid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->msgid());
    }

    // required int32 conMethod = 2;
    if (has_conmethod()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->conmethod());
    }

    // required string szName = 3;
    if (has_szname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->szname());
    }

    // required string szPassWord = 4;
    if (has_szpassword()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->szpassword());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Msg_Login_C2S::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Msg_Login_C2S* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Msg_Login_C2S*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Msg_Login_C2S::MergeFrom(const Msg_Login_C2S& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_msgid()) {
      set_msgid(from.msgid());
    }
    if (from.has_conmethod()) {
      set_conmethod(from.conmethod());
    }
    if (from.has_szname()) {
      set_szname(from.szname());
    }
    if (from.has_szpassword()) {
      set_szpassword(from.szpassword());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Msg_Login_C2S::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Msg_Login_C2S::CopyFrom(const Msg_Login_C2S& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Msg_Login_C2S::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000e) != 0x0000000e) return false;

  return true;
}

void Msg_Login_C2S::Swap(Msg_Login_C2S* other) {
  if (other != this) {
    std::swap(msgid_, other->msgid_);
    std::swap(conmethod_, other->conmethod_);
    std::swap(szname_, other->szname_);
    std::swap(szpassword_, other->szpassword_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Msg_Login_C2S::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Msg_Login_C2S_descriptor_;
  metadata.reflection = Msg_Login_C2S_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Msg_Login_S2C::kMsgIDFieldNumber;
const int Msg_Login_S2C::kLoginTimeStampFieldNumber;
#endif  // !_MSC_VER

Msg_Login_S2C::Msg_Login_S2C()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Msg_Login_S2C::InitAsDefaultInstance() {
}

Msg_Login_S2C::Msg_Login_S2C(const Msg_Login_S2C& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Msg_Login_S2C::SharedCtor() {
  _cached_size_ = 0;
  msgid_ = 1;
  logintimestamp_ = GOOGLE_LONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Msg_Login_S2C::~Msg_Login_S2C() {
  SharedDtor();
}

void Msg_Login_S2C::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Msg_Login_S2C::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Msg_Login_S2C::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Msg_Login_S2C_descriptor_;
}

const Msg_Login_S2C& Msg_Login_S2C::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Msg_2eproto();
  return *default_instance_;
}

Msg_Login_S2C* Msg_Login_S2C::default_instance_ = NULL;

Msg_Login_S2C* Msg_Login_S2C::New() const {
  return new Msg_Login_S2C;
}

void Msg_Login_S2C::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    msgid_ = 1;
    logintimestamp_ = GOOGLE_LONGLONG(0);
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Msg_Login_S2C::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .MsgType MsgID = 1 [default = LOGIN_S2C];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::MsgType_IsValid(value)) {
            set_msgid(static_cast< ::MsgType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_LoginTimeStamp;
        break;
      }

      // required int64 LoginTimeStamp = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_LoginTimeStamp:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &logintimestamp_)));
          set_has_logintimestamp();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Msg_Login_S2C::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .MsgType MsgID = 1 [default = LOGIN_S2C];
  if (has_msgid()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->msgid(), output);
  }

  // required int64 LoginTimeStamp = 2;
  if (has_logintimestamp()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->logintimestamp(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Msg_Login_S2C::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .MsgType MsgID = 1 [default = LOGIN_S2C];
  if (has_msgid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->msgid(), target);
  }

  // required int64 LoginTimeStamp = 2;
  if (has_logintimestamp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->logintimestamp(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Msg_Login_S2C::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .MsgType MsgID = 1 [default = LOGIN_S2C];
    if (has_msgid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->msgid());
    }

    // required int64 LoginTimeStamp = 2;
    if (has_logintimestamp()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->logintimestamp());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Msg_Login_S2C::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Msg_Login_S2C* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Msg_Login_S2C*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Msg_Login_S2C::MergeFrom(const Msg_Login_S2C& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_msgid()) {
      set_msgid(from.msgid());
    }
    if (from.has_logintimestamp()) {
      set_logintimestamp(from.logintimestamp());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Msg_Login_S2C::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Msg_Login_S2C::CopyFrom(const Msg_Login_S2C& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Msg_Login_S2C::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000002) != 0x00000002) return false;

  return true;
}

void Msg_Login_S2C::Swap(Msg_Login_S2C* other) {
  if (other != this) {
    std::swap(msgid_, other->msgid_);
    std::swap(logintimestamp_, other->logintimestamp_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Msg_Login_S2C::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Msg_Login_S2C_descriptor_;
  metadata.reflection = Msg_Login_S2C_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Msg_Connect_S2C::kMsgIDFieldNumber;
#endif  // !_MSC_VER

Msg_Connect_S2C::Msg_Connect_S2C()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Msg_Connect_S2C::InitAsDefaultInstance() {
}

Msg_Connect_S2C::Msg_Connect_S2C(const Msg_Connect_S2C& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Msg_Connect_S2C::SharedCtor() {
  _cached_size_ = 0;
  msgid_ = 2;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Msg_Connect_S2C::~Msg_Connect_S2C() {
  SharedDtor();
}

void Msg_Connect_S2C::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Msg_Connect_S2C::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Msg_Connect_S2C::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Msg_Connect_S2C_descriptor_;
}

const Msg_Connect_S2C& Msg_Connect_S2C::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_Msg_2eproto();
  return *default_instance_;
}

Msg_Connect_S2C* Msg_Connect_S2C::default_instance_ = NULL;

Msg_Connect_S2C* Msg_Connect_S2C::New() const {
  return new Msg_Connect_S2C;
}

void Msg_Connect_S2C::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    msgid_ = 2;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Msg_Connect_S2C::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .MsgType MsgID = 1 [default = Connect_S2C];
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::MsgType_IsValid(value)) {
            set_msgid(static_cast< ::MsgType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Msg_Connect_S2C::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .MsgType MsgID = 1 [default = Connect_S2C];
  if (has_msgid()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->msgid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Msg_Connect_S2C::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .MsgType MsgID = 1 [default = Connect_S2C];
  if (has_msgid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->msgid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Msg_Connect_S2C::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .MsgType MsgID = 1 [default = Connect_S2C];
    if (has_msgid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->msgid());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Msg_Connect_S2C::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Msg_Connect_S2C* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Msg_Connect_S2C*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Msg_Connect_S2C::MergeFrom(const Msg_Connect_S2C& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_msgid()) {
      set_msgid(from.msgid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Msg_Connect_S2C::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Msg_Connect_S2C::CopyFrom(const Msg_Connect_S2C& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Msg_Connect_S2C::IsInitialized() const {

  return true;
}

void Msg_Connect_S2C::Swap(Msg_Connect_S2C* other) {
  if (other != this) {
    std::swap(msgid_, other->msgid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Msg_Connect_S2C::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Msg_Connect_S2C_descriptor_;
  metadata.reflection = Msg_Connect_S2C_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
