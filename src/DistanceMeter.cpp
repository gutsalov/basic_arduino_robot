/*
 * DistanceMeter.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "DistanceMeter.h"

/* Number of measurements per second */
#define DISTANCE_MEASUREMENT_FREQ	2
/* Time between two trigger events */
#define TRIGGER_PERIOD				1000000 / DISTANCE_MEASUREMENT_FREQ
#define MAX_SENSOR_DELAY 18000  // Maximum uS it takes for sensor to start the ping (SRF06 is the highest measured, just under 18ms).
#define NO_ECHO				0
#define PING_OVERHEAD		(double)580.31

DistanceMeter::DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin): newPing(trigger_pin, echo_pin)
{
	/* Initialize interrupts */
	PCintPort::attachInterrupt(echo_pin, this, FALLING);

	/* Initialize states */
	numberOfStates = 0;
	idleState = new IdleState(numberOfStates++, this);
	waitForEchoState = new WaitForEchoState(numberOfStates++, this);
	State * allStates[] = {
			idleState,
			waitForEchoState,
	};
	State ** states = new State*[numberOfStates];
	for (State **srcState = allStates, **targetState = states;
			srcState < allStates + numberOfStates;
			srcState++, targetState++) {
		*targetState = *srcState;
	}
	stateMachine = new StateMachineTask(states, numberOfStates, 0);
	lastTriggerTime = micros();
	lastRoundtripTime = 0;
}

void DistanceMeter::pinChanged(void) {
	lastEchoTime = micros();
}

bool DistanceMeter::timeoutExpired() {
	return (micros() - lastTriggerTime) > TRIGGER_PERIOD;
}

DistanceMeter::DistanceMeterState::DistanceMeterState(uint8_t id,
		DistanceMeter * distanceMeter): State(id), distanceMeter(distanceMeter){}

Event * DistanceMeter::handleEvent(Event * event) {
	return stateMachine->handleEvent(event);
}

Event * DistanceMeter::WaitForEchoState::enterState(uint8_t prev) {
	Event * event = &Event::NO_EVENT;
	distanceMeter->lastEchoTime = NO_ECHO;
	distanceMeter->lastRoundtripTime = NO_ECHO;

	distanceMeter->lastTriggerTime = micros();
	if (!distanceMeter->newPing.ping_trigger()) {
		event = new Event(ErrorEvent, ERROR_CODE_DISTANCE_METER);                // Something went wrong, abort.
	}
	cli();
	distanceMeter->lastEchoTime = NO_ECHO;
	sei();
	return event;
}

uint8_t DistanceMeter::WaitForEchoState::handleEvent(Event* event) {
	uint8_t newStateId = getId();
	unsigned long lastEchoTime;
	cli();
	lastEchoTime = distanceMeter->lastEchoTime;
	sei();
	if (lastEchoTime != NO_ECHO || distanceMeter->timeoutExpired()) {
		if(lastEchoTime != NO_ECHO) {
			distanceMeter->lastRoundtripTime = lastEchoTime - distanceMeter->lastTriggerTime - PING_OVERHEAD;
		}
		newStateId = distanceMeter->idleState->getId();
	}
	return newStateId;
}

Event * DistanceMeter::IdleState::enterState(uint8_t prev) {
	Event * event = &Event::NO_EVENT;
	if (distanceMeter->lastRoundtripTime != NO_ECHO) {
		event = new Event(DistanceEvent, ((double)distanceMeter->lastRoundtripTime) / US_ROUNDTRIP_CM);
	}
	return event;
}
uint8_t DistanceMeter::IdleState::handleEvent(Event* event) {
	uint8_t newState = getId();
	if (distanceMeter->timeoutExpired()) {
		newState = distanceMeter->waitForEchoState->getId();
	}
	return newState;
}
