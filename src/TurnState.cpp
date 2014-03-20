/*
 * TurnState.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "TurnState.h"

#define AUTO_EXIT_TIMEOUT 100

TurnState::TurnState(uint8_t stateId): State(stateId) {}

Event * TurnState::enterState(uint8_t prevState) {
	State::enterState(prevState);
//	platform->move(getId() == StateTurnLeft ? Left : Right);
	enterTime = millis();
	return &Event::NO_EVENT;
}

uint8_t TurnState::handleEvents(Event * event) {
	uint8_t newState = getId();
//	if (newState == getId() && !eventQueue->isEmpty()) {
//		Event * event = eventQueue->peek();
//		if (event->getType() == TimerEvent) {
//			Event * event = eventQueue->pop();
//			if (millis() >= enterTime + AUTO_EXIT_TIMEOUT) {
//				newState = getPrevStateId();
//			}
//			delete event;
//		}
//		else {
//			State::handleEvents(eventQueue);
//		}
//	}
	return newState;
}

