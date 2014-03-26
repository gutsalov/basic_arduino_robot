#ifndef _Event_h_
#define _Event_h_

#include <Arduino.h>

#include "Event.h"

#define EVENT_STOP     'E'
#define EVENT_FORWARD  'A'
#define EVENT_BACKWARD 'B'
#define EVENT_LEFT     'C'
#define EVENT_RIGHT    'D'

#define ERROR_CODE_DISTANCE_METER	1

enum EventType {
	NoEvent,
	ErrorEvent,
	ControlEvent,
	DistanceEvent,
	TimerEvent,
	ChassisForwardEvent,
	ChassisBackwardEvent,
	ChassisLeftEvent,
	ChassisRightEvent,
	ChassisStopEvent,
	SpeedLeftEvent,
	SpeedRightEvent
};

class Event {
public:
	static Event NO_EVENT;

	Event(EventType eventType, double eventData);
	EventType getType();
	double getData();
private:
	EventType type;
	double data;
};

#endif //_Event_h_
