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
public:
	TurnState(StateId stateId, Platform * platform);
    virtual void enterState(int prev);
};

#endif /* TURNSTATE_H_ */
