#include <Arduino.h>
#include <HardwareSerial.h>
#include <AFMotor.h>
#include <cppsupport.h>
#include <QueueList.h>

#include "Platform.h"
#include "State.h"
#include "IdleState.h"
#include "ForwardState.h"
#include "SerialControl.h"

#define MOTOR_ID_LEFT  1
#define MOTOR_ID_RIGHT 4
#define NUMBER_OF_INPUT_DEVICES 1

#define DELAY 1000

Platform * platform;
State ** states;
State * currentState;
InputDevice ** inputDevices;
QueueList<Event *> eventQueue;

void switchToState(State * newState) {
	newState->enterState(currentState->getId());
	currentState = newState;
}

void setup() {
	/* platform */
	platform = new Platform(MOTOR_ID_LEFT, MOTOR_ID_RIGHT);
	/* devices */
	inputDevices = new InputDevice * [NUMBER_OF_INPUT_DEVICES];
	inputDevices[0] = new SerialControl();
	/* states */
	states = new State * [NumberOfStates];
	states[StateIdle] = new IdleState(platform);
	states[StateForward] = new ForwardState(platform);
	switchToState(states[StateIdle]);
}

void loop() {
	Event * event = NULL;
	for (InputDevice ** device = inputDevices; device < inputDevices + NUMBER_OF_INPUT_DEVICES; device++) {
		event = (*device)->checkEvent();
		if (event != NULL) {
			eventQueue.push(event);
		}
	}
	if (!eventQueue.isEmpty()) {
		StateId newStateId = currentState->handleEvents(&eventQueue);
		if (newStateId != currentState->getId()) {
			switchToState(states[newStateId]);
		}
	}
}

