#include "ForwardState.h"
#include "Platform.h"
#include "Event.h"

#define MINIMAL_DISTANCE 15

ForwardState::ForwardState(uint8_t id): State(id) {
}

Event * ForwardState::enterState(uint8_t prevState) {
	State::enterState(prevState);
}

uint8_t ForwardState::handleEvent(Event * eventQueue) {
	uint8_t newStateId = getId();
//	if (newStateId == getId() && !eventQueue->isEmpty()) {
//		Event * event = eventQueue->peek();
//		if (event->getType() == DistanceEvent) {
//			event = eventQueue->pop();
//			if (event->getData() < MINIMAL_DISTANCE) {
//				newStateId = StateTurnRight;
//			}
//			delete event;
//		}
//		else {
//			newStateId = State::handleEvents(eventQueue);
//		}
//	}
	return newStateId;
}
