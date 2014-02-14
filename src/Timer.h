/*
 * Timer.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "InputDevice.h"

class Timer: public InputDevice {
private:
	unsigned long nextTick;
	uint16_t period;
public:
	Timer(uint16_t period);
	virtual Event * checkEvent();
};

#endif /* TIMER_H_ */
