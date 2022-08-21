#include "X86LinuxTypeBuilder.h"

#include "Types.h"

#include "llvm/Support/Casting.h"

#include <vector>

using namespace std;

// Aggregates and Unions
StructType *X86LinuxTypeBuilder::getStruct(std::span<Type *> members) {
  assert(!members.empty());

  size_t currentOffset = 0;
  size_t currentSize = 0;
  std::vector<std::variant<Type *, unsigned>> newMembers;

  for (unsigned i = 0; i < members.size(); ++i) {
    size_t align = target->getAlignmentOf(members[i]);
    size_t size = target->getSizeOf(members[i]);
    size_t swizzle = currentOffset % align;
    if (swizzle == 0) {
      newMembers.push_back(members[i]);
      currentOffset += size;
      currentSize += size;
    } else {
      newMembers.push_back((unsigned)(align - swizzle)); // padding
      newMembers.push_back(members[i]);                  // value
      currentOffset += size;
      currentSize += size;
    }
  }

  return new StructType(newMembers, currentSize,
                        target->getAlignmentOf(members[0]));
}

bool X86LinuxTypeBuilder::isSupportedVectorLength(size_t bits) const {
  return (bits == 64) || (bits == 128) || (bits == 256) || (bits == 512);
}

bool X86LinuxTypeBuilder::isSupportedBitFieldType(const Type *type) const {
  if (auto built = llvm::dyn_cast<BuiltinType>(type)) {
    switch (built->getKind()) {
    case BuiltinKind::Byte:
    case BuiltinKind::Short:
    case BuiltinKind::Word:
    case BuiltinKind::DoubleWord:
      return true;
    default:
      return false;
    }
  }
  return false;
}
