#pragma once

#include "CallWithLayoutAndCode.h"

#include "llvm/ADT/Triple.h"

#include <memory>
#include <span>
#include <string>

class Type;
class FunctionType;
class TypeBuilder;

enum class DataModel {
  LP64,  // Unix
  ILP32, // 32-bit
  LL64   // Windows and IA-64
};

class TargetInfo {
public:
  virtual ~TargetInfo() = default;

  virtual DataModel getDataModel() = 0;

  virtual bool isBigEndian() = 0;

  virtual bool isCharSigned() = 0;

  virtual size_t getSizeOf(const Type *) = 0;
  virtual size_t getAlignmentOf(const Type *) = 0;
  //virtual bool isSupported(const Type *) = 0;

  virtual unsigned getNrOfBitsInLargestLockFreeInteger() const = 0;

  virtual CallWithLayoutAndCode getCall(std::span<Type *> arguments) = 0;

  virtual TypeBuilder *getTypeBuilder() = 0;
};

extern std::unique_ptr<TargetInfo>
getTargetInfo(llvm::Triple triple, std::span<std::string> cpuFeatureFlags);
