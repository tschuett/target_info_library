#pragma once

#include "TargetInfo.h"

class AArch64Linux : public TargetInfo {
public:
  AArch64Linux() = default;
  virtual ~AArch64Linux() = default;

  bool isBigEndian() override;

  bool isCharSigned() override;

  size_t getSizeOf(const Type *) override;
  size_t getAlignmentOf(const Type *) override;
  bool isSupported(const Type *) override;

  CallWithLayoutAndCode getCall(const FunctionType *signature,
                                std::span<Type *> arguments) override;

private:
  size_t getMaxAlignment(std::span<Type*> members);
  size_t fitIntoAlignment(std::span<Type *> members);
  bool isHomogeneousAggregate(Type *);
  bool isHomogeneousFloatingPointAggregate(Type *);
  bool isHomogeneousShortVectorAggregate(Type *);

  bool isPureScalabeType(Type *);
};
