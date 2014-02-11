#include <AFMotor.h>

#include "Platform.h"

#define MOTOR_ID_LEFT  1
#define MOTOR_ID_RIGHT 2

Platform platform(MOTOR_ID_LEFT, MOTOR_ID_RIGHT);
 
void setup() {
}

void loop() {
  platform.move(Platform::Forward);
  delay(1000);
  platform.move(Platform::Backward);
  delay(1000);
  platform.move(Platform::Left);
  delay(1000);
  platform.move(Platform::Right);
  delay(1000);
  platform.stop();
  delay(1000);
}
