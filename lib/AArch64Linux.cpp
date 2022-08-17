#include "AArch64Linux.h"

#include "Types.h"

#include "llvm/Support/Casting.h"

#include <cstddef>
#include <cstdlib>
#include <vector>

const uint8_t POINTER_SIZE = 8;

using namespace llvm;
using namespace std;

// https://github.com/ARM-software/abi-aa/blob/main/aapcs64/aapcs64.rst 2022Q1

// FIXME: 5.9.4   Bit-fields subdivision

bool AArch64Linux::isBigEndian() { return false; }

bool AArch64Linux::isCharSigned() {}

size_t AArch64Linux::getSizeOf(const Type *type) {

  if (auto builtin = dyn_cast<BuiltinType>(type)) {
    switch (builtin->getKind()) {
    case BuiltinKind::Byte:
      return 1;
    case BuiltinKind::Short:
      return 2;
    case BuiltinKind::Word:
      return 4;
    case BuiltinKind::DoubleWord:
      return 8;
    case BuiltinKind::QuadWord:
      return 16;
    case BuiltinKind::Half:
      return 2;
    case BuiltinKind::Single:
      return 4;
    case BuiltinKind::Double:
      return 8;
    case BuiltinKind::QuadFloat:
      return 16;
    case BuiltinKind::SingleDecimal:
      return 4;
    case BuiltinKind::DoubleDecimal:
      return 8;
    case BuiltinKind::QuadDecimal:
      return 16;
    }
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    size_t bits = vector->getBits();
    assert((bits == 64) || (bits == 128));
    return bits / 8;
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // 5.9.1 Aggregates
    std::vector<Type *> members = aggre->getMembers();
    return fitIntoAlignment(members);
  } else if (auto unio = dyn_cast<UnionType>(type)) {
    // 5.9.2 Union
    std::vector<Type *> members = unio->getMembers();
    return fitIntoAlignment(members);
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // 5.9.3 Array
    Type *baseType = arra->getBaseType();
    return getSizeOf(baseType) * arra->getNumberOfElements();
  } else {
    assert(false);
  }
}

size_t AArch64Linux::getAlignmentOf(const Type *type) {
  if (auto builtin = dyn_cast<BuiltinType>(type)) {
    switch (builtin->getKind()) {
    case BuiltinKind::Byte:
      return 1;
    case BuiltinKind::Short:
      return 2;
    case BuiltinKind::Word:
      return 4;
    case BuiltinKind::DoubleWord:
      return 8;
    case BuiltinKind::QuadWord:
      return 16;
    case BuiltinKind::Half:
      return 2;
    case BuiltinKind::Single:
      return 4;
    case BuiltinKind::Double:
      return 8;
    case BuiltinKind::QuadFloat:
      return 16;
    case BuiltinKind::SingleDecimal:
      return 4;
    case BuiltinKind::DoubleDecimal:
      return 8;
    case BuiltinKind::QuadDecimal:
      return 16;
    }
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    size_t bits = vector->getBits();
    assert((bits == 64) || (bits == 128));
    return bits / 8;
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // 5.9.1 Aggregates
    std::vector<Type *> members = aggre->getMembers();
    return getMaxAlignment(members);
  } else if (auto uni = dyn_cast<UnionType>(type)) {
    // 5.9.2 Union
    std::vector<Type *> members = uni->getMembers();
    return getMaxAlignment(members);
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // 5.9.3 Array
    Type *baseType = arra->getBaseType();
    return getAlignmentOf(baseType);
  } else {
    assert(false);
  }
}

bool AArch64Linux::isSupported(const Type *type) {
  switch (type->getKind()) {
  case Type::TypeKind::ArrayType: {
  }
  case Type::TypeKind::BitfieldType: {
  }
  case Type::TypeKind::BuiltinType: {
  }
  case Type::TypeKind::FunctionType: {
  }
  case Type::TypeKind::PointerType: {
  }
  case Type::TypeKind::ScalableVectorType: {
  }
  case Type::TypeKind::ScalablePredicateType: {
  }
  case Type::TypeKind::StructType: {
  }
  case Type::TypeKind::UnionType: {
  }
  case Type::TypeKind::VectorType: {
  }
  }
}

CallWithLayoutAndCode AArch64Linux::getCall(const FunctionType *signature,
                                            span<Type *> arguments) {}

size_t AArch64Linux::getMaxAlignment(std::span<Type *> members) {
  size_t maxAlign = 0;
  for (Type *mem : members) {
    size_t align = getAlignmentOf(mem);
    maxAlign = std::max(maxAlign, align);
  }
  return maxAlign;
};

size_t AArch64Linux::fitIntoAlignment(std::span<Type *> members) {
  size_t maxAlignment = getMaxAlignment(members);
  size_t sumSize = 0;
  for (Type *mem : members) {
    sumSize += getSizeOf(mem);
  }

  ldiv_t divResult = std::ldiv(sumSize, maxAlignment);
  if (divResult.rem == 0) {
    return sumSize;
  } else {
    return sumSize + divResult.rem * maxAlignment;
  }
}

// 5.9.5   Homogeneous Aggregates
bool AArch64Linux::isHomogeneousAggregate(Type *type) {
  if (auto struc = dyn_cast<StructType>(type)) {
    vector<Type *> members = struc->getMembers();
    if (members.empty())
      return true;

    Type::TypeKind kind = members[0]->getKind();
    for (Type *member : members) {
      if (member->getKind() != kind)
        return false;
    }
    return true;
  } else {
    // no struct
    return false;
  }
}

// 5.9.5.1   Homogeneous Floating-point Aggregates (HFA)
bool AArch64Linux::isHomogeneousFloatingPointAggregate(Type *type) {
  if (not isHomogeneousAggregate(type))
    return false;
  if (auto struc = dyn_cast<StructType>(type)) {
    vector<Type *> members = struc->getMembers();
    if (members.size() > 4)
      return false;
    if (auto mem = dyn_cast<BuiltinType>(members[0])) {
      return mem->isFloatAAPCS();
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// 5.9.5.2   Homogeneous Short-Vector Aggregates (HVA)
bool AArch64Linux::isHomogeneousShortVectorAggregate(Type *type) {
  if (not isHomogeneousAggregate(type))
    return false;
  if (auto struc = dyn_cast<StructType>(type)) {
    vector<Type *> members = struc->getMembers();
    if (members.size() > 4)
      return false;
    if (auto mem = dyn_cast<VectorType>(members[0])) {
      size_t bits = mem->getBits();
      // a short vector
      return (bits == 64) || (bits == 128);
    } else {
      return false;
    }
  }
  return false;
}

// 5.10 Pure Scalable Types(PSTs)
bool AArch64Linux::isPureScalabeType(Type *type) {
  // scalable vector
  if (auto scal = dyn_cast<ScalableVectorType>(type))
    return true;

  // scalable predicate vector
  if (auto scalPred = dyn_cast<ScalablePredicateType>(type))
    return true;

  // array
  if (auto arra = dyn_cast<ArrayType>(type)) {
    if (arra->getNumberOfElements() == 0)
      return false;
    return isPureScalabeType(arra->getBaseType());
  }

  // aggregate
  if (auto struc = dyn_cast<StructType>(type)) {
    if (not isHomogeneousAggregate(struc))
      return false;

    vector<Type *> members = struc->getMembers();
    return isPureScalabeType(members[0]);
  }

  return false;
}
