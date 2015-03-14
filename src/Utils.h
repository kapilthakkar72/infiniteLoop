/* 
 * File:   Utils.h
 * Author: harinder
 *
 * Created on 13 March, 2015, 5:51 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#include <iostream>

using namespace std;

ObjectType playerNum_to_ObjectType(PlayerNum p_num) {

	switch (p_num) {
	case PlayerNum_P1:
		return ObjectType_PLAYER1;
		break;
	case PlayerNum_P2:
		return ObjectType_PLAYER2;
		break;
	default:
		cout << "ERROR: shall never reach here" << endl;
		exit(1);
		break;
	}
}

Position getNewPositionInDirection(Position pos, Direction direction) {
	Position new_pos;

	new_pos.x = pos.x;
	new_pos.y = pos.y;

	switch (direction) {
	case Direction_UP:
		new_pos.x -= 2;
		break;

	case Direction_DOWN:
		new_pos.x += 2;
		break;

	case Direction_LEFT:
		new_pos.y -= 2;
		break;

	case Direction_RIGHT:
		new_pos.y += 2;
		break;

	default:
		cout << "ERROR: shall never come here" << endl;
		exit(1);
		break;
	}

	return new_pos;
}

#endif	/* UTILS_H */

