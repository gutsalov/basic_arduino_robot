/*
 * SpeedMeter.cpp
 */

#include "SpeedMeter.h"

#include <Arduino.h>

#define NUMBER_OF_HOLES_PER_CIRCLE  20
#define CIRCLE_PATH_LENGTH_CM  		22

SpeedMeter::SpeedMeter(uint8_t pin, EventType eventType): eventType(eventType), pin(pin) {
	pinMode(pin, INPUT);
	state = digitalRead(pin);
	stateTime = millis();
	count = 0;
}

Event * SpeedMeter::handleEvent(Event * event) {
	Event * resultEvent = &Event::NO_EVENT;
	int newState = digitalRead(pin);
	if (state ^ newState) {
		state = newState;
		if (state) {
			count++;
			if (NUMBER_OF_HOLES_PER_CIRCLE == count) {
				long newEventTime = millis();
				long oneCircleTime = newEventTime - stateTime;
				int speed = CIRCLE_PATH_LENGTH_CM * 1000 / oneCircleTime;
				resultEvent = new Event(eventType, speed);
				stateTime = newEventTime;
				count = 0;
			}
		}
	}
	return resultEvent;
}
