/* 
 * File:   Helper.h
 * Author: kapil
 *
 * Created on 11 March, 2015, 8:14 PM
 */

#ifndef HELPER_H
#define	HELPER_H

#include "Constants.h"

#include "Structures.h"
#include "GlobalVariables.h"
#include "Utils.h"
#include "Validations.h"

// This is just used to define priority of queue
class CompareNodes {
public:

	bool operator()(const Node comp1, const Node comp2) const {
		return ((comp1.f) > (comp2.f));
	}
};

double getHeuristicValue(PlayerNum playerNumber, Position currentPos) {
	if (playerNumber == PlayerNum_P1) {
		// Player 1 will start from top and has to reach to end
		return (MAX_ROW * 2 - currentPos.x);
	} else // for player 2
	{
		// player 2 will start from bottom of the board and has to reach to top of the board
		return (currentPos.x - 2);
	}
}

//returns the path cost (number of steps)
int a_star(Graph g, Player p) {

	priority_queue<Node, vector<Node> , CompareNodes> openList;

	vector<Node> closeList;

	Node n;
	n.g = 0;
	n.pos.x = p.position.x;
	n.pos.y = p.position.y;
	n.f = getHeuristicValue(p.playerNumber, n.pos);
	n.numberOfSteps = 0;
	n.parent = NULL;

	openList.push(n);

	Node currentNode;

	while (!openList.empty()) {
		// Take out first Node of the queue
		currentNode = openList.top();
		openList.pop();

		if (nodeGoalPosition(currentNode, p.playerNumber)) {
			// reached to end... stop
			break;
		}

		if (presentInClosed(currentNode, closeList))
			continue;

		// put currentNode in the closed list
		closeList.push_back(currentNode);

		if (isValidMoveForPlayer(currentNode.pos, g, Direction_UP)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos, Direction_UP);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}

		if (isValidMoveForPlayer(currentNode.pos, g, Direction_DOWN)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos,
					Direction_DOWN);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}

		if (isValidMoveForPlayer(currentNode.pos, g, Direction_LEFT)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos,
					Direction_LEFT);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}

		if (isValidMoveForPlayer(currentNode.pos, g, Direction_RIGHT)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos,
					Direction_RIGHT);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}
	}

	if (openList.empty() || !nodeGoalPosition(currentNode, p.playerNumber)) {
		//path = NULL;
		return -1;
	} else {
		return currentNode.numberOfSteps;
	}
}

double utility(GameState g, Weights w) {
	int p1walls = g.players[PlayerNum_P1].wallsRemaining;
	int p2walls = g.players[PlayerNum_P2].wallsRemaining;

	int walls = p1walls - p2walls;

	int noOfMoves1 = a_star(g.graph, g.players[PlayerNum_P1]);
	int noOfMoves2 = a_star(g.graph, g.players[PlayerNum_P2]);

	int moves = noOfMoves1 - noOfMoves2;

	return (w.a_0 * moves + w.a_1 * walls);
}

GameState genChild_gameState(GameState gs) {
	GameState newGS;

	newGS.players[PlayerNum_P1] = gs.players[PlayerNum_P1]; //modified at a later stage
	newGS.players[PlayerNum_P2] = gs.players[PlayerNum_P2]; //modified at a later stage

	if (gs.turn == PlayerNum_P1) {
		//This is obvious - alternate turns
		newGS.nodeType = NodeType_MIN_NODE;
		newGS.turn = PlayerNum_P2;
	} else {
		newGS.nodeType = NodeType_MAX_NODE;
		newGS.turn = PlayerNum_P1;
	}

	newGS.alpha = gs.alpha;
	newGS.beta = gs.beta;

	newGS.graph = gs.graph; //modified at a later stage
	newGS.move = gs.move; //modified at a later stage

	return newGS;
}

void helper_movePlayer(GameState gs, Direction direction,
		vector<GameState> & successors) {
	if (!isValidMoveForPlayer(gs.players[gs.turn].position, gs.graph, direction)) {
		return;
	}

	GameState new_GS = genChild_gameState(gs);
	Position new_pos = getNewPositionInDirection(gs.players[gs.turn].position,
			direction);
	new_GS.players[gs.turn].position = new_pos;
	new_GS.move.moveType = MoveType_PLAYER;
	new_GS.move.position = new_pos;
	new_GS.graph.graph[new_pos.x][new_pos.y] = playerNum_to_ObjectType(gs.turn); //new position of player
	new_GS.graph.graph[gs.players[gs.turn].position.x][gs.players[gs.turn].position.y]
			= ObjectType_EMPTY; //the previous position is offcourse empty

	successors.push_back(new_GS);
}

void helper_placeWall(GameState gs, vector<GameState> & successors,
		WallType wallType, Position pos) {

	if (!isValidPositionForWall(pos, gs.graph, wallType)) {
		return;
	}

	GameState new_gs = genChild_gameState(gs);

	if (wallType == WallType_H)
		new_gs.graph.graph[pos.x][pos.y] = ObjectType_WALL_H;
	else
		new_gs.graph.graph[pos.x][pos.y] = ObjectType_WALL_V;

	new_gs.move.moveType = MoveType_PLACE_WALL;
	new_gs.move.position = pos;

	successors.push_back(new_gs);
}

vector<GameState> generateSuccessors(GameState gs) {
	vector<GameState> successors;

	helper_movePlayer(gs, Direction_UP, successors);
	helper_movePlayer(gs, Direction_DOWN, successors);
	helper_movePlayer(gs, Direction_LEFT, successors);
	helper_movePlayer(gs, Direction_RIGHT, successors);

	for (int i = 2; i < CURRENT_GAME_MAX_POSITION.x - 2; i += 2) {
		for (int j = 2; j < CURRENT_GAME_MAX_POSITION.y - 2; j += 2) {
			Position new_pos;
			new_pos.x = i;
			new_pos.y = j;

			helper_placeWall(gs, successors, WallType_H, new_pos);
			helper_placeWall(gs, successors, WallType_V, new_pos);
		}
	}

	return successors;
}

GameState alpha_beta(GameState node, double alpha, double beta, Weights w) {
	if (node.level == CUTOFF_LEVEL) {
		node.utilityVal = utility(node, w);
		return node;
	}

	if (node.nodeType == NodeType_MAX_NODE) {
		vector<GameState> successors = generateSuccessors(node);

		for (vector<GameState>::iterator it = successors.begin(); it
				!= successors.end(); it++) {
			GameState tempGS = alpha_beta(*it, alpha, beta, w);
			alpha = max_my(alpha, tempGS.utilityVal);

			if (alpha >= beta) {
				node.utilityVal = beta;
				return node;
			}

		}
		node.utilityVal = alpha;
		return node;
	}

	else { //MIN_NODE
		vector<GameState> successors = generateSuccessors(node);

		for (vector<GameState>::iterator it = successors.begin(); it
				!= successors.end(); it++) {
			GameState tempGS = alpha_beta(*it, alpha, beta, w);
			beta = min_my(beta, tempGS.utilityVal);

			if (alpha >= beta) {
				node.utilityVal = alpha;
				return node;
			}

		}
		node.utilityVal = beta;
		return node;
	}
}

Move getMeMove(GameState gs) {
	gs = alpha_beta(gs, MINUS_INFINITY_THAKKAR, INFINITY_THAKKAR, Wts_final);
	return gs.move;
}

GameState generateStartGameState(int maxWalls) {
	GameState startGS;
	startGS.alpha = MINUS_INFINITY_THAKKAR;
	startGS.beta = INFINITY_THAKKAR;

	startGS.nodeType = NodeType_MAX_NODE;

	Player p1;
	p1.position.x = 1;
	p1.position.y = (CURRENT_GAME_MAX_POSITION.y + 1) / 2;
	p1.wallsRemaining = maxWalls;
	p1.playerNumber = PlayerNum_P1;

	Player p2;
	p2.position.x = CURRENT_GAME_MAX_POSITION.x - 2;
	p2.position.y = (CURRENT_GAME_MAX_POSITION.y + 1) / 2;
	p2.wallsRemaining = maxWalls;
	p2.playerNumber = PlayerNum_P2;

	startGS.players[PlayerNum_P1] = p1;
	startGS.players[PlayerNum_P2] = p2;

	startGS.turn = PlayerNum_P1;

	return startGS;
}

#endif	/* HELPER_H */

