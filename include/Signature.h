#pragma once

#include <span>
#include <vector>

class Type;

class Signature {
  Type *returnType;
  std::vector<Type *> arguments;

public:
  Signature(Type *returnType, std::span<Type *> arguments2)
      : returnType(returnType) {
    arguments.assign(arguments2.begin(), arguments2.end());
  }
};
