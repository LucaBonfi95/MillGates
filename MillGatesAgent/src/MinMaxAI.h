/*
 * MinMaxAI.h
 *
 *  Created on: May 6, 2018
 *      Author: Luca
 */

#ifndef MINMAXAI_H_
#define MINMAXAI_H_

#include "AI.h"
#include "ExpVector.h"
#include "ZobristHashing.h"

class MinMaxAI: public AI {
private:

	std::vector<ExpVector<hashcode>*> * _hashes;
	ZobristHashing * _hasher;
	int _count;
	uint8 _depth;

	int evaluate(State * state);
	int min(State * state, hashcode hashcode, int level);
	int max(State * state, hashcode hashcode, int level);
	bool visited(hashcode hashcode);
	void add(hashcode hashcode);

public:
	MinMaxAI();
	virtual ~MinMaxAI();
	virtual void setDepth(uint8 depth);
	virtual Action choose(State * state);
};

#endif /* MINMAXAI_H_ */
