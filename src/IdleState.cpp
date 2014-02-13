#include "IdleState.h"
#include "Event.h"

IdleState::IdleState(Platform * platform): State(StateIdle, platform) {
}

void IdleState::enterState(int prev) {
	platform->stop();
}

StateId IdleState::handleEvent(Event * event) {
	if (event->getType() == ControlEvent) {
		switch (event->getData()) {
			case EVENT_FORWARD:
				return StateForward;
				break;
			default:
				return getId();
		};
	}
	return getId();
}
