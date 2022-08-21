#include "AArch32LinuxTypeBuilder.h"

#include "AArchLinuxStructBuilder.h"

#include "llvm/Support/Casting.h"

//#include <vector>

using namespace std;

StructType *AArch32LinuxTypeBuilder::getStruct(std::span<Type *> members) {
  return ::getStruct(members, target);
}

bool AArch32LinuxTypeBuilder::isSupportedVectorLength(size_t bits) const {
  return (bits == 64) || (bits == 128);
}

bool AArch32LinuxTypeBuilder::isSupportedBitFieldType(const Type *type) const {
  return llvm::isa<BuiltinType>(type) || llvm::isa<PointerType>(type) ||
         llvm::isa<VectorType>(type);
}
