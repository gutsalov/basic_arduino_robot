#ifndef _State_h_
#define _State_h_

#include <Arduino.h>
#include "Platform.h"
#include "Event.h"

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
    virtual StateId handleEvent(Event * event) = 0;
};

#endif
