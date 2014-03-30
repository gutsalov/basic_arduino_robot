/*
 * ControlTask.h
 *
 *  Created on: 30 марта 2014 г.
 *      Author: user
 */

#ifndef CONTROLTASK_H_
#define CONTROLTASK_H_

#include "Task.h"

class ControlTask: public Task {
public:
	ControlTask();
	virtual Event * handleEvent(Event * event);
private:
	Event * handleDistance(double distance);
};

#endif /* CONTROLTASK_H_ */
