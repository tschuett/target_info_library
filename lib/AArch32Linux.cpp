#include "AArch32Linux.h"

#include "AArch32LinuxTypeBuilder.h"
#include "Struct.h"
#include "Types.h"

#include "llvm/Support/Casting.h"

const uint8_t POINTER_SIZE = 4;

using namespace llvm;
using namespace std;

// https://github.com/ARM-software/abi-aa/blob/main/aapcs32/aapcs32.rst

bool AArch32Linux::isBigEndian() { return false; }

bool AArch32Linux::isCharSigned() { return false; }

size_t AArch32Linux::getSizeOf(const Type *type) {

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
    case BuiltinKind::Half:
      return 2;
    case BuiltinKind::Single:
      return 4;
    case BuiltinKind::Double:
      return 8;
    default:
      assert(false);
      return 0;
    }
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    size_t bits = vector->getBits();
    assert((bits == 64) || (bits == 128));
    return bits / 8;
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // 5.9.1 Aggregates
    return aggre->getSizeInBytes();
  } else if (auto unio = dyn_cast<UnionType>(type)) {
    // 5.9.2 Union
    return unio->getSizeInBytes();
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // 5.9.3 Array
    Type *baseType = arra->getBaseType();
    return getSizeOf(baseType) * arra->getNumberOfElements();
  } else {
    assert(false);
  }
}

size_t AArch32Linux::getAlignmentOf(const Type *type) {
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
    case BuiltinKind::Half:
      return 2;
    case BuiltinKind::Single:
      return 4;
    case BuiltinKind::Double:
      return 8;
    default:
      assert(false);
      return 0;
    }
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    size_t bits = vector->getBits();
    assert((bits == 64) || (bits == 128));
    return bits / 8;
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // 5.9.1 Aggregates
    return aggre->getAlignmentInBytes();
  } else if (auto uni = dyn_cast<UnionType>(type)) {
    // 5.9.2 Union
    return uni->getAlignmentInBytes();
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // 5.9.3 Array
    Type *baseType = arra->getBaseType();
    return getAlignmentOf(baseType);
  } else {
    assert(false);
  }
}

CallWithLayoutAndCode AArch32Linux::getCall(/*const FunctionType *signature,*/
                                            std::span<Type *> arguments) {

  CallWithLayoutAndCode result;

  // Stage B – Pre-padding and extension of arguments
  unsigned idx = 0;
  for (Type *arg : arguments) {
    // B.1
    if (isDynamicallySizedType(arg)) {
      result.addAction(idx, new CopyToMemoryAction(arg));
    }

    // B.2
    if (isIntegralFundamentDataType(arg) && getSizeOf(arg) < 4) {
      result.addAction(idx, new ZeroOrSignExtendAction(arg, 4));
    }

    // B.3.cp

    // B.4
    if (auto aggre = llvm::dyn_cast<StructType>(arg)) {
      if (aggre->getSizeInBytes() % 4 != 0) {
        result.addAction(idx, new SizeRoundUpAction(arg, 4));
      }
    }

    // B.5.
    // FIXME

    ++idx;
  }

  // Stage C – Assignment of arguments to registers and stack
  idx = 0;
  for (Type *arg : arguments) {
    // C1.cp
    // FIXME

    // C2.cp
    // FIXME

    // C.3
    // skiped

    // C.4
    // skipped

    // C.5
    // skipped

    // C.6
    // skipped

    // C.7
    // skipped

    // C.8
    // skipped
  }

  // FIXME 6.4 Result Return

  return result;
}

TypeBuilder *AArch32Linux::getTypeBuilder() {
  return new AArch32LinuxTypeBuilder(this);
}

// 5.3.5   Homogeneous Aggregates
bool AArch32Linux::isHomogeneousAggregate(const Type *type) {
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

unsigned AArch32Linux::getNrOfBitsInLargestLockFreeInteger() const {
  return 64;
}

bool AArch32Linux::isDynamicallySizedType(Type *type) {
  if (auto aggre = llvm::dyn_cast<StructType>(type)) {
    return false;
  } else {
    return false;
  }
}

bool AArch32Linux::isIntegralFundamentDataType(Type *type) {
  if (auto builtin = llvm::dyn_cast<BuiltinType>(type)) {
    switch (builtin->getKind()) {
    case BuiltinKind::Byte:
      return true;
    case BuiltinKind::Short:
      return true;
    case BuiltinKind::Word:
      return true;
    case BuiltinKind::DoubleWord:
      return true;
    default:
      return false;
    }
  }

  return false;
}
