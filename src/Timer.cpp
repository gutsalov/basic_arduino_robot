/*
 * Timer.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "Timer.h"

Timer::Timer(uint16_t period): period(period) {
	nextTick = millis() + period;
}

Event * Timer::checkEvent() {
	Event * event = NULL;
	unsigned long currentTime = millis();
	if (currentTime >= nextTick) {
		nextTick += period;
		event = new Event(TimerEvent, 0);
	}
	return event;
}
