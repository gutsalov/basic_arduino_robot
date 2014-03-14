/*
 * SpeedMeter.h
 */

#ifndef SPEEDMETER_H_
#define SPEEDMETER_H_

#include <Arduino.h>
#include <PinChangeInt.h>
#include "Task.h"
#include "Event.h"

class SpeedMeter: public Task {
	private:
	  EventType eventType;
	  uint8_t pin;
	  int state;
	  int count;
	  long stateTime;
	public:
	  SpeedMeter(uint8_t pin, EventType eventType);

	  Event * handleEvent(Event * event);
};



#endif /* SPEEDMETER_H_ */
