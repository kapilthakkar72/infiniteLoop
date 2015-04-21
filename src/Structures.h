/* 
 * File:   Structures.h
 * Author: kapil
 *
 * Created on 11 March, 2015, 8:07 PM
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#include<stdio.h>
#include<vector>
#include<queue>

#include "Constants.h"

using namespace std;

struct Position {
	int row;
	int col;
};

struct Node {
	Position pos;
	//f(n) = g(n) + h(n)
	double f;
	double g;
	int numberOfSteps;
	Node *parent;//TODO: to-do just because this is a pointer
};

struct Player {
	Position position;
	int wallsRemaining;
	PlayerNum playerNumber;
};

struct Weights {
	double a_0; // weight for moves
	double a_1; // weight for walls
};

struct Move {
	MoveType moveType;
	Position position;
	WallType wallType; //makes sense only if the movetype is placing wall
	bool isValid;
};

struct Graph {
	ObjectType graph[13 * 2 + 1][13 * 2 + 1];
};

struct Utility {
	double utilityVal;
	int walls_diff;
	int moves_diff;
};

struct GameState {
	Player players[2];

	PlayerNum turn; //refers to the object of the current player
	NodeType nodeType;

	Graph graphStruct;
	Move moveTakenToReach;
	Move moveToBeTaken;

	int level;
	Utility utility;
};

#endif	/* STRUCTURES_H */

