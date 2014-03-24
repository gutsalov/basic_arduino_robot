/*
 * Event.cpp
 *
 *  Created on: 13 февр. 2014 г.
 *      Author: user
 */
#include "Event.h"

Event Event::NO_EVENT(NoEvent, 0);

Event::Event(EventType eventType, double eventData): type(eventType), data(eventData){};

EventType Event::getType() {
	return type;
}

double Event::getData() {
	return data;
}
