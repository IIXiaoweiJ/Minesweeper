#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "textureManager.h"
#include <cstdlib> 

#include <map>
using namespace std;
using namespace sf;


class tile {
public:
	
	vector<tile> adjacent;
	int displayCondition ; //contains all realConditions but has its own values (11,12,13)
	int realCondition;
	bool alreadyRevealed;
	void setDisplayCondition(int i) {
		displayCondition = i;
	
	}
	void setRealCondition(int i) {
		realCondition = i;
	
	}
	void setalreadyRevealed(bool i) {
		alreadyRevealed = i;

	}
	void displayEqualsReal() {
		displayCondition = realCondition;
	}
	/*
	0: mine
	1. 1round
	2. 2 around
	.
	.
	.
	8. 8 mines around
	9. default condition(hidden tile)  //not for real condition , only for display
	10. real default condition underneath hidden(texture as revealed)   ****empty tile****
	11. flagged // for display 
	12. already revealed
	
	*/

	
	void tiledefault() {
		displayCondition = 9;

	}
	
	void setunRecursive() {
		realCondition = 12;
	}

};
