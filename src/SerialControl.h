/*
 * SerialControl.h
 *
 *  Created on: 13 февр. 2014 г.
 *      Author: user
 */

#ifndef SERIALCONTROL_H_
#define SERIALCONTROL_H_

#include "InputDevice.h"

class SerialControl: public InputDevice {
public:
	SerialControl();
	virtual Event * checkEvent();
};

#endif /* SERIALCONTROL_H_ */
