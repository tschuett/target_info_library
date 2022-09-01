#include "Types.h"
#include "riscv64.h"
#include "Struct.h"

#include "RiscvTypeBuilder.h"

#include "llvm/Support/Casting.h"

const unsigned XLEN = 64;
const unsigned FLEN = 64;
const unsigned POINTER_SIZE = 64;

using namespace llvm;

size_t RISCV64Linux::getSizeOf(const Type *type) {
  if (auto builtin = dyn_cast<BuiltinType>(type)) {
    switch(builtin->getKind()) {
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
    }
    // FIXME Complex
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    // FIXME
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // xxx Aggregates
    return aggre->getSizeInBytes();
  } else if (auto unio = dyn_cast<UnionType>(type)) {
    // xxx Union
    return unio->getSizeInBytes();
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // xxx Array
    Type *baseType = arra->getBaseType();
    return getSizeOf(baseType) * arra->getNumberOfElements();
  } else {
    assert(false);
  }
}

size_t RISCV64Linux::getAlignmentOf(const Type *type) {
  if (auto builtin = dyn_cast<BuiltinType>(type)) {
    switch(builtin->getKind()) {
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
    }
    // FIXME Complex
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    // FIXME
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // xxx Aggregates
    return aggre->getAlignmentInBytes();
  } else if (auto unio = dyn_cast<UnionType>(type)) {
    // xxx Union
    return unio->getAlignmentInBytes();
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // xxx Array
    Type *baseType = arra->getBaseType();
    // FIXME
    return getAlignmentOf(baseType);
  } else {
    assert(false);
  }
}

unsigned RISCV64Linux::getNrOfBitsInLargestLockFreeInteger() const {}

CallWithLayoutAndCode RISCV64Linux::getCall(std::span<Type *> arguments) {}

TypeBuilder *getTypeBuilder() {
  return new RiscvTypeBuilder(XLEN);
}
