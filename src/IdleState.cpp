#include "IdleState.h"
#include "Event.h"

IdleState::IdleState(Platform * platform): State(StateIdle, platform) {
}

void IdleState::enterState(StateId prevState) {
	State::enterState(prevState);
	platform->stop();
}
