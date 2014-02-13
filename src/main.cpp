#include <Arduino.h>
#include <HardwareSerial.h>
#include <AFMotor.h>
#include <cppsupport.h>

#include "Platform.h"
#include "State.h"
#include "IdleState.h"
#include "ForwardState.h"

#define MOTOR_ID_LEFT  1
#define MOTOR_ID_RIGHT 4

#define DELAY 1000

Platform * platform;
State ** states;
State * currentState;

void switchToState(State * newState) {
  newState->enterState(currentState->getId());
  currentState = newState;
}

void setup() {
  Serial.begin(9600);
  platform = new Platform(MOTOR_ID_LEFT, MOTOR_ID_RIGHT);
  states = new State * [NumberOfStates];
  states[StateIdle] = new IdleState(platform);
  states[StateForward] = new ForwardState(platform);
  switchToState(states[StateIdle]);
}

void loop() {
  if (Serial.available()) {
    int event = Serial.read();
    StateId newStateId = currentState->handleEvent(event);
    if (newStateId != currentState->getId()) {
      switchToState(states[newStateId]);
    }
  }
}

