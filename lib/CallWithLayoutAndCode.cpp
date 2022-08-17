#include "CallWithLayoutAndCode.h"

using namespace std;

void CallWithLayoutAndCode::addAction(unsigned idx, Action *action) {
  actions.push_back(make_pair(idx, action));
}
