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

bool isValidMoveForPlayer(Position old_pos, Graph graph, Direction direction) {

	Position new_pos = getNewPositionInDirection(old_pos, direction);

	if (new_pos.x % 2 == 0 || new_pos.y % 2 == 0) //player can only be at odd positions
		return false;

	if (new_pos.x <= 0 || new_pos.y <= 0)
		return false;

	if (new_pos.x >= CURRENT_GAME_MAX_POSITION.x || new_pos.y
			>= CURRENT_GAME_MAX_POSITION.y) {
		return false;
	}

	switch (direction) {
	case Direction_UP:
		if (graph.graph[old_pos.x + 1][old_pos.y - 1] == ObjectType_WALL_H)
			return false;
		if (graph.graph[old_pos.x - 1][old_pos.y - 1] == ObjectType_WALL_H)
			return false;
		break;

	case Direction_DOWN:
		if (graph.graph[old_pos.x + 1][old_pos.y + 1] == ObjectType_WALL_H)
			return false;
		if (graph.graph[old_pos.x - 1][old_pos.y + 1] == ObjectType_WALL_H)
			return false;
		break;

	case Direction_LEFT:
		if (graph.graph[old_pos.x - 1][old_pos.y + 1] == ObjectType_WALL_V)
			return false;
		if (graph.graph[old_pos.x - 1][old_pos.y - 1] == ObjectType_WALL_V)
			return false;
		break;

	case Direction_RIGHT:
		if (graph.graph[old_pos.x + 1][old_pos.y + 1] == ObjectType_WALL_V)
			return false;
		if (graph.graph[old_pos.x + 1][old_pos.y - 1] == ObjectType_WALL_V)
			return false;
		break;
	}

	return true;
}

//here pos denotes the middle of the wall
bool isValidPositionForWall(Position pos, Graph graph, WallType wallType) {
	if (pos.x % 2 != 0 || pos.y % 2 != 0) //walls can only be at even positions
		return false;

	if (pos.x <= 1 || pos.y <= 1)
		return false;

	if (pos.x >= CURRENT_GAME_MAX_POSITION.x - 2 || pos.y
			>= CURRENT_GAME_MAX_POSITION.y - 2) {
		//we have subtracted 2 because the pos denotes the middle
		return false;
	}

	if (graph.graph[pos.x][pos.y] == ObjectType_WALL_H)
		return false;

	if (graph.graph[pos.x][pos.y] == ObjectType_WALL_V)
		return false;

	switch (wallType) {
	case WallType_H:
		if (graph.graph[pos.x + 2][pos.y] == ObjectType_WALL_H)
			return false;
		if (graph.graph[pos.x - 2][pos.y] == ObjectType_WALL_H)
			return false;
		break;

	case WallType_V:
		if (graph.graph[pos.x][pos.y + 2] == ObjectType_WALL_V)
			return false;
		if (graph.graph[pos.x][pos.y - 2] == ObjectType_WALL_V)
			return false;
		break;
	}

	return true;
}

bool isPosOccupiedByOtherPlayer(Player player, Position pos, Graph graph_struct) {
	if (player.playerNumber == PlayerNum_P1 && graph_struct.graph[pos.x][pos.y]
			== ObjectType_PLAYER2)
		return true;

	if (player.playerNumber == PlayerNum_P2 && graph_struct.graph[pos.x][pos.y]
			== ObjectType_PLAYER1)
		return true;

	return false;
}

bool isGoalPosition(Player p) {
	if (p.playerNumber == PlayerNum_P1)
		if (p.position.x == 1)
			return true;
		else
			return false;
	else // player number 2
	if (p.position.x == CURRENT_GAME_MAX_POSITION.x - 2)
		return true;
	else
		return false;
}

//a_star specific
bool nodeGoalPosition(Node n, PlayerNum p_no) {
	if (p_no == PlayerNum_P1)
		if (n.pos.x == 1)
			return true;
		else
			return false;
	else // player number 2
	if (n.pos.x == CURRENT_GAME_MAX_POSITION.x - 2)
		return true;
	else
		return false;
}

//a_star specific
bool presentInClosed(Node n, vector<Node> &closed) {
	for (vector<Node>::iterator it = closed.begin(); it != closed.end(); it++) {
		Node currentNode = *it;
		if (currentNode.pos.x == n.pos.x && currentNode.pos.y == n.pos.y) {
			return true;
		}
	}

	return false;
}

#endif	/* VALIDATIONS_H */

