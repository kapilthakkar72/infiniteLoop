/* 
 * File:   Utils.h
 * Author: harinder
 *
 * Created on 13 March, 2015, 5:51 PM
 */

#ifndef UTILS_H
#define	UTILS_H

#include <iostream>
#include <stdio.h>

using namespace std;

bool haveThePlayerWon(GameState gs, Position old_pos, PlayerNum playerNum) {
	if (playerNum == PlayerNum_P1 && old_pos.row
			== CURRENT_GAME_MAX_POSITION.row - 2) {
		//p1 has won
		return true;
	}

	else if (playerNum == PlayerNum_P2 && old_pos.row == 1) {
		//p2 has won
		return true;
	}

	return false;
}

bool haveIWon(GameState gs) {
	Position my_pos = gs.players[whoAmI].position;
	return haveThePlayerWon(gs, my_pos, whoAmI);
}

bool haveTheOpponentWon(GameState &gs) {
	Position opp_pos = gs.players[opponent].position;

	bool have_opponent_won = haveThePlayerWon(gs, opp_pos, opponent);

	if (have_opponent_won) {
		//My opponent has no existence for me now
		gs.graphStruct.graph[opp_pos.row][opp_pos.col] = ObjectType_EMPTY;
	}

	return have_opponent_won;
}

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

string getMePositionKey(Position pos) {
	stringstream ss;
	ss << pos.row << "|" << pos.col;
	return ss.str();
}

Position whereIsMyOpponent(GameState gs) {

	PlayerNum opponent;

	if (gs.turn == PlayerNum_P1)
		opponent = PlayerNum_P2;

	else
		opponent = PlayerNum_P1;

	return gs.players[opponent].position;
}

Position whereAmI(GameState gs) {

	return gs.players[gs.turn].position;
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

int getTotalRemaningWalls(GameState gs) {
	int totalWallsLeft = 0;
	totalWallsLeft += gs.players[0].wallsRemaining;
	totalWallsLeft += gs.players[1].wallsRemaining;
	return totalWallsLeft;
}

int getNumberOfWallsPlaced(GameState gs) {
	return (CURRENT_GAME_MAX_WALLS * 2) - getTotalRemaningWalls(gs);
}

#endif	/* UTILS_H */

