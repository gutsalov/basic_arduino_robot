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
		int symbol = Serial.read();
		Serial.print("Control = ");
		Serial.println(symbol, HEX);
		Event * event = new Event(ControlEvent, symbol);
		return event;
	}
	else {
		return NULL;
	}
}
