/*
 * PrintTask.h
 *
 *  Created on: 05 марта 2014 г.
 *      Author: user
 */

#ifndef PRINTTASK_H_
#define PRINTTASK_H_

#include "Task.h"

class PrintTask: public Task {
public:
	PrintTask();
	Event * handleEvent(Event * event);
};


#endif /* PRINTTASK_H_ */
