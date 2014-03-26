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
#define US_ROUNDTRIP_CM		(double)58.31

DistanceMeter::DistanceMeter(uint8_t trigger_pin, uint8_t echo_pin)
{
	/* Initialize sonar hardware; got from NewPing */
	triggerBit = digitalPinToBitMask(trigger_pin); // Get the port register bitmask for the trigger pin.
	echoBit = digitalPinToBitMask(echo_pin);       // Get the port register bitmask for the echo pin.

	triggerOutput = portOutputRegister(digitalPinToPort(trigger_pin)); // Get the output port register for the trigger pin.
	echoInput = portInputRegister(digitalPinToPort(echo_pin));         // Get the input port register for the echo pin.

	/* Initialize interrupts */
	pinMode(echo_pin, INPUT);
	PCintPort::attachInterrupt(echo_pin, this, RISING);

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
	Serial.print("WaitForEchoState::enterState: ");
	Serial.println(distanceMeter->lastTriggerTime);
	distanceMeter->lastEchoTime = NO_ECHO;
	distanceMeter->lastRoundtripTime = NO_ECHO;
	/* Code got from NewPing */
	*(distanceMeter->triggerOutput) &= ~(distanceMeter->triggerBit); // Set the trigger pin low, should already be low, but this will make sure it is.
	delayMicroseconds(4);            // Wait for pin to go low, testing shows it needs 4uS to work every time.
	*(distanceMeter->triggerOutput) |= (distanceMeter->triggerBit);  // Set trigger pin high, this tells the sensor to send out a ping.
	delayMicroseconds(10);           // Wait long enough for the sensor to realize the trigger pin is high. Sensor specs say to wait 10uS.
	*(distanceMeter->triggerOutput) &= ~(distanceMeter->triggerBit); // Set trigger pin back to low.

	unsigned long max_time =  micros() + MAX_SENSOR_DELAY;                  // Set a timeout for the ping to trigger.
	while (*(distanceMeter->echoInput) & (distanceMeter->echoBit) && micros() <= max_time) {} // Wait for echo pin to clear.
	while (!(*(distanceMeter->echoInput) & (distanceMeter->echoBit)))                          // Wait for ping to start.
		if (micros() > max_time) return new Event(ErrorEvent, ERROR_CODE_DISTANCE_METER);                // Something went wrong, abort.
	distanceMeter->lastTriggerTime = micros();
	return &Event::NO_EVENT;
}

uint8_t DistanceMeter::WaitForEchoState::handleEvent(Event* event) {
	uint8_t newStateId = getId();
	unsigned long lastEchoTime;
	cli();
	lastEchoTime = distanceMeter->lastEchoTime;
	sei();
	if (lastEchoTime != NO_ECHO || distanceMeter->timeoutExpired()) {
		if(lastEchoTime != NO_ECHO) {
			distanceMeter->lastRoundtripTime = lastEchoTime - distanceMeter->lastTriggerTime;
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
