#ifndef _IdleState_h_
#define _IdleState_h_

#include <Arduino.h>
#include "State.h"

class IdleState: public State {
  public:
    IdleState(uint8_t id);
    virtual Event * enterState(uint8_t prevState);
};

#endif
