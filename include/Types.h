#pragma once

#include <span>
#include <vector>

#include "Signature.h"

enum class BuiltinKind {
  Byte,
  Short,
  Word,
  DoubleWord,
  QuadWord,
  Half,
  Single,
  Double,
  QuadFloat,
  SingleDecimal,
  DoubleDecimal,
  QuadDecimal,
};

class Type {
public:
  enum class TypeKind {
    ArrayType,
    BitfieldType,
    BuiltinType,
    FunctionType,
    PointerType,
    ScalableVectorType,
    ScalablePredicateType,
    StructType,
    UnionType,
    VectorType,
  };

private:
  const TypeKind kind;

public:
  Type(TypeKind K) : kind(K) {}
  TypeKind getKind() const { return kind; }
};

class BuiltinType : public Type {
  BuiltinKind builtin;

public:
  BuiltinType(BuiltinKind bk) : Type(TypeKind::BuiltinType), builtin(bk) {}

  BuiltinKind getKind() const { return builtin; };

  bool isFloatAAPCS() const {
    return (builtin == BuiltinKind::Half) || (builtin == BuiltinKind::Single) ||
           (builtin == BuiltinKind::Double) ||
           (builtin == BuiltinKind::QuadFloat) ||
           (builtin == BuiltinKind::SingleDecimal) ||
           (builtin == BuiltinKind::DoubleDecimal) ||
           (builtin == BuiltinKind::QuadDecimal);
  }

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::BuiltinType;
  }
};

class VectorType : public Type {
  size_t bits;

public:
  VectorType(size_t bits) : Type(TypeKind::VectorType), bits(bits) {}

  size_t getBits() const { return bits; }

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::VectorType;
  }
};

class PointerType : public Type {
  BuiltinKind builtin;

public:
  PointerType(BuiltinKind bk) : Type(TypeKind::PointerType), builtin(bk) {}

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::PointerType;
  }
};

class ScalableVectorType : public Type {
  BuiltinKind builtin;

public:
  ScalableVectorType(BuiltinKind bk)
      : Type(TypeKind::ScalableVectorType), builtin(bk) {}

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::ScalableVectorType;
  }
};

class ScalablePredicateType : public Type {
  BuiltinKind builtin;

public:
  ScalablePredicateType(BuiltinKind bk)
      : Type(TypeKind::ScalablePredicateType), builtin(bk) {}

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::ScalablePredicateType;
  }
};

class FunctionType : public Type {
  Signature sig;

public:
  FunctionType(Signature sig) : Type(TypeKind::FunctionType), sig(sig) {}

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::FunctionType;
  }
};

class StructType : public Type {
  std::vector<Type *> members;

public:
  StructType(std::vector<Type *> members)
      : Type(TypeKind::StructType), members(members) {}

  std::vector<Type *> getMembers() const { return members; }

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::StructType;
  }
};

class ArrayType : public Type {
  Type *baseType;
  size_t elements;

public:
  ArrayType(Type *baseType, size_t elements)
      : Type(TypeKind::ArrayType), baseType(baseType), elements(elements) {}

  Type *getBaseType() const { return baseType; }
  size_t getNumberOfElements() const { return elements; }

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::ArrayType;
  }
};

class UnionType : public Type {
  std::vector<Type *> members;

public:
  UnionType(std::vector<Type *> members)
      : Type(TypeKind::UnionType), members(members) {}

  std::vector<Type *> getMembers() const { return members; }

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::UnionType;
  }
};

class BitfieldType : public Type {
  // Fundamental data type, i.e, BuiltinType, VectorType, ScalableVectorType,
  // ScalablePredicateType, PointerType
  Type *fundamentDataType;

  // FIXME fillness

public:
  BitfieldType(Type *type)
      : Type(TypeKind::BitfieldType), fundamentDataType(type) {}

  static bool classof(const Type *S) {
    return S->getKind() == TypeKind::BitfieldType;
  }
};

class TypeBuilder {};
