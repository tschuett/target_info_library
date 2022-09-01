#include "AArch32Linux.h"
#include "AArch64Linux.h"
#include "TargetInfo.h"
#include "X8664Linux.h"

#include "riscv/riscv64.h"
#include "riscv/riscv32.h"

#include <memory>

using namespace std;

unique_ptr<TargetInfo> getTargetInfo(llvm::Triple triple,
                                     span<string> cpuFeatureFlags) {

  printf("triple: %s\n", triple.str().c_str());

  if (triple.isAArch64())
    return make_unique<AArch64Linux>();
  if (triple.isARM() && triple.isArch32Bit())
    return make_unique<AArch32Linux>();

  if (triple.isX86() && triple.isArch64Bit())
    return make_unique<X8664Linux>();

  if (triple.isRISCV() && triple.isArch64Bit())
    return make_unique<RISCV64Linux>();

  if (triple.isRISCV() && triple.isArch32Bit())
    return make_unique<RISCV32Linux>();

  printf("no target found: failed\n");
  assert(false);
}
