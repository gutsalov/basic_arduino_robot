/*
 * TurnState.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "TurnState.h"

#define AUTO_EXIT_TIMEOUT 300

TurnState::TurnState(StateId stateId, Platform * platform): State(stateId, platform) {}

void TurnState::enterState(StateId prevState) {
	State::enterState(prevState);
	platform->move(getId() == StateTurnLeft ? Left : Right);
	enterTime = millis();
}

StateId TurnState::handleEvents(QueueList<Event *> * eventQueue) {
	StateId newState = getId();
	if (newState == getId() && !eventQueue->isEmpty()) {
		Event * event = eventQueue->peek();
		if (event->getType() == TimerEvent) {
			Event * event = eventQueue->pop();
			if (millis() >= enterTime + AUTO_EXIT_TIMEOUT) {
				newState = getPrevStateId();
			}
			delete event;
		}
		else {
			State::handleEvents(eventQueue);
		}
	}
	return newState;
}

