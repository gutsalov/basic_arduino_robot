/*
 * SpeedMeter.h
 */

#ifndef SPEEDMETER_H_
#define SPEEDMETER_H_

#include <Arduino.h>
#include <PinChangeInt.h>
#include "Task.h"
#include "Event.h"

#define NUMBER_OF_SAMPLES	5

class SpeedMeter: public Task, PinChangeHandler {
	private:
	  EventType eventType;
	  volatile unsigned long currentChangeTime;
	  volatile unsigned long previousChangeTime;
	  unsigned long lastChangeTimestamp;
	public:
	  SpeedMeter(uint8_t pin, EventType eventType);
	  Event * handleEvent(Event * event);
	  virtual void pinChanged();
};



#endif /* SPEEDMETER_H_ */
