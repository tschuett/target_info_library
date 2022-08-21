#include "X8664Linux.h"

#include "Actions.h"
#include "Struct.h"
#include "Types.h"
#include "X86LinuxTypeBuilder.h"

#include "llvm/Support/Casting.h"

const uint8_t POINTER_SIZE = 8;

using namespace llvm;
using namespace std;

bool X8664Linux::isBigEndian() { return false; }

bool X8664Linux::isCharSigned() { return true; }

size_t X8664Linux::getSizeOf(const Type *type) {
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
    case BuiltinKind::FloatWth80Bits:
      return 16;
    }
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    size_t bits = vector->getBits();
    assert((bits == 64) || (bits == 128) || (bits == 256) || (bits == 512));
    return bits / 8;
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    //  Aggregates
    return aggre->getSizeInBytes();
  } else if (auto unio = dyn_cast<UnionType>(type)) {
    //  Union
    return unio->getSizeInBytes();
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    //  Array
    Type *baseType = arra->getBaseType();
    return getSizeOf(baseType) * arra->getNumberOfElements();
  } else {
    assert(false);
  }
}

size_t X8664Linux::getAlignmentOf(const Type *type) {
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
    case BuiltinKind::FloatWth80Bits:
      return 16;
    }
  } else if (auto pointer = dyn_cast<PointerType>(type)) {
    return POINTER_SIZE;
  } else if (auto vector = dyn_cast<VectorType>(type)) {
    size_t bits = vector->getBits();
    assert((bits == 64) || (bits == 128) || (bits == 256) || (bits == 512));
    // Scalar Types
    switch (bits) {
    case 64:
      return 8;
    case 128:
      return 16;
    case 256:
      return 32;
    case 512:
      return 64;
    default:
      assert(false);
    }
  } else if (auto aggre = dyn_cast<StructType>(type)) {
    // Aggregates and Unions
    return aggre->getAlignmentInBytes();
  } else if (auto uni = dyn_cast<UnionType>(type)) {
    // Aggregates and Unions
    return uni->getAlignmentInBytes();
  } else if (auto arra = dyn_cast<ArrayType>(type)) {
    // Aggregates and Unions
    Type *baseType = arra->getBaseType();
    // size_t align = getAlignmentOf(baseType);
    // size_t size = getSizeOf(baseType);
    return getAlignmentOf(baseType);
  } else {
    assert(false);
  }
}

unsigned X8664Linux::getNrOfBitsInLargestLockFreeInteger() const { return 128; }

CallWithLayoutAndCode X8664Linux::getCall(std::span<Type *> arguments) {

  CallWithLayoutAndCode result;
  // June 21, 2022
  // 3.2 Function Calling Sequence
  // 3.2.3 Function Calling Sequence
  for (unsigned i = 0; i < arguments.size(); ++i) {
    ClassificationKind classification = getClassification(arguments[i]);

    result.addAction(i, new SizeRoundUpAction(arguments[i], 8));
  }

  return result;
}

TypeBuilder *X8664Linux::getTypeBuilder() { return &typeBuilder; }

X8664Linux::ClassificationKind X8664Linux::getClassification(Type *arg) {
  if (auto builtin = dyn_cast<BuiltinType>(arg)) {
    switch (builtin->getKind()) {
    case BuiltinKind::Byte:
    case BuiltinKind::Short:
    case BuiltinKind::Word:
      return ClassificationKind::Integer;
    case BuiltinKind::Half:
    case BuiltinKind::Single:
    case BuiltinKind::Double:
    case BuiltinKind::SingleDecimal:
    case BuiltinKind::DoubleDecimal:
      return ClassificationKind::SSE;
    case BuiltinKind::QuadFloat:
    case BuiltinKind::QuadDecimal:

    default:
      return xxx;
    }
  }
}
