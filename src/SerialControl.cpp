/*
 * SerialControl.cpp
 *
 *  Created on: 13 февр. 2014 г.
 *      Author: user
 */
#include <HardwareSerial.h>

#include "SerialControl.h"

SerialControl::SerialControl() {
	Serial.begin(9600);
}

Event * SerialControl::checkEvent() {
	if (Serial.available()) {
		Event * event = new Event(ControlEvent, Serial.read());
		return event;
	}
	else {
		return NULL;
	}
}
