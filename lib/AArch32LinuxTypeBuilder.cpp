#include "AArch32LinuxTypeBuilder.h"

#include "AArchLinuxStructBuilder.h"

#include "llvm/Support/Casting.h"

#include <vector>

using namespace std;

StructType *AArch32LinuxTypeBuilder::getStruct(std::span<Type *> members) {
  return ::getStruct(members, linux);
}

VectorType *AArch32LinuxTypeBuilder::getVector(size_t bits) {
  assert((bits == 64) || (bits == 128));

  return new VectorType(bits);
}

UnionType *AArch32LinuxTypeBuilder::getUnion(std::span<Type *> members) {
  size_t maxAlign = 0;
  size_t sizeUnion = 0;
  vector<Type *> result;
  for (Type *member : members) {
    size_t align = linux->getAlignmentOf(member);
    size_t size = linux->getSizeOf(member);
    maxAlign = std::max(maxAlign, align);
    sizeUnion = std::max(sizeUnion, size);
    result.push_back(member);
  }

  return new UnionType(result, sizeUnion, maxAlign);
}

BitfieldType *AArch32LinuxTypeBuilder::getBitfield(Type *type, size_t bits) {
  assert(isFundamentalDataType(type));

  size_t sizeInBytes = linux->getSizeOf(type);
  return new BitfieldType(type, sizeInBytes, bits);
}

bool AArch32LinuxTypeBuilder::isFundamentalDataType(const Type *type) const {
  return llvm::isa<BuiltinType>(type) || llvm::isa<PointerType>(type) ||
         llvm::isa<VectorType>(type);
}



// FIXME AArchLinuxTypeBuilder ?
