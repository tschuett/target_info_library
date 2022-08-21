#pragma once

#include "TargetInfo.h"

class AArch32Linux : public TargetInfo {
public:
  AArch32Linux() = default;

  virtual ~AArch32Linux() = default;

  DataModel getDataModel() override { return DataModel::ILP32; };

  bool isBigEndian() override;

  bool isCharSigned() override;

  size_t getSizeOf(const Type *) override;
  size_t getAlignmentOf(const Type *) override;
  //bool isSupported(const Type *) override;

  unsigned getNrOfBitsInLargestLockFreeInteger() const override;

  CallWithLayoutAndCode getCall(/*const FunctionType *signature*,*/
                                std::span<Type *> arguments) override;

  TypeBuilder *getTypeBuilder() override;


private:
  //  size_t getMaxAlignment(std::span<Type *> members);
  bool isHomogeneousAggregate(const Type *);
  bool isDynamicallySizedType(Type *type);
  bool isIntegralFundamentDataType(Type *arg);
  //  bool isHomogeneousFloatingPointAggregate(const Type *);
  //  bool isHomogeneousShortVectorAggregate(const Type *);
  //
  //  bool isPureScalabeType(const Type *);
  //  bool isFloatOrShortVector(const Type *);
  //  bool isShortVector(const Type *);
  //  bool isHalfOrSingle(const Type *);
  //  bool isFloat(const Type *);
};
