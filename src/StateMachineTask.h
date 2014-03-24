/*
 * StateMachineTask.h
 *
 *  Created on: Mar 20, 2014
 *      Author: gutsan
 */

#ifndef STATEMACHINETASK_H_
#define STATEMACHINETASK_H_

#include "State.h"

class StateMachineTask: public Task {
private:
	State ** states;
	uint8_t currentState;
public:
	StateMachineTask();
	StateMachineTask(State ** states, uint8_t numberOfStates, uint8_t initialState);
	virtual Event * handleEvent(Event * event);
};

#endif /* STATEMACHINETASK_H_ */
