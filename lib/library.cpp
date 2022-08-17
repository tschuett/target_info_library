#include "AArch64Linux.h"
#include "TargetInfo.h"

using namespace std;

unique_ptr<TargetInfo> getTargetInfo(llvm::Triple triple,
                                     span<string> cpuFeatureFlags) {

  //printf("triple: %s\n", triple.str().c_str());

//  if (triple.getArch() == llvm::Triple::ArchType::aarch64 and
//      triple.getOS() == llvm::Triple::OSType::Linux)
    return make_unique<AArch64Linux>();
    //printf("no target found: failed\n");
}
