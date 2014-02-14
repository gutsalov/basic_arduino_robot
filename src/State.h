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
  NumberOfStates,
  Invalid
};


class State {
  private:
    StateId id;
    StateId previous;
  protected:
    Platform * platform;
    StateId getPrevStateId(void);
  public:
    State(StateId stateId, Platform * platform);
    StateId getId(void);
    virtual void enterState(StateId prev);
    virtual StateId handleEvents(QueueList<Event*> * eventQueue);
};

#endif
