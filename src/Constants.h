/* 
 * File:   Constants.h
 * Author: kt
 *
 * Created on March 11, 2015, 11:04 PM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#include<limits.h>

enum PlayerNum {
	PlayerNum_P1, PlayerNum_P2
};

enum WallType {
	WallType_H, WallType_V, WallType_None
};

enum MoveType {
	MoveType_PLAYER, MoveType_PLACE_WALL, MoveType_NONE
};

enum NodeType {
	NodeType_MIN_NODE, NodeType_MAX_NODE
};

enum ObjectType {
	ObjectType_WALL_H,
	ObjectType_WALL_V,
	ObjectType_PLAYER1,
	ObjectType_PLAYER2,
	ObjectType_EMPTY
};

enum Direction {
	Direction_UP, Direction_DOWN, Direction_LEFT, Direction_RIGHT
};

#define CUTOFF_LEVEL 3

#define INFINITY_THAKKAR INT_MAX
#define MINUS_INFINITY_THAKKAR INT_MIN

#endif	/* CONSTANTS_H */

