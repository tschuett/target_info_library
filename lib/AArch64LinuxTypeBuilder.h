#pragma once

#include "AArch64Linux.h"
#include "TypeBuilder.h"

class AArch64LinuxTypeBuilder : public TypeBuilder {

public:
  AArch64LinuxTypeBuilder(AArch64Linux *linux) : TypeBuilder(linux) {}

  BuiltinType *getBuiltin(BuiltinKind bk) override;

  StructType *getStruct(std::span<Type *> members) override;

private:
  bool isSupportedVectorLength(size_t bits) const override;

  bool isSupportedBitFieldType(const Type *) const override;

  bool areScalableTypesSupported() const override { return true; }
  };
