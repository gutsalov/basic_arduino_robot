#ifndef _ForwardState_h_
#define _ForwardState_h_

#include <Arduino.h>
#include "State.h"

class ForwardState: public State {
  public:
    ForwardState(uint8_t id);
    virtual Event * enterState(uint8_t prevState);
    virtual uint8_t handleEvent(Event * event);
};

#endif
