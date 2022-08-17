#pragma once

#include "AArch64Linux.h"
#include "TypeBuilder.h"

class AArch64LinuxTypeBuilder : public TypeBuilder {
  AArch64Linux *linux;

public:
  AArch64LinuxTypeBuilder(AArch64Linux *linux) : linux(linux) {}

  StructType *getStruct(std::span<Type *> members) override;

  VectorType *getVector(size_t bits) override;

  UnionType *getUnion(std::span<Type *> members) override;

  BitfieldType *getBitfield(Type *type, size_t bits) override;

 private:

  bool isFundamentalDataType(const Type *) const;

};
