#include "AArch64LinuxTypeBuilder.h"
#include "Types.h"

// 5.9   Composite Types
StructType *AArch64LinuxTypeBuilder::getStruct(std::span<Type *> members) {
  assert(false);
  // FIXME
}

VectorType *AArch64LinuxTypeBuilder::getVector(size_t bits) {
  return new VectorType(bits);
}
