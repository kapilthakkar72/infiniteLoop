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

Position whereIsMyOpponent(GameState gs) {

	PlayerNum opponent;

	if (gs.turn == PlayerNum_P1)
		opponent = PlayerNum_P2;

	else
		opponent = PlayerNum_P1;

	return gs.players[opponent].position;
}

Position getNewPositionInDirection(Position pos, Direction direction) {
	Position new_pos;

	new_pos.row = pos.row;
	new_pos.col = pos.col;

	switch (direction) {
	case Direction_UP:
		new_pos.row -= 2;
		break;

	case Direction_DOWN:
		new_pos.row += 2;
		break;

	case Direction_LEFT:
		new_pos.col -= 2;
		break;

	case Direction_RIGHT:
		new_pos.col += 2;
		break;

	default:
		cout << "ERROR: shall never come here" << endl;
		exit(1);
		break;
	}

	return new_pos;
}

#endif	/* UTILS_H */

