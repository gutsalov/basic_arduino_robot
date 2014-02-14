/*
 * TurnState.cpp
 *
 *  Created on: Feb 14, 2014
 *      Author: gutsan
 */

#include "TurnState.h"

TurnState::TurnState(StateId stateId, Platform * platform): State(stateId, platform) {}

void TurnState::enterState(int prev) {
	platform->move(getId() == StateTurnLeft ? Left : Right);
}

