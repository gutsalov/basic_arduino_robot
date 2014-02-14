#ifndef _ForwardState_h_
#define _ForwardState_h_

#include <Arduino.h>
#include "State.h"

class ForwardState: public State {
  public:
    ForwardState(Platform * platform);
    virtual void enterState(StateId prevState);
    virtual StateId handleEvents(QueueList<Event*> * eventQueue);
};

#endif
