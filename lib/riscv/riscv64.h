#pragma once

#include "TargetInfo.h"

class RISCV64Linux : public TargetInfo {

  // LP64D
  DataModel getDataModel() override {
    return DataModel::LP64;
  }

  bool isBigEndian() override;

  bool isCharSigned() override {
    return false;
  }

  size_t getSizeOf(const Type *) override;
  size_t getAlignmentOf(const Type *) override;

  unsigned getNrOfBitsInLargestLockFreeInteger() const override;

  CallWithLayoutAndCode getCall(std::span<Type *> arguments) override;

  TypeBuilder *getTypeBuilder() override;
};
