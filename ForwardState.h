#ifndef _ForwardState_h_
#define _ForwardState_h_

#include <Arduino.h>
#include "State.h"

class ForwardState: public State {
  public:
    ForwardState(Platform * platform);
    virtual void enterState(int prevState);
    virtual StateId handleEvent(int event);
};

#endif
