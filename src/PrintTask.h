/*
 * PrintTask.h
 *
 *  Created on: 05 ����� 2014 �.
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
