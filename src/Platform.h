#ifndef _Platform_h_
#define _Platform_h_

#include <Arduino.h>
#include <AFMotor.h>
#include <PID_v1.h>

#include "Event.h"
#include "Task.h"

#define MAX_CHASSIS_SPEED 80
#define MIN_CHASSIS_SPEED 10

class Platform: public Task {
  private:
	class Motor {
		public:
			Motor(uint8_t motorId);
			void forward(double targetSpeed);
			void stop();
			void backward(void);
			void handleCurrentWheelSpeed(double currentSpeed);
			void adjustMotorSpeedIfNeeded(void);
		private:
			AF_DCMotor motorWrapper;
			PID motorPID;
			double motorSpeed;
			double currentWheelSpeed;
			double targetWheelSpeed;
	};
    Motor leftMotor;
    Motor rightMotor;
  public:
    Platform(uint8_t leftId, uint8_t rightId);
    Event * handleEvent(Event * event);
  private:
    void handleForward(double speed);
    void handleStop();
    void handleSpeed(Motor * motor, double currentSpeed);
    void adjustMotorSpeedIfNeeded(void);
};

#endif
