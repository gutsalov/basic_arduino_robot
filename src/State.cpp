#include "State.h"

State::State(uint8_t stateId): id(stateId) {
	previous = INVALID_STATE_ID;
}

uint8_t State::getId(void) {
  return id;
}
uint8_t State::getPrevStateId(void) {
	return previous;
}

Event * State::enterState(uint8_t prev) {
	previous = prev;
	return &Event::NO_EVENT;
}

uint8_t State::handleEvent(Event* event) {
	return getId();
}
