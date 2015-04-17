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
	MoveType_PLAYER, MoveType_PLACE_WALL, MoveType_NONE, MoveType_PASS
//TODO: moveType pass abi ke liye..remove if not required
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

#define CUTOFF_MOVE 2
#define CUTOFF_LEVEL_P1 CUTOFF_MOVE*2
#define CUTOFF_LEVEL_P2 CUTOFF_LEVEL_P1+1

#define INFINITY_THAKKAR INT_MAX
#define MINUS_INFINITY_THAKKAR INT_MIN

#define IS_TRAINING_MODE false
#define MAX_TIMES_OSCILLATING 3
#define IS_FAST_MODE_DEFAULT true
#define IS_SUPER_FAST_MODE_DEFAULT false //TODO: this shall be false
#define NUM_OF_WALLS_FIRST_ALARM 2
#define NUM_OF_WALLS_SECOND_ALARM 5

#define WTS_FINAL_A0 1.0
#define WTS_FINAL_A1 1.1

#define WTS_CHANGING_A0 1.0
#define WTS_CHANGING_A1 1.1

#define ALLOWED_WALLS_ADJACENT_OPPONENT 1
#define WALL_OPPONENT_MAX_GAP ((ALLOWED_WALLS_ADJACENT_OPPONENT - 1) * 2) + 1

#define BUFFER_SUPER_FAST_MODE 5 //remaining time(sec) to start superFast mode

#endif	/* CONSTANTS_H */

