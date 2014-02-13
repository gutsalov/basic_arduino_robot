#include "IdleState.h"
#include "Event.h"

IdleState::IdleState(Platform * platform): State(StateIdle, platform) {
}

void IdleState::enterState(int prev) {
	platform->stop();
}
