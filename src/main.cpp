#include <Arduino.h>
#include <HardwareSerial.h>
#include <AFMotor.h>
#include <cppsupport.h>
#include <QueueList.h>

#include "Platform.h"
#include "State.h"
#include "IdleState.h"
#include "ForwardState.h"
#include "TurnState.h"
#include "SerialControl.h"
#include "DistanceMeter.h"
#include "Timer.h"

#define MOTOR_ID_LEFT  1
#define MOTOR_ID_RIGHT 2

#define SONAR_PIN_TRIGGER A1
#define SONAR_PIN_ECHO A0

#define NUMBER_OF_INPUT_DEVICES 3

#define TIMER_PERIOD 100

#define DELAY 3000

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
	inputDevices[1] = new DistanceMeter(SONAR_PIN_TRIGGER, SONAR_PIN_ECHO);
	inputDevices[2] = new Timer(TIMER_PERIOD);
	/* states */
	states = new State * [NumberOfStates];
	states[StateIdle] = new IdleState(platform);
	states[StateForward] = new ForwardState(platform);
	states[StateTurnLeft] = new TurnState(StateTurnLeft, platform);
	states[StateTurnRight] = new TurnState(StateTurnRight, platform);
	switchToState(states[StateIdle]);

	pinMode(A3, OUTPUT);
	digitalWrite(A3, HIGH);
	pinMode(A4, OUTPUT);
	digitalWrite(A4, HIGH);
	pinMode(A5, OUTPUT);
	digitalWrite(A5, HIGH);
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


