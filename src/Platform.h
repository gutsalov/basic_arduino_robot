#ifndef _Platform_h_
#define _Platform_h_

#include <Arduino.h>
#include <AFMotor.h>

#include "Event.h"
#include "Task.h"

class Platform: public Task {
  private:
    AF_DCMotor leftMotor;
    AF_DCMotor rightMotor;
    uint8_t leftMotorSpeed;
    uint8_t rightMotorSpeed;
    int chassisSpeed;
  public:
    Platform(uint8_t leftId, uint8_t rightId);
    Event * handleEvent(Event * event);
  private:
    void handleForward(int speed);
};

#endif
