#pragma once

#include "TargetInfo.h"

class RISCV32Linux : public TargetInfo {
    // ILP32D
  DataModel getDataModel() override {
    return DataModel::ILP32;
  }

  bool isBigEndian() override;

  bool isCharSigned() override;

  size_t getSizeOf(const Type *) override;
  size_t getAlignmentOf(const Type *) override;

  unsigned getNrOfBitsInLargestLockFreeInteger() const override;

  CallWithLayoutAndCode getCall(std::span<Type *> arguments) override;

  TypeBuilder *getTypeBuilder() override;
};
