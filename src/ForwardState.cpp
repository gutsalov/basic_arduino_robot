#include "ForwardState.h"
#include "Platform.h"
#include "Event.h"

#define MINIMAL_DISTANCE 15

ForwardState::ForwardState(Platform * platform): State(StateForward, platform) {
}

void ForwardState::enterState(StateId prevState) {
	State::enterState(prevState);
//	platform->move(Forward);
}

StateId ForwardState::handleEvents(QueueList<Event*> * eventQueue) {
	StateId newStateId = getId();
	if (newStateId == getId() && !eventQueue->isEmpty()) {
		Event * event = eventQueue->peek();
		if (event->getType() == DistanceEvent) {
			event = eventQueue->pop();
			if (event->getData() < MINIMAL_DISTANCE) {
				newStateId = StateTurnRight;
			}
			delete event;
		}
		else {
			newStateId = State::handleEvents(eventQueue);
		}
	}
	return newStateId;
}
