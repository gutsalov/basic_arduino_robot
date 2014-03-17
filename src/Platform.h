#ifndef _Platform_h_
#define _Platform_h_

#include <Arduino.h>
#include <AFMotor.h>

#include "Event.h"
#include "Task.h"

#define MAX_CHASSIS_SPEED 50

class Platform: public Task {
  private:
	class Motor {
		public:
			Motor(uint8_t motorId): motorWrapper(motorId), motorSpeed(0) {};
			void forward(uint8_t wheelSpeed);
			uint8_t adjustSpeed(uint8_t currentSpeed, uint8_t targetSpeed);
		private:
			AF_DCMotor motorWrapper;
			uint8_t motorSpeed;
	};
    Motor leftMotor;
    Motor rightMotor;
    uint8_t wheelSpeed;
  public:
    Platform(uint8_t leftId, uint8_t rightId);
    Event * handleEvent(Event * event);
    void handleSpeed(Motor * motor, int speed);
  private:
    void handleForward(int speed);
    void handleSpeed(int speed, AF_DCMotor * );
};

#endif
