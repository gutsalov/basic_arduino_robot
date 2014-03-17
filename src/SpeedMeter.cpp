/*
 * SpeedMeter.cpp
 */

#include "SpeedMeter.h"

#include <Arduino.h>

#define NUMBER_OF_HOLES_PER_CIRCLE  20
#define CIRCLE_PATH_LENGTH_CM  		22

#define MAX_SAMPLE_VALUE			255L

SpeedMeter::SpeedMeter(uint8_t pin, EventType eventType): eventType(eventType) {
	pinMode(pin, INPUT);
	PCintPort::attachInterrupt(pin, this, RISING);
	currentChangeTime = 0;
	previousChangeTime = 0;
	currentSampleIndex = 0;
	lastChangeTimestamp = 0;
	for (uint8_t * sample = samples;
			sample < samples + NUMBER_OF_SAMPLES;
			sample++) {
		*sample = 0;
	}
}

void SpeedMeter::pinChanged() {
	previousChangeTime = currentChangeTime;
	currentChangeTime = millis();
}

Event * SpeedMeter::handleEvent(Event * event) {
	Event * resultEvent = &Event::NO_EVENT;
	/* Disable interrupts and check the last pin change */
	long currentSample = 0;
	cli();
	if (lastChangeTimestamp != currentChangeTime) {
		lastChangeTimestamp = currentChangeTime;
		currentSample = currentChangeTime - previousChangeTime;
	}
	sei();
	if (currentSample != 0 && currentSample <= MAX_SAMPLE_VALUE) {
		/* TODO: update sample and generate event if needed */

		currentSampleIndex = (currentSampleIndex + 1) % NUMBER_OF_SAMPLES;
	}

	return resultEvent;
}
