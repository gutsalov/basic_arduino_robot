/*
 * PrintTask.cpp
 *
 *  Created on: 05 марта 2014 г.
 *      Author: user
 */

#include <Arduino.h>
#include "PrintTask.h"

PrintTask::PrintTask() {
	Serial.begin(9600);
}

Event * PrintTask::handleEvent(Event * event) {
	Event * resultEvent = &Event::NO_EVENT;
	EventType type = event->getType();
	if (type == SpeedLeftEvent ||
			type == SpeedRightEvent) {
		Serial.print(type == SpeedLeftEvent ? "Left" : "Right");
		Serial.print(" weel speed = ");
		Serial.print(event->getData());
		Serial.println(" cm/s");
	}
	return resultEvent;
}

