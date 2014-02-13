#ifndef _State_h_
#define _State_h_

#include <Arduino.h>
#include "Platform.h"


enum StateId {
  StateIdle,
  StateForward,
  NumberOfStates
};


class State {
  private:
    StateId id;
  protected:
    Platform * platform;
  public:
    State(StateId stateId, Platform * platform);
    StateId getId(void);
    virtual void enterState(int prev) = 0;
    virtual StateId handleEvent(int event) = 0;
};

#endif