#include "AArchLinuxStructBuilder.h"

#include "TargetInfo.h"

#include "llvm/Support/Casting.h"

// 5.9   Composite Types (64-bit)
// 5.3   Composite Types (32-bit)
StructType *getStruct(std::span<Type *> members, TargetInfo *linux) {
  assert(!members.empty());

  size_t currentOffset = 0;
  size_t currentSize = 0;
  std::vector<std::variant<Type *, unsigned>> newMembers;

  // FIXME bitfields  5.3.4 Bit-fields (32) or 5.9.4   Bit-fields subdivision
  // (64)
  for (Type *member : members) {
    if (BitfieldType *bit = llvm::dyn_cast<BitfieldType>(member)) {
      bit->getFreeBits();
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
