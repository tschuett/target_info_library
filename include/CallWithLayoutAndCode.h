#pragma once

#include "Actions.h"

#include <vector>

class CallWithLayoutAndCode {
  std::vector<std::pair<unsigned, Action *>> actions;

public:
  void addAction(unsigned idx, Action *action);
};
