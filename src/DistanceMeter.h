/*
 * DistanceMeter.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#ifndef DISTANCEMETER_H_
#define DISTANCEMETER_H_
#include <NewPing.h>

#include "InputDevice.h"

#define MAX_DISTANCE 50
#define NUMBER_OF_SAMPLES 5

class DistanceMeter: public InputDevice {
public:
	DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin);
	virtual Event * checkEvent();
private:
	NewPing * sonar;
	bool pingInProgress;
	uint8_t samples[NUMBER_OF_SAMPLES];
	int currentSampleIndex;
	uint8_t average(uint8_t current);
};

#endif /* DISTANCEMETER_H_ */
