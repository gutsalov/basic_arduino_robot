/*
 * Task.h
 *
 *  Created on: 05 марта 2014 г.
 *      Author: user
 */

#ifndef TASK_H_
#define TASK_H_

#include "Event.h"

class Task {
public:
	virtual Event * handleEvent(Event * event) = 0;
};


#endif /* TASK_H_ */
