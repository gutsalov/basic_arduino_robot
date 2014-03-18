/*
 * SpeedMeter.cpp
 */

#include "SpeedMeter.h"

#include <Arduino.h>

#define NUMBER_OF_HOLES_PER_CIRCLE  20
#define CIRCLE_PATH_LENGTH_CM  		22
#define MAX_AVERAGE_INTERVAL		1000
#define MAX_SAMPLE_VALUE			255L

SpeedMeter::SpeedMeter(uint8_t pin, EventType eventType): eventType(eventType) {
	pinMode(pin, INPUT);
	PCintPort::attachInterrupt(pin, this, RISING);
	currentChangeTime = 0;
	previousChangeTime = 0;
	currentSampleIndex = 0;
	lastChangeTimestamp = 0;
	for (Sample * sample = samples;
			sample < samples + NUMBER_OF_SAMPLES;
			sample++) {
		sample->value = 0;
		sample->timestamp = 0;
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
		samples[currentSampleIndex].value = (uint8_t)currentSample;
		samples[currentSampleIndex].timestamp = lastChangeTimestamp;

		uint8_t sampleCount = 0;
		uint16_t sampleSum = 0;
		for (uint8_t sampleIndex = currentSampleIndex;
				sampleIndex != currentSampleIndex;
				sampleIndex = (sampleIndex + 1) % NUMBER_OF_SAMPLES) {
			if (lastChangeTimestamp - samples[sampleIndex].timestamp > MAX_AVERAGE_INTERVAL) {
				sampleSum += samples[sampleIndex].value;
				sampleCount++;
			}
		}
		resultEvent = new Event(eventType, (uint8_t)(sampleSum / sampleCount));
		currentSampleIndex = (currentSampleIndex + 1) % NUMBER_OF_SAMPLES;
	}

	return resultEvent;
}
