/*
 * TurnState.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "TurnState.h"

#define AUTO_EXIT_TIMEOUT 1000

TurnState::TurnState(StateId stateId, Platform * platform): State(stateId, platform) {}

void TurnState::enterState(StateId prevState) {
	State::enterState(prevState);
	platform->move(getId() == StateTurnLeft ? Left : Right);
	enterTime = millis();
}

StateId TurnState::handleEvents(QueueList<Event *> * eventQueue) {
	StateId newState = State::handleEvents(eventQueue);
	if (newState == getId() && !eventQueue->isEmpty()) {
		Event * event = eventQueue->pop();
		if (event->getType() == TimerEvent && millis() >= enterTime + AUTO_EXIT_TIMEOUT) {
			newState = getPrevStateId();
		}
		delete event;
	}
	return newState;
}

