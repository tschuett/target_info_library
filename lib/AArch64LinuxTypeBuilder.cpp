#include "AArch64LinuxTypeBuilder.h"

#include "AArchLinuxStructBuilder.h"
#include "Struct.h"
#include "Types.h"

#include "llvm/Support/Casting.h"

#include <cstddef>

using namespace std;

BuiltinType *AArch64LinuxTypeBuilder::getBuiltin(BuiltinKind bk) {
  assert(bk != BuiltinKind::FloatWth80Bits);

  return new BuiltinType(bk);
}

// 5.9   Composite Types
StructType *AArch64LinuxTypeBuilder::getStruct(std::span<Type *> members) {
  return ::getStruct(members, target);
}

bool AArch64LinuxTypeBuilder::isSupportedVectorLength(size_t bits) const {
  return (bits == 64) || (bits == 128);
}

bool AArch64LinuxTypeBuilder::isSupportedBitFieldType(const Type *type) const {
  return llvm::isa<BuiltinType>(type) || llvm::isa<PointerType>(type) ||
         llvm::isa<VectorType>(type);
}
