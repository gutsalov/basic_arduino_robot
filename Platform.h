#ifndef _Platform_h_
#define _Platform_h_

#include <Arduino.h>
#include <AFMotor.h>

enum Motors {
  LeftMotor,
  RightMotor,
  NumberOfMotors
};

class Platform {
  private:
    AF_DCMotor motors[NumberOfMotors];
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
