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
	TurnState(StateId stateId, Platform * platform);
    virtual void enterState(StateId prevState);
    virtual StateId handleEvents(QueueList<Event*> * eventQueue);
};

#endif /* TURNSTATE_H_ */
