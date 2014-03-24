/*
 * DistanceMeter.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "DistanceMeter.h"

/* Number of measurements per second */
#define DISTANCE_MEASUREMENT_FREQ	5
/* Time between two trigger events */
#define TRIGGER_PERIOD				1000000 / DISTANCE_MEASUREMENT_FREQ

DistanceMeter::DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin)
{
	/* Initialize sonar hardware; got from NewPing */
	triggerBit = digitalPinToBitMask(trigger_pin); // Get the port register bitmask for the trigger pin.
	echoBit = digitalPinToBitMask(echo_pin);       // Get the port register bitmask for the echo pin.

	triggerOutput = portOutputRegister(digitalPinToPort(trigger_pin)); // Get the output port register for the trigger pin.
	echoInput = portInputRegister(digitalPinToPort(echo_pin));         // Get the input port register for the echo pin.

	/* Initialize states */
	numberOfStates = 0;
	idleState = new IdleState(numberOfStates++, this);
	waitForEchoState = new WaitForEchoState(numberOfStates++, this);
	errorState = new ErrorState(numberOfStates++, this);
	State * allStates[] = {
			idleState,
			waitForEchoState,
			errorState
	};
	State ** states = new State*[numberOfStates];
	for (State **srcState = allStates, **targetState = states;
			srcState < allStates + numberOfStates;
			srcState++, targetState++) {
		*targetState = *srcState;
	}
	stateMachine = new StateMachineTask(states, numberOfStates, 0);
	lastTriggerTime = micros();
}

DistanceMeter::DistanceMeterState::DistanceMeterState(uint8_t id,
		DistanceMeter * distanceMeter): State(id), distanceMeter(distanceMeter){}

Event * DistanceMeter::handleEvent(Event * event) {
	return stateMachine->handleEvent(event);
}

Event * DistanceMeter::WaitForEchoState::enterState(uint8_t prev) {
	return &Event::NO_EVENT;
}

uint8_t DistanceMeter::WaitForEchoState::handleEvent(Event* event) {
	return getId();
}

Event * DistanceMeter::IdleState::enterState(uint8_t prev) {
	return &Event::NO_EVENT;
}
uint8_t DistanceMeter::IdleState::handleEvent(Event* event) {
	uint8_t newState = getId();
	if (micros() - distanceMeter->lastTriggerTime > TRIGGER_PERIOD) {
		newState = distanceMeter->waitForEchoState->getId();
	}
	return newState;
}

Event * DistanceMeter::ErrorState::enterState(uint8_t prev) {
	return &Event::NO_EVENT;
}

uint8_t DistanceMeter::ErrorState::handleEvent(Event* event) {
	return getId();

}
