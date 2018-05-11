/*
 * IterativeDeepeningAI.cpp
 *
 *  Created on: May 10, 2018
 *      Author: Luca
 */

#include "IterativeDeepeningAI.h"

IterativeDeepeningAI::IterativeDeepeningAI() {
	// TODO Auto-generated constructor stub
	_ai = NULL;
}

void IterativeDeepeningAI::setAI(AI * ai) {
	// TODO Auto-generated constructor stub
	_ai = ai;
}

void IterativeDeepeningAI::setDepth(uint8 depth) {
	// TODO Auto-generated constructor stub
	_ai->setDepth(depth);
}

Action IterativeDeepeningAI::choose(State * state) {
	Action result;

	for(int i = 8; i <= MAX_SEARCH_DEPTH; i++) {
		setDepth(i);
		std::cout << "Negascout profondo " << i << "\n";
		result = _ai->choose(state);
		std::cout << result << "\n";
		// if time_out() break;
	}

	return result;
}

IterativeDeepeningAI::~IterativeDeepeningAI() {
	// TODO Auto-generated destructor stub
}

