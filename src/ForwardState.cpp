#include "ForwardState.h"
#include "Platform.h"
#include "Event.h"

#define MINIMAL_DISTANCE 10

ForwardState::ForwardState(Platform * platform): State(StateForward, platform) {
}

void ForwardState::enterState(int prev) {
	platform->move(Forward);
}

StateId ForwardState::handleEvents(QueueList<Event*> * eventQueue) {
	StateId newStateId = State::handleEvents(eventQueue);
	if (newStateId == getId() && !eventQueue->isEmpty()) {
		Event * event = eventQueue->pop();
		if (event->getType() == DistanceEvent && event->getData() < MINIMAL_DISTANCE) {
			newStateId = StateIdle;
		}
		delete event;
	}
	return newStateId;
}
