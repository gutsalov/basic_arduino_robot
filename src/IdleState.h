#ifndef _IdleState_h_
#define _IdleState_h_

#include <Arduino.h>
#include "State.h"

class IdleState: public State {
  public:
    IdleState(Platform * platform);
    virtual void enterState(StateId prevState);
};

#endif
