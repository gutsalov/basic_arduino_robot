#include "IdleState.h"
#include "Event.h"

IdleState::IdleState(uint8_t id): State(id) {
}

Event * IdleState::enterState(uint8_t prevState) {
	State::enterState(prevState);
//	platform->stop();
	return &Event::NO_EVENT;
}
