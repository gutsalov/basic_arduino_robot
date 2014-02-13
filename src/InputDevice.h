/*
 * InputDevice.h
 *
 *  Created on: 13 февр. 2014 г.
 *      Author: user
 */

#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_

#include "Event.h"

class InputDevice {
public:
	InputDevice();
	virtual Event * checkEvent() = 0;
};

#endif /* INPUTDEVICE_H_ */
