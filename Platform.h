#ifndef _Platform_h_
#define _Platform_h_

#include <Arduino.h>
#include <AFMotor.h>

class Platform {
  private:
    AF_DCMotor ** motors;
  public:
    enum Direction {
      Forward,
      Backward,
      Left,
      Right
    };
    Platform(uint8_t leftId, uint8_t rightId);
    void move(Direction);
    void stop();
};

#endif
