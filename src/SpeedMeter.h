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

struct Sample {
	uint8_t value;
	long    timestamp;
};

class SpeedMeter: public Task, PinChangeHandler {
	private:
	  EventType eventType;
	  volatile long currentChangeTime;
	  volatile long previousChangeTime;
	  long lastChangeTimestamp;
	  Sample samples[NUMBER_OF_SAMPLES];
	  uint8_t currentSampleIndex;
	public:
	  SpeedMeter(uint8_t pin, EventType eventType);
	  Event * handleEvent(Event * event);
	  virtual void pinChanged();
};



#endif /* SPEEDMETER_H_ */
