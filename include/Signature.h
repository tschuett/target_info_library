#pragma once

#include <vector>

class Type;

class Signature {
  Type *returnType;
  std::vector<Type *> arguments;
};

