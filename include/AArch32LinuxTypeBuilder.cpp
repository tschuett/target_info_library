#include "AArch32LinuxTypeBuilder.h"

StructType *AArch32LinuxTypeBuilder::getStruct(std::span<Type *> members) {}

VectorType *AArch32LinuxTypeBuilder::getVector(size_t bits) {}

UnionType *AArch32LinuxTypeBuilder::getUnion(std::span<Type *> members) {}

BitfieldType *AArch32LinuxTypeBuilder::getBitfield(Type *type, size_t bits) {}

bool AArch32LinuxTypeBuilder::isFundamentalDataType(const Type *) const {}
