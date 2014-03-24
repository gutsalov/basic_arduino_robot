#include "Platform.h"

#define MAX_MOTOR_SPEED   	255
#define MIN_MOTOR_SPEED   	120
#define INITIAL_MOTOR_SPEED	200

Platform::Platform(uint8_t leftId, uint8_t rightId): leftMotor(leftId), rightMotor(rightId) {
}

Event * Platform::handleEvent(Event * event) {
    switch (event->getType()) {
    	case ChassisForwardEvent:
    		handleForward(event->getData());
    		break;
    	case SpeedLeftEvent:
    		handleSpeed(&leftMotor, event->getData());
    		break;
    	case SpeedRightEvent:
    		handleSpeed(&rightMotor, event->getData());
    		break;

    	default:
    		;
    }
    adjustMotorSpeedIfNeeded();
	return &Event::NO_EVENT;
}

void Platform::adjustMotorSpeedIfNeeded(void) {
	leftMotor.adjustMotorSpeedIfNeeded();
	rightMotor.adjustMotorSpeedIfNeeded();
}

void Platform::handleForward(double speed) {
	leftMotor.forward(speed);
	rightMotor.forward(speed);
}

void Platform::handleSpeed(Motor * motor, double speed) {
	motor->handleCurrentWheelSpeed(speed);
}

Platform::Motor::Motor(uint8_t id): motorWrapper(id),
		motorPID(&currentWheelSpeed, &motorSpeed, &targetWheelSpeed, 4, 0.2, 0.1, DIRECT) {
	motorSpeed = 0;
	currentWheelSpeed = 0;
	targetWheelSpeed = 0;
	motorPID.SetMode(AUTOMATIC);
	motorPID.SetSampleTime(100);
	motorPID.SetOutputLimits(MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
}


void Platform::Motor::forward(double targetSpeed) {
	targetWheelSpeed = targetSpeed;
	motorWrapper.run(FORWARD);
	handleCurrentWheelSpeed(0);
}

void Platform::Motor::handleCurrentWheelSpeed(double currentSpeed) {
	currentWheelSpeed = currentSpeed;
}

void Platform::Motor::adjustMotorSpeedIfNeeded() {
	double prevSpeed = motorSpeed;
	motorPID.Compute();
	if (prevSpeed != motorSpeed) {
		motorWrapper.setSpeed(motorSpeed);
	}
}
