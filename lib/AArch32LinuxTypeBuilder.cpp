#include "AArch32LinuxTypeBuilder.h"


  AArch32LinuxTypeBuilder(AArch32Linux *linux) : linux(linux) {}

StructType *AArch32LinuxTypeBuilder::getStruct(std::span<Type *> members) override;

  VectorType *AArch32LinuxTypeBuilder::getVector(size_t bits) override;

  UnionType *AArch32LinuxTypeBuilder::getUnion(std::span<Type *> members) override;

  BitfieldType *AArch32LinuxTypeBuilder::getBitfield(Type *type, size_t bits) override;

  bool AArch32LinuxTypeBuilder::isFundamentalDataType(const Type *) const;
