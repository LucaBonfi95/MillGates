/*
 * Test.cpp
 *
 *  Created on: 02 mag 2018
 *      Author: Lorenzo Rosa
 */


#include "CubeStateImpl.h"
#include <iostream>
#include "NodeExpander.h"


//Given a pos, returns a string (e.g. "a1").
std::string get2Dcoordinates(int8 pos) {
	if(!IS_VALID(pos))
		return "";
	std::string res("");
	int8 i = GETX(pos);
	int8 j = GETY(pos);
	int8 k = GETZ(pos);

	if(j==0) { //a,b,c
			if (k==2) {
				res.append("a");
				res.append(std::string(1, '0' + 7-(3*i)));
			}
			else if (k==1) {
				res.append("b");
				res.append(std::string(1, '0' + 6-(2*i) ));
			}
			else if (k==0) {
				res.append("c");
				res.append(std::string(1, '0' + 5-i ));
			}
	}
	else if (j==1) { //d
			res.append("d");
			if (i==2) //1,2,3
				res.append(std::string(1, '0' + 3-k ));
			else if (i==0)
				res.append(std::string(1, '0' + 5+k ));
			else
				res.append("4"); //d4, central pos
	}
	else if (j==2){  //e,f,g
			if (k==2) {
				res.append("g");
				res.append(std::string(1, '0' + 7-(3*i) ));
			}
			else if (k==1) {
				res.append("f");
				res.append(std::string(1, '0' + 6-(2*i) ));
			}
			else if (k==0) {
				res.append("e");
				res.append(std::string(1, '0' + 5-i ));
			}
	}

	return res;
}

//Given two chars, returns a pos
int8 get3Dcoordinates(char x, char y) {
	int i, j, k;
	i = j = k = -1;

	//Convert from char to int
	y= y - '1' + 1;

	if ( x == 'd') { // 'd'
		//Coordinate 'x'
		j = 1;
		//Coordinate 'y'
		if ( y > 0 && y < 4) {
			i = 2;
			k =  3 - y;
		}
		else if ( y == 4) {
			i = 1;
			k = 0;
		}
		else if (y > 4 && y < 8) {
			i = 0;
			k = y % 5;
		}
		else return POS_NULL;
	}
	else {
		//Coordinate 'x'
		if (x >= 'a' && (x/100) == 0) { // 'a','b','c'
			j = 0;
			k = 2 - (x % 'a');
		}
		else if (x <= 'g' && (x/100) == 1) { // 'e','f','g'
			j = 2;
			k = x % 'e';
		} else return POS_NULL;

		//Coordinate 'y'
		if ( y > 0 && y < 4 )
			i = 2;
		else if ( y == 4)
			i = 1;
		else if (y > 4 && y < 8)
			i = 0;
		else return POS_NULL;
	}

	if (i<0 || j<0 || k<0)
		return POS_NULL;

	return NEW_POS(i,j,k);
}

void checkMapping(State*state, char x, char y) {
	state->setPawnAt2D(x, y, PAWN_WHITE);
	if(state->getPawnAt(2, 0, 2) != state->getPawnAt2D(x, y))
		std::cout << x << y << " wrong!\n";
	else {
		int8 pos = get3Dcoordinates(x, y);
		int i = GETX(pos);
		int j = GETY(pos);
		int k = GETZ(pos);
		std::cout << x << y << " mapped into " << i << " " << j << " " << k << "\n";
	}
}

void testMapping(State*state) {
	//Test mapping ==> OK
	std::cout << "Testing mapping\n";
	checkMapping(state, 'a','1');
	checkMapping(state, 'a','4');
	checkMapping(state, 'a','7');
	checkMapping(state, 'b','2');
	checkMapping(state, 'b','4');
	checkMapping(state, 'b','6');
	checkMapping(state, 'c','3');
	checkMapping(state, 'c','4');
	checkMapping(state, 'c','5');
	checkMapping(state, 'd','1');
	checkMapping(state, 'd','2');
	checkMapping(state, 'd','3');
	checkMapping(state, 'd','5');
	checkMapping(state, 'd','6');
	checkMapping(state, 'd','7');
	checkMapping(state, 'e','3');
	checkMapping(state, 'e','4');
	checkMapping(state, 'e','5');
	checkMapping(state, 'f','2');
	checkMapping(state, 'f','4');
	checkMapping(state, 'f','6');
	checkMapping(state, 'g','1');
	checkMapping(state, 'g','4');
	checkMapping(state, 'g','7');
}

void testIsInMorris(State*state) {
	//Diagonals ==> TODO: please avoid that
	state->setPawnAt2D('a', '7', PAWN_WHITE);
	state->setPawnAt2D('b', '6', PAWN_WHITE);
	state->setPawnAt2D('c', '5', PAWN_WHITE);

	if(state->isInMorris(get3Dcoordinates('a', '7')))
		std::cout << "a7 forms a morris!\n";
	else
		std::cout << "a7 doesn't form a morris\n"; //EXPECTED ==> WRONG! TODO

	//Following are correct; but they should be invoked properly
	bool x = state->isInMorris(get3Dcoordinates('a', '7'), X_AXIS); //False => ok
	bool y = state->isInMorris(get3Dcoordinates('a', '7'), Y_AXIS); //False => ok
	bool z = state->isInMorris(get3Dcoordinates('a', '7'), Z_AXIS); //True => ok, but we should not consider it now

	std::cout << "a7" << " is in morris: x =" << x << " y = " << y << " z = " << z << "\n";

	delete state;

	//x axis
	state = new CubeStateImpl();
	state->setPawnAt2D('c', '5', PAWN_WHITE);
	state->setPawnAt2D('d', '5', PAWN_WHITE);
	state->setPawnAt2D('e', '5', PAWN_WHITE);

	if(state->isInMorris(get3Dcoordinates('d', '5')))
		std::cout << "d5 forms a morris!\n"; //Expected => OK
	else
		std::cout << "d5 doesn't form a morris\n";

	if(state->isInMorris(get3Dcoordinates('a', '1')))
		std::cout << "d5 forms a morris!\n";
	else
		std::cout << "d5 doesn't form a morris\n"; //Expected => OK
}

void testWillBeInMorris(State*state) {
	state->setPawnAt2D('d', '1', PAWN_WHITE);
	state->setPawnAt2D('d', '2', PAWN_WHITE);

	if(state->willBeInMorris(get3Dcoordinates('d', '2'), get3Dcoordinates('d','3'), PAWN_WHITE))
		std::cout << "SI\n";
	else
		std::cout << "NO\n"; //Expected

}

void testGetAllPositions(State*state) {
	/* Test for getAllPositions
	 * NONE ok
	 * WHITE ok
	 * BLACK ok
	 */
	std::vector<int8> res = state->getAllPositions(PAWN_BLACK);
	std::cout << "Posizioni nere: " << res.size() << "\n";

	for (int8 i = 0; i < res.size(); i++) {
		std::cout <<  get2Dcoordinates(res[i]) <<"\n";
	}
}

void testGetAvailablePositions(State*state, char x, char y){
	//Phase 1 and Phase 3 calls getAllPositions(PAWN_NONE)
	//TODO: INCLUDE SE STESSO!
	std::vector<int8> res = state->getAvailablePositions(get3Dcoordinates('g','7'));

	std::cout << "Posizioni disponibili da g7: " << res.size() << "\n";
	for (int8 i = 0; i < res.size(); i++)
		std::cout <<  get2Dcoordinates(res[i]) <<"\n";


	//Phase 2 ==> see the pic I sent on Telegram

	state->setPhase(PHASE_2);

	state->setBlackCheckersOnBoard("9");
	state->setWhiteCheckersOnBoard("8");

	state->setPawnAt2D('a', '1', PAWN_WHITE);
	state->setPawnAt2D('a', '4', PAWN_WHITE);
	state->setPawnAt2D('a', '7', PAWN_BLACK);

	state->setPawnAt2D('b', '2', PAWN_BLACK);
	state->setPawnAt2D('b', '4', PAWN_BLACK);
	state->setPawnAt2D('b', '6', PAWN_BLACK);

	state->setPawnAt2D('c', '3', PAWN_BLACK);
	state->setPawnAt2D('c', '4', PAWN_WHITE);
	state->setPawnAt2D('c', '5', PAWN_BLACK);

	state->setPawnAt2D('d', '1', PAWN_BLACK);
	state->setPawnAt2D('d', '3', PAWN_WHITE);
	state->setPawnAt2D('d', '5', PAWN_BLACK);
	state->setPawnAt2D('d', '7', PAWN_BLACK);

	state->setPawnAt2D('e', '4', PAWN_WHITE);
	state->setPawnAt2D('e', '5', PAWN_WHITE);

	state->setPawnAt2D('f', '4', PAWN_WHITE);

	state->setPawnAt2D('g', '7', PAWN_WHITE);

	res = state->getAvailablePositions(get3Dcoordinates(x,y));
	std::cout << "Posizioni disponibili da "<< x << y << ": " << res.size() << "\n";

	for (int8 i = 0; i < res.size(); i++) {
		std::cout <<  get2Dcoordinates(res[i]) <<"\n";
	}
}

int main(void) {

	State *state;

	/* TESTING THE STATE */
//	state = new CubeStateImpl(); //Creates a void state
//	testMapping(state);
//	delete state;
//
//	//Test isInMorris
//	state = new CubeStateImpl();
//	testIsInMorris(state);
//	delete state;
//
	//Test willBeInMorris
	state = new CubeStateImpl();
	testWillBeInMorris(state);
	delete state;

	//Test getAllPositions
//	state = new CubeStateImpl();
//	testGetAllPositions(state);
//	delete state;

//	//Test getAvailablePositions
//	state = new CubeStateImpl();
//	testGetAvailablePositions(state, 'f', '4');
//	delete state;

	/* TESTING THE EXPANDER */

	//state = new CubeStateImpl();

	//Node node(state, PAWN_WHITE);
	//NodeExpander expander;

	// FASE 1a

	//Caso 1: prima espansione ==> ok, rimane il problema della getAvailable: una delle azioni possibili � stare fermo
//	std::vector<Action> res = expander.expand(node);
//	std::cout << "Azioni disponibili: "<< res.size() << "\n";
//	for(int8 j=0; j<res.size(); j++)
//		std::cout << res[j] << "\n";

	// FASE 1b
	//Caso 2: presenti due pedine nere ==> ok, rimane il problema della getAvailable: una delle azioni possibili � stare fermo
//	node.getState()->setPawnAt2D('a', '1', PAWN_BLACK);
//	node.getState()->setPawnAt2D('g', '7', PAWN_BLACK);
//	std::vector<Action> res = expander.expand(node);
//	std::cout << "Azioni disponibili: "<< res.size() << "\n";
//	for(int8 j=0; j<res.size(); j++)
//	std::cout << res[j] << "\n";
//	delete state;

	//FASE 2 (state: see the pic I sent on Telegram)
	state = new CubeStateImpl();

	state->setPhase(PHASE_2);

	state->setBlackCheckersOnBoard("9");
	state->setWhiteCheckersOnBoard("8");

	state->setPawnAt2D('a', '1', PAWN_WHITE);
	state->setPawnAt2D('a', '4', PAWN_WHITE);
	state->setPawnAt2D('a', '7', PAWN_BLACK);

	state->setPawnAt2D('b', '2', PAWN_BLACK);
	state->setPawnAt2D('b', '4', PAWN_BLACK);
	state->setPawnAt2D('b', '6', PAWN_BLACK);

	state->setPawnAt2D('c', '3', PAWN_BLACK);
	state->setPawnAt2D('c', '4', PAWN_WHITE);
	state->setPawnAt2D('c', '5', PAWN_BLACK);

	state->setPawnAt2D('d', '1', PAWN_BLACK);
	state->setPawnAt2D('d', '3', PAWN_WHITE);
	state->setPawnAt2D('d', '5', PAWN_BLACK);
	state->setPawnAt2D('d', '7', PAWN_BLACK);

	state->setPawnAt2D('e', '4', PAWN_WHITE);
	state->setPawnAt2D('e', '5', PAWN_WHITE);

	state->setPawnAt2D('f', '4', PAWN_WHITE);
	state->setPawnAt2D('g', '7', PAWN_WHITE);

	Node node(state, PAWN_WHITE);
	NodeExpander expander;

	std::vector<Action> res = expander.expand(node);
	std::cout << "Azioni disponibili: "<< res.size() << "\n";
	for(int8 j=0; j<res.size(); j++)
		std::cout << res[j] << "\n";

}
