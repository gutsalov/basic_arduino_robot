#ifndef _State_h_
#define _State_h_

#include <Arduino.h>
#include <QueueList.h>
#include "Platform.h"
#include "Event.h"

enum StateId {
  StateIdle,
  StateForward,
  StateTurnLeft,
  StateTurnRight,
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
    virtual StateId handleEvents(QueueList<Event*> * eventQueue);
};

#endif
