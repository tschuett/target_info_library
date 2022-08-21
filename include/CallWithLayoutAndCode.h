#pragma once

#include "Actions.h"

#include <vector>

class CallWithLayoutAndCode {
  std::vector<std::pair<unsigned, Action *>> actions;
  std::vector<Action *> returnActions;

public:
  void addAction(unsigned idx, Action *action);

  void addReturnAction(Action *action);

  std::vector<Action *> getActionsForArguments(unsigned idx);

  std::vector<Action *> getActionForReturn();
};
