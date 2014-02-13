/*
 * SerialControl.cpp
 *
 *  Created on: 13 ����. 2014 �.
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
