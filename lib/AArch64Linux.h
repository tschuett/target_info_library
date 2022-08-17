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

  TypeBuilder *getTypeBuilder() override;

private:
  size_t getMaxAlignment(std::span<Type *> members);
  size_t fitIntoAlignment(std::span<Type *> members);
  bool isHomogeneousAggregate(const Type *);
  bool isHomogeneousFloatingPointAggregate(const Type *);
  bool isHomogeneousShortVectorAggregate(const Type *);

  bool isPureScalabeType(const Type *);
  bool isFloatOrShortVector(const Type *);
  bool isShortVector(const Type *);
  bool isHalfOrSingle(const Type *);
  bool isFloat(const Type *);
};
