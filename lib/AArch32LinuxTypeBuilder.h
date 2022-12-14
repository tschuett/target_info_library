#pragma once

#include "AArch32Linux.h"
#include "TypeBuilder.h"

class AArch32LinuxTypeBuilder : public TypeBuilder {
public:
  AArch32LinuxTypeBuilder(AArch32Linux *linux) : TypeBuilder(linux) {}

  StructType *getStruct(std::span<Type *> members) override;

private:
  virtual bool isSupportedVectorLength(size_t bits) const override;

  virtual bool isSupportedBitFieldType(const Type *) const override;

  bool areScalableTypesSupported() const override { return false; }
};
