#pragma once

#include "Types.h"

class TypeBuilder {
public:
  virtual StructType *getStruct(std::span<Type *> members) = 0;

  virtual VectorType *getVector(size_t bits) = 0;
};
