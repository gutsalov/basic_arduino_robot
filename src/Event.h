#ifndef _Event_h_
#define _Event_h_

#include <Arduino.h>

#include "Event.h"

#define EVENT_STOP     'E'
#define EVENT_FORWARD  'A'
#define EVENT_BACKWARD 'B'
#define EVENT_LEFT     'C'
#define EVENT_RIGHT    'D'

enum EventType {
	ControlEvent,
	DistanceEvent,
	TimerEvent
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
