#pragma once

#include "Struct.h"
#include "TargetInfo.h"
#include "Types.h"

#include <span>

StructType *getStruct(std::span<Type *> members, TargetInfo *linux);
