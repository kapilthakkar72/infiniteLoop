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

enum MoveType {
    MoveType_PLAYER, MoveType_PLACE_WALL
};

enum NodeType {
    NodeType_MIN_NODE, NodeType_MAX_NODE
};

enum ObjectType {
    ObjectType_WALL, ObjectType_PLAYER1, ObjectType_PLAYER2, ObjectType_EMPTY
};

enum Direction {
    Direction_UP, Direction_DOWN, Direction_LEFT, Direction_RIGHT
};


#define MAX_ROW 9
#define MAX_COL 9

#define INFINITY INT_MAX
#define MINUS_INFINITY INT_MIN

#endif	/* CONSTANTS_H */

