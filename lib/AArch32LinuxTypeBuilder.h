#pragma once

#include "AArch32Linux.h"
#include "TypeBuilder.h"

class AArch32LinuxTypeBuilder : public TypeBuilder {
  AArch32Linux *linux;

public:
  AArch32LinuxTypeBuilder(AArch32Linux *linux) : linux(linux) {}

  StructType *getStruct(std::span<Type *> members) override;

  VectorType *getVector(size_t bits) override;

  UnionType *getUnion(std::span<Type *> members) override;

  BitfieldType *getBitfield(Type *type, size_t bits) override;

private:
  bool isFundamentalDataType(const Type *) const;
};
