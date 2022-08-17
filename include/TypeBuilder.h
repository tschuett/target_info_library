#pragma once

#include "Struct.h"
#include "Types.h"

class TypeBuilder {
public:
  virtual StructType *getStruct(std::span<Type *> members) = 0;

  virtual VectorType *getVector(size_t bits) = 0;

  virtual UnionType *getUnion(std::span<Type *> members) = 0;

  virtual BitfieldType *getBitfield(Type *type, size_t bits) = 0;
};
