#include "ForwardState.h"
#include "Platform.h"

ForwardState::ForwardState(Platform * platform): State(StateForward, platform) {
}

void ForwardState::enterState(int prev) {
  platform->move(Forward);
}

StateId ForwardState::handleEvent(int event) {
  return StateIdle;
}


