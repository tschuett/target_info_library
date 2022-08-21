#pragma once

#include "TargetInfo.h"
#include "TypeBuilder.h"
#include "Types.h"

class X86LinuxTypeBuilder : public TypeBuilder {
public:
  X86LinuxTypeBuilder(TargetInfo *linux) : TypeBuilder(linux) {}

  StructType *getStruct(std::span<Type *> members) override;

private:
  //bool isFundamentalDataType(Type *) const;

  virtual bool isSupportedVectorLength(size_t bits) const override;

  virtual bool isSupportedBitFieldType(const Type *) const override;

  bool areScalableTypesSupported() const override { return false; }
};
