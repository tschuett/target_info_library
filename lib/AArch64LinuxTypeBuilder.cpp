#include "AArch64LinuxTypeBuilder.h"

#include "Struct.h"
#include "Types.h"

#include "llvm/Support/Casting.h"

#include <cstddef>

using namespace std;

// 5.9   Composite Types
StructType *AArch64LinuxTypeBuilder::getStruct(std::span<Type *> members) {
  assert(!members.empty());

  size_t currentOffset = 0;
  size_t currentSize = 0;
  std::vector<std::variant<Type *, unsigned>> newMembers;

  // FIXME bitfields  5.3.4 Bit-fields
  for (Type *member : members) {
    if (BitfieldType *bit = llvm::dyn_cast<BitfieldType>(member)) {
      // FIXME
    } else {
      size_t align = linux->getAlignmentOf(member);
      size_t size = linux->getSizeOf(member);
      size_t swizzle = currentOffset % align;
      if (swizzle == 0) {
        newMembers.push_back(member);
        currentOffset += size;
        currentSize += size;
      } else {
        newMembers.push_back((unsigned)(align - swizzle)); // padding
        newMembers.push_back(member);                      // value
        currentOffset += size;
        currentSize += size;
      }
    }
  }

  return new StructType(newMembers, currentSize,
                        linux->getAlignmentOf(members[0]));
}

VectorType *AArch64LinuxTypeBuilder::getVector(size_t bits) {
  assert((bits == 64) || (bits == 128));

  return new VectorType(bits);
}

UnionType *AArch64LinuxTypeBuilder::getUnion(std::span<Type *> members) {
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

BitfieldType *AArch64LinuxTypeBuilder::getBitfield(Type *type, size_t bits) {
  assert(isFundamentalDataType(type));

  size_t sizeInBytes = linux->getSizeOf(type);
  return new BitfieldType(type, sizeInBytes, bits);
}

// size_t AArch64Linux::fitIntoAlignment(std::span<Type *> members) {
//   size_t maxAlignment = getMaxAlignment(members);
//   size_t sumSize = 0;
//   for (Type *mem : members) {
//     sumSize += getSizeOf(mem);
//   }
//
//   ldiv_t divResult = std::ldiv(sumSize, maxAlignment);
//   if (divResult.rem == 0) {
//     return sumSize;
//   } else {
//     return sumSize + divResult.rem * maxAlignment;
//   }
// }
//

bool AArch64LinuxTypeBuilder::isFundamentalDataType(const Type *type) const {
  return llvm::isa<BuiltinType>(type) || llvm::isa<PointerType>(type) ||
         llvm::isa<VectorType>(type);
}
