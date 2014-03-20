#ifndef _State_h_
#define _State_h_

#include <Arduino.h>
#include <QueueList.h>
#include "Platform.h"
#include "Event.h"

#define INVALID_STATE_ID	255

class State {
  private:
    uint8_t id;
    uint8_t previous;
  protected:
    uint8_t getPrevStateId(void);
  public:
    State(uint8_t stateId);
    uint8_t getId(void);
    virtual Event * enterState(uint8_t prev);
    virtual uint8_t handleEvent(Event* event);
};

#endif
