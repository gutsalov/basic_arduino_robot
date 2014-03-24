/*
 * StateMachineTask.cpp
 *
 *  Created on: Mar 20, 2014
 *      Author: gutsan
 */

#include <assert.h>

#include "StateMachineTask.h"

StateMachineTask::StateMachineTask() {}

StateMachineTask::StateMachineTask(State ** states, uint8_t numberOfStates,
		uint8_t initialState): states(states), currentState(initialState) {
	for (State ** state = states; state < states + numberOfStates; state++) {
		assert((*state)->getId() == (state - states));
	}
	(*(states + initialState))->enterState(INVALID_STATE_ID);
}

Event * StateMachineTask::handleEvent(Event * event) {
	Event * newEvent = &Event::NO_EVENT;

	uint8_t newState = (*(states + currentState))->handleEvent(event);
	if (newState != currentState) {
		newEvent = (*(states + newState))->enterState(currentState);
		currentState = newState;
	}

	return newEvent;
}
