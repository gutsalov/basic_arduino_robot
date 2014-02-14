#include "State.h"

State::State(StateId stateId, Platform * platf): id(stateId), platform(platf) {
	previous = Invalid;
}

StateId State::getId(void) {
  return id;
}
StateId State::getPrevStateId(void) {
	return previous;
}

void State::enterState(StateId prev) {
	previous = prev;
}

StateId State::handleEvents(QueueList<Event*> * eventQueue) {
	if (eventQueue->isEmpty()) {
		return getId();
	}
	Event * event = eventQueue->pop();
	StateId state = getId();
	if (event->getType() == ControlEvent) {
		switch (event->getData()) {
			case EVENT_STOP:
				state = StateIdle;
				break;
			case EVENT_FORWARD:
				state = StateForward;
				break;
			case EVENT_LEFT:
				state = StateTurnLeft;
				break;
			case EVENT_RIGHT:
				state = StateTurnRight;
				break;
			default:;
		};
	}
	delete event;
	return state;
}
