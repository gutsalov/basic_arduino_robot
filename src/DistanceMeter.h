/*
 * DistanceMeter.h
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#ifndef DISTANCEMETER_H_
#define DISTANCEMETER_H_

#include "StateMachineTask.h"

class DistanceMeter: public Task {
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
	class ErrorState: public DistanceMeterState {
	public:
		ErrorState(uint8_t id, DistanceMeter * distanceMeter):
			DistanceMeterState(id, distanceMeter){};
	    virtual Event * enterState(uint8_t prev);
	    virtual uint8_t handleEvent(Event* event);
	};
	WaitForEchoState * waitForEchoState;
	IdleState * idleState;
	ErrorState * errorState;
	uint8_t numberOfStates;
	StateMachineTask * stateMachine;
	uint8_t triggerBit;
	uint8_t echoBit;
	volatile uint8_t *triggerOutput;
	volatile uint8_t *echoInput;
	unsigned long lastTriggerTime;
public:
	DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin);
	virtual Event * handleEvent(Event * event);
};

#endif /* DISTANCEMETER_H_ */
