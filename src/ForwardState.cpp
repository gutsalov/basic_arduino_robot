#include "ForwardState.h"
#include "Platform.h"
#include "Event.h"

ForwardState::ForwardState(Platform * platform): State(StateForward, platform) {
}

void ForwardState::enterState(int prev) {
	platform->move(Forward);
}

StateId ForwardState::handleEvent(int event) {
	if (event == EVENT_STOP) {
		return StateIdle;
	}
	return StateForward;
}
