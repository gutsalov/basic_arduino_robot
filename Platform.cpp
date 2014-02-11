#include "Platform.h"

struct MotorCommand {
  uint8_t command;
  uint8_t speed;
};  

MotorCommand commands[][NumberOfMotors] = {
  {{FORWARD, 255},  {FORWARD, 255}},  /* Forward */
  {{BACKWARD, 255}, {BACKWARD, 255}}, /* Backward */
  {{BACKWARD, 255}, {FORWARD, 255}},  /* Left */
  {{FORWARD, 255},  {BACKWARD, 255}}, /* Right */
};

Platform::Platform(uint8_t leftId, uint8_t rightId): motors{AF_DCMotor(leftId), AF_DCMotor(rightId)} {
}

void Platform::move(Direction dir) {
  MotorCommand * cmd;
  AF_DCMotor * motor;
  for (cmd = commands[dir], motor = motors; motor < motors + NumberOfMotors; cmd++, motor++) {
    motor->setSpeed(cmd->speed);
    motor->run(cmd->command);
  }
}

void Platform::stop(void) {
  AF_DCMotor * motor;
  for (motor = motors; motor < motors + NumberOfMotors; motor++) {
    motor->setSpeed(0);
    motor->run(BRAKE);
  }
}
