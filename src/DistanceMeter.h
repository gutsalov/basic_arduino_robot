/*
 * DistanceMeter.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#ifndef DISTANCEMETER_H_
#define DISTANCEMETER_H_

#include <PinChangeInt.h>
#include <NewPing.h>
#include "StateMachineTask.h"

class DistanceMeter: public Task, PinChangeHandler {
private:
	class DistanceMeterState: public State {
	protected:
		DistanceMeter * distanceMeter;
	public:
		DistanceMeterState(uint8_t id, DistanceMeter * distanceMeter);
	};
	class WaitForEchoState: public DistanceMeterState {
	public:
		WaitForEchoState(uint8_t id, DistanceMeter * distanceMeter):
			DistanceMeterState(id, distanceMeter){};
	    virtual Event * enterState(uint8_t prev);
	    virtual uint8_t handleEvent(Event* event);
	};
	class IdleState: public DistanceMeterState {
	public:
		IdleState(uint8_t id, DistanceMeter * distanceMeter):
			DistanceMeterState(id, distanceMeter){};
	    virtual Event * enterState(uint8_t prev);
	    virtual uint8_t handleEvent(Event* event);
	};
	WaitForEchoState * waitForEchoState;
	IdleState * idleState;
	uint8_t numberOfStates;
	StateMachineTask * stateMachine;
	NewPing newPing;
	unsigned long lastTriggerTime;
	unsigned long lastRoundtripTime;
	volatile unsigned long lastEchoTime;
protected:
	bool timeoutExpired();
public:
	DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin);
	virtual Event * handleEvent(Event * event);
    virtual void pinChanged();
};

#endif /* DISTANCEMETER_H_ */
