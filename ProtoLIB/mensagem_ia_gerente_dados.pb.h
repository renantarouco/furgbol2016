// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mensagem_ia_gerente_dados.proto

#ifndef PROTOBUF_mensagem_5fia_5fgerente_5fdados_2eproto__INCLUDED
#define PROTOBUF_mensagem_5fia_5fgerente_5fdados_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_mensagem_5fia_5fgerente_5fdados_2eproto();
void protobuf_AssignDesc_mensagem_5fia_5fgerente_5fdados_2eproto();
void protobuf_ShutdownFile_mensagem_5fia_5fgerente_5fdados_2eproto();

class PacoteVelocidades;
class PacoteIAGerenteDados;

// ===================================================================

class PacoteVelocidades : public ::google::protobuf::Message {
 public:
  PacoteVelocidades();
  virtual ~PacoteVelocidades();
  
  PacoteVelocidades(const PacoteVelocidades& from);
  
  inline PacoteVelocidades& operator=(const PacoteVelocidades& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const PacoteVelocidades& default_instance();
  
  void Swap(PacoteVelocidades* other);
  
  // implements Message ----------------------------------------------
  
  PacoteVelocidades* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PacoteVelocidades& from);
  void MergeFrom(const PacoteVelocidades& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);
  
  // required float vx = 2;
  inline bool has_vx() const;
  inline void clear_vx();
  static const int kVxFieldNumber = 2;
  inline float vx() const;
  inline void set_vx(float value);
  
  // required float vy = 3;
  inline bool has_vy() const;
  inline void clear_vy();
  static const int kVyFieldNumber = 3;
  inline float vy() const;
  inline void set_vy(float value);
  
  // required float vtheta = 4;
  inline bool has_vtheta() const;
  inline void clear_vtheta();
  static const int kVthetaFieldNumber = 4;
  inline float vtheta() const;
  inline void set_vtheta(float value);
  
  // @@protoc_insertion_point(class_scope:PacoteVelocidades)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_vx();
  inline void clear_has_vx();
  inline void set_has_vy();
  inline void clear_has_vy();
  inline void set_has_vtheta();
  inline void clear_has_vtheta();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::uint32 id_;
  float vx_;
  float vy_;
  float vtheta_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_mensagem_5fia_5fgerente_5fdados_2eproto();
  friend void protobuf_AssignDesc_mensagem_5fia_5fgerente_5fdados_2eproto();
  friend void protobuf_ShutdownFile_mensagem_5fia_5fgerente_5fdados_2eproto();
  
  void InitAsDefaultInstance();
  static PacoteVelocidades* default_instance_;
};
// -------------------------------------------------------------------

class PacoteIAGerenteDados : public ::google::protobuf::Message {
 public:
  PacoteIAGerenteDados();
  virtual ~PacoteIAGerenteDados();
  
  PacoteIAGerenteDados(const PacoteIAGerenteDados& from);
  
  inline PacoteIAGerenteDados& operator=(const PacoteIAGerenteDados& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const PacoteIAGerenteDados& default_instance();
  
  void Swap(PacoteIAGerenteDados* other);
  
  // implements Message ----------------------------------------------
  
  PacoteIAGerenteDados* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PacoteIAGerenteDados& from);
  void MergeFrom(const PacoteIAGerenteDados& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required uint32 numFrame = 1;
  inline bool has_numframe() const;
  inline void clear_numframe();
  static const int kNumFrameFieldNumber = 1;
  inline ::google::protobuf::uint32 numframe() const;
  inline void set_numframe(::google::protobuf::uint32 value);
  
  // repeated .PacoteVelocidades velocidades = 2;
  inline int velocidades_size() const;
  inline void clear_velocidades();
  static const int kVelocidadesFieldNumber = 2;
  inline const ::PacoteVelocidades& velocidades(int index) const;
  inline ::PacoteVelocidades* mutable_velocidades(int index);
  inline ::PacoteVelocidades* add_velocidades();
  inline const ::google::protobuf::RepeatedPtrField< ::PacoteVelocidades >&
      velocidades() const;
  inline ::google::protobuf::RepeatedPtrField< ::PacoteVelocidades >*
      mutable_velocidades();
  
  // @@protoc_insertion_point(class_scope:PacoteIAGerenteDados)
 private:
  inline void set_has_numframe();
  inline void clear_has_numframe();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::PacoteVelocidades > velocidades_;
  ::google::protobuf::uint32 numframe_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_mensagem_5fia_5fgerente_5fdados_2eproto();
  friend void protobuf_AssignDesc_mensagem_5fia_5fgerente_5fdados_2eproto();
  friend void protobuf_ShutdownFile_mensagem_5fia_5fgerente_5fdados_2eproto();
  
  void InitAsDefaultInstance();
  static PacoteIAGerenteDados* default_instance_;
};
// ===================================================================


// ===================================================================

// PacoteVelocidades

// required uint32 id = 1;
inline bool PacoteVelocidades::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PacoteVelocidades::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PacoteVelocidades::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PacoteVelocidades::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 PacoteVelocidades::id() const {
  return id_;
}
inline void PacoteVelocidades::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
}

// required float vx = 2;
inline bool PacoteVelocidades::has_vx() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PacoteVelocidades::set_has_vx() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PacoteVelocidades::clear_has_vx() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PacoteVelocidades::clear_vx() {
  vx_ = 0;
  clear_has_vx();
}
inline float PacoteVelocidades::vx() const {
  return vx_;
}
inline void PacoteVelocidades::set_vx(float value) {
  set_has_vx();
  vx_ = value;
}

// required float vy = 3;
inline bool PacoteVelocidades::has_vy() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PacoteVelocidades::set_has_vy() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PacoteVelocidades::clear_has_vy() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PacoteVelocidades::clear_vy() {
  vy_ = 0;
  clear_has_vy();
}
inline float PacoteVelocidades::vy() const {
  return vy_;
}
inline void PacoteVelocidades::set_vy(float value) {
  set_has_vy();
  vy_ = value;
}

// required float vtheta = 4;
inline bool PacoteVelocidades::has_vtheta() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PacoteVelocidades::set_has_vtheta() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PacoteVelocidades::clear_has_vtheta() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PacoteVelocidades::clear_vtheta() {
  vtheta_ = 0;
  clear_has_vtheta();
}
inline float PacoteVelocidades::vtheta() const {
  return vtheta_;
}
inline void PacoteVelocidades::set_vtheta(float value) {
  set_has_vtheta();
  vtheta_ = value;
}

// -------------------------------------------------------------------

// PacoteIAGerenteDados

// required uint32 numFrame = 1;
inline bool PacoteIAGerenteDados::has_numframe() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PacoteIAGerenteDados::set_has_numframe() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PacoteIAGerenteDados::clear_has_numframe() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PacoteIAGerenteDados::clear_numframe() {
  numframe_ = 0u;
  clear_has_numframe();
}
inline ::google::protobuf::uint32 PacoteIAGerenteDados::numframe() const {
  return numframe_;
}
inline void PacoteIAGerenteDados::set_numframe(::google::protobuf::uint32 value) {
  set_has_numframe();
  numframe_ = value;
}

// repeated .PacoteVelocidades velocidades = 2;
inline int PacoteIAGerenteDados::velocidades_size() const {
  return velocidades_.size();
}
inline void PacoteIAGerenteDados::clear_velocidades() {
  velocidades_.Clear();
}
inline const ::PacoteVelocidades& PacoteIAGerenteDados::velocidades(int index) const {
  return velocidades_.Get(index);
}
inline ::PacoteVelocidades* PacoteIAGerenteDados::mutable_velocidades(int index) {
  return velocidades_.Mutable(index);
}
inline ::PacoteVelocidades* PacoteIAGerenteDados::add_velocidades() {
  return velocidades_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::PacoteVelocidades >&
PacoteIAGerenteDados::velocidades() const {
  return velocidades_;
}
inline ::google::protobuf::RepeatedPtrField< ::PacoteVelocidades >*
PacoteIAGerenteDados::mutable_velocidades() {
  return &velocidades_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_mensagem_5fia_5fgerente_5fdados_2eproto__INCLUDED