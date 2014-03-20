/*
 * PrintTask.cpp
 *
 *  Created on: 05 марта 2014 г.
 *      Author: user
 */

#include <Arduino.h>
#include "PrintTask.h"

PrintTask::PrintTask() {
}

Event * PrintTask::handleEvent(Event * event) {
	Event * resultEvent = &Event::NO_EVENT;
	EventType type = event->getType();
	if (type == SpeedLeftEvent ||
			type == SpeedRightEvent) {
		if (type == SpeedRightEvent) {
			Serial.print("               ");
		}
		Serial.println(event->getData());
	}
	return resultEvent;
}

