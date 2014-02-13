#include "ForwardState.h"
#include "Platform.h"
#include "Event.h"

ForwardState::ForwardState(Platform * platform): State(StateForward, platform) {
}

void ForwardState::enterState(int prev) {
	platform->move(Forward);
}
