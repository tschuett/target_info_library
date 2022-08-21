#include "TypeBuilder.h"

#include "Types.h"

ArrayType *getArray(Type *type, size_t elements) {
  return new ArrayType(type, elements);
}

BitfieldType *TypeBuilder::getBitfield(Type *type, size_t bits) {
  assert(isSupportedBitFieldType(type));

  size_t sizeInBytes = target->getSizeOf(type);
  return new BitfieldType(type, sizeInBytes, bits);
}

BuiltinType *TypeBuilder::getBuiltin(BuiltinKind bk) {
  return new BuiltinType(bk);
}

UnionType *TypeBuilder::getUnion(std::span<Type *> members) {
  size_t maxAlign = 0;
  size_t sizeUnion = 0;
  std::vector<Type *> result;
  for (Type *member : members) {
    size_t align = target->getAlignmentOf(member);
    size_t size = target->getSizeOf(member);
    maxAlign = std::max(maxAlign, align);
    sizeUnion = std::max(sizeUnion, size);
    result.push_back(member);
  }

  return new UnionType(result, sizeUnion, maxAlign);
}

VectorType *TypeBuilder::getVector(size_t bits) {
  assert(isSupportedVectorLength(bits));

  return new VectorType(bits);
}

ScalableVectorType *TypeBuilder::getScalableVector(BuiltinKind baseType) {
  if (areScalableTypesSupported()) {
    return new ScalableVectorType(baseType);
  }

  return nullptr;
}

ScalablePredicateType *TypeBuilder::getScalablePredicate(BuiltinKind baseType) {
  if (areScalableTypesSupported()) {
    return new ScalablePredicateType(baseType);
  }

  return nullptr;
}

FunctionType *TypeBuilder::getFunction(Signature sig) {
  return new FunctionType(sig);
}

PointerType *TypeBuilder::getPointer(BuiltinKind baseType) {
  return new PointerType(baseType);
}
