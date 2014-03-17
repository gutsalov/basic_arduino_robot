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

QueueList<Event *> eventQueue;
Task ** allTasks;
uint8_t numberOfTasks;

void setup() {
	Task * tasks[]= {
			new Platform(MOTOR_ID_LEFT, MOTOR_ID_RIGHT),
			new SpeedMeter(SPEED_METER_LEFT, SpeedLeftEvent),
			new SpeedMeter(SPEED_METER_RIGHT, SpeedRightEvent),
			new PrintTask()
		};
	uint8_t numberOfTasks = sizeof(allTasks) / sizeof(Task *);
	allTasks = new Task * [numberOfTasks];
	for (Task ** source = tasks, **target = allTasks; source < tasks + numberOfTasks; source++, target++) {
		*target = *source;
	}
	Event * event = new Event(ChassisForwardEvent, MAX_CHASSIS_SPEED);
	eventQueue.push(event);
}

void loop() {
	Event * event = eventQueue.isEmpty() ? &Event::NO_EVENT : eventQueue.pop();
	for (Task ** task = allTasks; task < allTasks + 3; task++) {
		Event * newEvent = (*task)->handleEvent(event);
		if (newEvent != &Event::NO_EVENT) {
			eventQueue.push(newEvent);
		}
	}
	if (event != &Event::NO_EVENT) {
		delete event;
	}
}


