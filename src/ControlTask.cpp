/*
 * ControlTask.cpp
 *
 *  Created on: 30 марта 2014 г.
 *      Author: user
 */

#include "ControlTask.h"
#include "Platform.h"

#define STOP_DISTANCE (double)10
#define SLOW_DISTANCE (double)70

ControlTask::ControlTask() {
}

Event * ControlTask::handleEvent(Event * event) {
	Event * newEvent = &Event::NO_EVENT;

	if (event->getType() == DistanceEvent) {
		newEvent = handleDistance(event->getData());
	}
	return newEvent;
}

Event * ControlTask::handleDistance(double distance) {
	Event * newEvent = &Event::NO_EVENT;
	if (distance <= STOP_DISTANCE) {
		newEvent = new Event(ChassisStopEvent, 0);
	}
	else if (distance <= SLOW_DISTANCE) {
		double speed = ((distance - STOP_DISTANCE) * ((double)MAX_CHASSIS_SPEED - (double)MIN_CHASSIS_SPEED))
				/ (SLOW_DISTANCE - STOP_DISTANCE) + MIN_CHASSIS_SPEED;
		newEvent = new Event(ChassisForwardEvent, speed);
	}
	return newEvent;
}
