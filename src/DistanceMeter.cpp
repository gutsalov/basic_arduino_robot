/*
 * DistanceMeter.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */
#include "DistanceMeter.h"

#define NOT_INITIALIZED 255

DistanceMeter::DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin) {
	sonar = new NewPing(trigger_pin, echo_pin, MAX_DISTANCE);
	pingInProgress = false;
	currentSampleIndex = 0;
	for (uint8_t * sample = samples; sample < samples + NUMBER_OF_SAMPLES; sample++) {
		*sample = NOT_INITIALIZED;
	}
}

Event * DistanceMeter::checkEvent() {
	Event * distanceEvent = NULL;
	if (!pingInProgress) {
		/* No ping in progress, start timer */
		sonar->ping_timer(NULL);
		pingInProgress = true;
	} else if (sonar->check_timer()) {
		/* Echo received, calculate distance */
		pingInProgress = false;
		uint8_t distance = sonar->ping_result / US_ROUNDTRIP_CM;
		samples[currentSampleIndex] = distance;
		uint8_t avrg = average(distance);
		if ((distance - avrg) < (avrg / 2)) {
			distanceEvent = new Event(DistanceEvent, distance);
		}
		currentSampleIndex = (currentSampleIndex + 1) % NUMBER_OF_SAMPLES;
	}
	return distanceEvent;
}

uint8_t DistanceMeter::average(uint8_t current) {
	int numberOfSamples = 1;
	uint16_t sum = current;
	for (uint8_t * sample = samples; sample < samples + NUMBER_OF_SAMPLES; sample++) {
		if (*sample != NOT_INITIALIZED) {
			sum += *sample;
			numberOfSamples++;
		}
	}
	return sum / numberOfSamples;
}
