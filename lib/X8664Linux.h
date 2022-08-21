#pragma once

#include "X86LinuxTypeBuilder.h"
#include "TargetInfo.h"
#include "X86LinuxTypeBuilder.h"

class X8664Linux : public TargetInfo {
  X86LinuxTypeBuilder typeBuilder;

public:
  X8664Linux() : typeBuilder(X86LinuxTypeBuilder(this)) {}

  DataModel getDataModel() override { return DataModel::LP64; };

  bool isBigEndian() override;

  bool isCharSigned() override;

  size_t getSizeOf(const Type *) override;
  size_t getAlignmentOf(const Type *) override;
  // bool isSupported(const Type *) override;

  unsigned getNrOfBitsInLargestLockFreeInteger() const override;

  CallWithLayoutAndCode getCall(/*const FunctionType *signature,*/
                                std::span<Type *> arguments) override;

  TypeBuilder *getTypeBuilder() override;

private:
  enum class ClassificationKind {
    Integer,
    SSE,
    SSEUp,
    X87,
    X87Up,
    ComplexX87,
    NoClass,
    Memory
  };

  ClassificationKind getClassification(Type *arg);
};
