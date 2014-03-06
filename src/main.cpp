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
#include "SpeedMeter.h"
#include "PrintTask.h"

#define MOTOR_ID_LEFT  1
#define MOTOR_ID_RIGHT 2

#define SPEED_METER_LEFT  A3
#define SPEED_METER_RIGHT A4

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
Task ** tasks;

void switchToState(State * newState) {
	newState->enterState(currentState->getId());
	currentState = newState;
}

void setup() {
	/* platform */
	platform = new Platform(MOTOR_ID_LEFT, MOTOR_ID_RIGHT);
	/* devices */
//	inputDevices = new InputDevice * [NUMBER_OF_INPUT_DEVICES];
//	inputDevices[0] = new SerialControl();
//	inputDevices[1] = new DistanceMeter(SONAR_PIN_TRIGGER, SONAR_PIN_ECHO);
//	inputDevices[2] = new Timer(TIMER_PERIOD);
	/* states */
	states = new State * [NumberOfStates];
	states[StateIdle] = new IdleState(platform);
	states[StateForward] = new ForwardState(platform);
	states[StateTurnLeft] = new TurnState(StateTurnLeft, platform);
	states[StateTurnRight] = new TurnState(StateTurnRight, platform);
	switchToState(states[StateForward]);

	tasks = new Task * [3];
	tasks[0] = new SpeedMeter(SPEED_METER_LEFT, SpeedLeftEvent);
	tasks[1] = new SpeedMeter(SPEED_METER_RIGHT, SpeedRightEvent);
	tasks[2] = new PrintTask();
}

void loop() {
	Event * event = eventQueue.isEmpty() ? &Event::NO_EVENT : eventQueue.pop();
	/*
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
	*/
	for (Task ** task = tasks; task < tasks + 3; task++) {
		Event * newEvent = (*task)->handleEvent(event);
		if (newEvent != &Event::NO_EVENT) {
			eventQueue.push(newEvent);
		}
	}
	if (event != &Event::NO_EVENT) {
		delete event;
	}
}


