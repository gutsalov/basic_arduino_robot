#include "Platform.h"

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
#define NUMBER_OF_MOTORS MOTOR_RIGHT + 1

Platform::Platform(int leftId, int rightId) {
  motors = new AF_DCMotor*[NUMBER_OF_MOTORS];
  motors[MOTOR_LEFT] = new AF_DCMotor(leftId);
  motors[MOTOR_RIGHT] = new AF_DCMotor(rightId);
}

void Platform::move(Direction dir) {
}
