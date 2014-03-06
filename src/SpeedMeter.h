/*
 * SpeedMeter.h
 *
 *  Created on: 05 марта 2014 г.
 *      Author: user
 */

#ifndef SPEEDMETER_H_
#define SPEEDMETER_H_

#include <Arduino.h>
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
	  SpeedMeter(uint8_t pin, EventType eventType): eventType(eventType), pin(pin) {
		  pinMode(pin, INPUT);
		  state = digitalRead(pin);
		  stateTime = millis();
		  count = 0;
	  };

	  Event * handleEvent(Event * event);
};



#endif /* SPEEDMETER_H_ */
