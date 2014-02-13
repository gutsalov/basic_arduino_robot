#include "State.h"

State::State(StateId stateId, Platform * platf): id(stateId), platform(platf) {
}

StateId State::getId(void) {
  return id;
}

