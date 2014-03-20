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
	return &Event::NO_EVENT;
}

void Platform::handleForward(int speed) {
	wheelSpeed = speed;
	leftMotor.forward(wheelSpeed);
	rightMotor.forward(wheelSpeed);
}

void Platform::handleSpeed(Motor * motor, int speed) {
	wheelSpeed = motor->adjustSpeed(speed, wheelSpeed);
}

void Platform::Motor::forward(uint8_t speed) {
//	motorSpeed = INITIAL_MOTOR_SPEED;
	motorSpeed = MAX_MOTOR_SPEED;
	motorWrapper.setSpeed(motorSpeed);
	motorWrapper.run(FORWARD);
}

uint8_t Platform::Motor::adjustSpeed(uint8_t currentSpeed, uint8_t targetSpeed) {
	if (currentSpeed == 0) {
		currentSpeed = 1;
	}

	uint16_t newMotorSpeed = targetSpeed * motorSpeed / currentSpeed;

	Serial.print(" - ");
	Serial.print(currentSpeed);
	Serial.print(" > ");
	Serial.print(targetSpeed);
	Serial.print(" = ");
	Serial.print(motorSpeed);
	Serial.print(" > ");
	Serial.println(newMotorSpeed);

	if (newMotorSpeed < MIN_MOTOR_SPEED ) {
		motorSpeed = MIN_MOTOR_SPEED;
	}
	else {
		motorSpeed = newMotorSpeed;
	}
	motorWrapper.setSpeed(motorSpeed);
	return targetSpeed;
}
