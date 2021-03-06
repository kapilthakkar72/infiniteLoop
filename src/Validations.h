/* 
 * File:   Validations.h
 * Author: harinder
 *
 * Created on 12 March, 2015, 5:43 PM
 */

#ifndef VALIDATIONS_H
#define	VALIDATIONS_H

#include "Structures.h"
#include "GlobalVariables.h"
#include "Utils.h"

bool isPlayerObstructedByWall(Position old_pos, Graph graph,
		Direction direction) {
	switch (direction) {
	case Direction_UP:
		if (graph.graph[old_pos.row - 1][old_pos.col + 1] == ObjectType_WALL_H)
			return false;
		if (graph.graph[old_pos.row - 1][old_pos.col - 1] == ObjectType_WALL_H)
			return false;
		break;

	case Direction_DOWN:
		if (graph.graph[old_pos.row + 1][old_pos.col + 1] == ObjectType_WALL_H)
			return false;
		if (graph.graph[old_pos.row + 1][old_pos.col - 1] == ObjectType_WALL_H)
			return false;
		break;

	case Direction_LEFT:
		if (graph.graph[old_pos.row + 1][old_pos.col - 1] == ObjectType_WALL_V)
			return false;
		if (graph.graph[old_pos.row - 1][old_pos.col - 1] == ObjectType_WALL_V)
			return false;
		break;

	case Direction_RIGHT:
		if (graph.graph[old_pos.row + 1][old_pos.col + 1] == ObjectType_WALL_V)
			return false;
		if (graph.graph[old_pos.row - 1][old_pos.col + 1] == ObjectType_WALL_V)
			return false;
		break;
	}

	return true;

}

bool isOscillatingPosition(Position new_pos, PlayerNum turn) {

	if (turn != whoAmI)
		return false;

	if (new_pos.row != oscillating_position_not_take.row)
		return false;

	if (new_pos.col != oscillating_position_not_take.col)
		return false;

	return true;
}

bool isValidMoveForPlayer(Position old_pos, Graph graph, PlayerNum turn,
		Direction direction) {

	Position new_pos = getNewPositionInDirection(old_pos, direction);

	if (new_pos.row % 2 == 0 || new_pos.col % 2 == 0) //player can only be at odd positions
		return false;

	if (new_pos.row <= 0 || new_pos.col <= 0)
		return false;

	if (new_pos.row >= CURRENT_GAME_MAX_POSITION.row || new_pos.col
			>= CURRENT_GAME_MAX_POSITION.col) {
		return false;
	}

	if (isOscillatingPosition(new_pos, turn)) {
		return false;
	}

	return isPlayerObstructedByWall(old_pos, graph, direction);
}

bool isPosOccupiedByOtherPlayer(GameState gs, Position pos, Direction direction) {
	ObjectType objectType_opponent;
	Graph graph = gs.graphStruct;

	if (gs.turn == PlayerNum_P1) {
		objectType_opponent = ObjectType_PLAYER2;
	} else {
		objectType_opponent = ObjectType_PLAYER1;
	}

	switch (direction) {
	case Direction_UP:
		if (graph.graph[pos.row - 2][pos.col] == objectType_opponent)
			return true;
		break;

	case Direction_DOWN:
		if (graph.graph[pos.row + 2][pos.col] == objectType_opponent)
			return true;
		break;

	case Direction_LEFT:
		if (graph.graph[pos.row][pos.col - 2] == objectType_opponent)
			return true;
		break;

	case Direction_RIGHT:
		if (graph.graph[pos.row][pos.col + 2] == objectType_opponent)
			return true;
		break;
	}

	return false;
}

bool isGoalPosition(Player p) {
	if (p.playerNumber == PlayerNum_P1)
		if (p.position.row == 1)
			return true;
		else
			return false;
	else // player number 2
	if (p.position.row == CURRENT_GAME_MAX_POSITION.row - 2)
		return true;
	else
		return false;
}

//a_star specific
bool nodeGoalPosition(Node n, PlayerNum p_no) {
	if (p_no == PlayerNum_P1)
		if (n.pos.row == CURRENT_GAME_MAX_POSITION.row - 2)
			return true;
		else
			return false;
	else // player number 2
	if (n.pos.row == 1)
		return true;
	else
		return false;
}

//a_star specific
bool presentInClosed(Node n, vector<Node> &closed) {
	for (vector<Node>::iterator it = closed.begin(); it != closed.end(); it++) {
		Node currentNode = *it;
		if (currentNode.pos.row == n.pos.row && currentNode.pos.col
				== n.pos.col) {
			return true;
		}
	}

	return false;
}

#endif	/* VALIDATIONS_H */

