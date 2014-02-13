#ifndef _Event_h_
#define _Event_h_

#include <Arduino.h>

#include "Event.h"

#define EVENT_STOP     0x30
#define EVENT_FORWARD  0x38
#define EVENT_BACKWARD 0x32
#define EVENT_FLEFT    0x34
#define EVENT_RIGHT    0x36

enum EventType {
	ControlEvent,
	DistanceEvent
};

class Event {
public:
	Event(EventType eventType, int eventData);
	EventType getType();
	int getData();
private:
	EventType type;
	int data;
};

#endif //_Event_h_
