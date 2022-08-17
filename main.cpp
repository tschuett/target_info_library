#include "TargetInfo.h"

#include "llvm/ADT/Triple.h"

#include <vector>

int main(int argc, char **argv) {

  llvm::Triple triple = llvm::Triple("aarch64-linux-gnu");

  std::vector<std::string> cpuFeatureFlags;

  std::unique_ptr<TargetInfo> targetInfo =
      getTargetInfo(triple, cpuFeatureFlags);

  TypeBuilder *builder = targetInfo->getTypeBuilder();

  return 0;
}
