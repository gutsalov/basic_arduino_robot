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
      Right,
      Left
    };
    Platform(int leftId, int rightId);
    void move(Direction);
};

#endif
