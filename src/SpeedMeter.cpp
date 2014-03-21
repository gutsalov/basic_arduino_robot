/*
 * SpeedMeter.cpp
 */

#include "SpeedMeter.h"

#include <Arduino.h>

#define SPEED_FACTOR				(double)1100
#define MAX_SAMPLE_VALUE			100

SpeedMeter::SpeedMeter(uint8_t pin, EventType eventType): eventType(eventType) {
	pinMode(pin, INPUT);
	PCintPort::attachInterrupt(pin, this, RISING);
	currentChangeTime = 0;
	previousChangeTime = 0;
	lastChangeTimestamp = 0;
}

void SpeedMeter::pinChanged() {
	previousChangeTime = currentChangeTime;
	currentChangeTime = millis();
}

Event * SpeedMeter::handleEvent(Event * event) {
	Event * resultEvent = &Event::NO_EVENT;
	/* Disable interrupts and check the last pin change */
	double currentSample = 0;
	cli();
	if (lastChangeTimestamp != currentChangeTime) {
		lastChangeTimestamp = currentChangeTime;
		currentSample = currentChangeTime - previousChangeTime;
	}
	sei();
	if (currentSample != 0 && currentSample < MAX_SAMPLE_VALUE) {
		double speed = SPEED_FACTOR / currentSample;
		resultEvent = new Event(eventType, speed);
	}

	return resultEvent;
}
