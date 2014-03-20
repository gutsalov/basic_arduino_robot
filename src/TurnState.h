/*
 * TurnState.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#ifndef TURNSTATE_H_
#define TURNSTATE_H_

#include "State.h"

class TurnState: public State {
private:
	unsigned long enterTime;
public:
	TurnState(uint8_t stateId);
    virtual Event * enterState(uint8_t prevState);
    virtual uint8_t handleEvents(Event* event);
};

#endif /* TURNSTATE_H_ */
