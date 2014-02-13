#include "ForwardState.h"
#include "Platform.h"
#include "Event.h"

ForwardState::ForwardState(Platform * platform): State(StateForward, platform) {
}

void ForwardState::enterState(int prev) {
	platform->move(Forward);
}

StateId ForwardState::handleEvent(Event * event) {
	if (event->getType() == ControlEvent) {
		switch (event->getData()) {
			case EVENT_STOP:
				return StateIdle;
				break;
			default:
				return getId();
		};
	}
	return getId();
}
