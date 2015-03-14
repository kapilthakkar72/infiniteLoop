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
		return (MAX_ROW * 2 - currentPos.row);
	} else // for player 2
	{
		// player 2 will start from bottom of the board and has to reach to top of the board
		return (currentPos.row - 2);
	}
}

void helper_a_star(Node & currentNode, Graph & g, Player & p,
		priority_queue<Node, vector<Node> , CompareNodes> & openList,
		Direction direction) {

	if (!isValidMoveForPlayer(currentNode.pos, g, direction)) {
		return;
	}

	Node temp;
	temp.pos = getNewPositionInDirection(currentNode.pos, direction);
	temp.g = currentNode.g + 1;
	temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
	temp.parent = &currentNode;
	temp.numberOfSteps = currentNode.numberOfSteps + 1;
	openList.push(temp);
}

//returns the path cost (number of steps)
int a_star(Graph g, Player p) {

	priority_queue<Node, vector<Node> , CompareNodes> openList;

	vector<Node> closeList;

	Node n;
	n.g = 0;
	n.pos.row = p.position.row;
	n.pos.col = p.position.col;
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

		helper_a_star(currentNode, g, p, openList, Direction_UP);
		helper_a_star(currentNode, g, p, openList, Direction_DOWN);
		helper_a_star(currentNode, g, p, openList, Direction_LEFT);
		helper_a_star(currentNode, g, p, openList, Direction_RIGHT);
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

	newGS.level = gs.level + 1;
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
	new_GS.moveTakenToReach.moveType = MoveType_PLAYER;
	new_GS.moveTakenToReach.position = new_pos;
	new_GS.graph.graph[new_pos.row][new_pos.col] = playerNum_to_ObjectType(
			gs.turn); //new position of player
	new_GS.graph.graph[gs.players[gs.turn].position.row][gs.players[gs.turn].position.col]
			= ObjectType_EMPTY; //the previous position is offcourse empty

	successors.push_back(new_GS);
}

void helper_placeWall(GameState gs, vector<GameState> & successors,
		WallType wallType, Position pos) {

	if (!isValidPositionForWall(pos, gs.graph, wallType)) {
		return;
	}

	GameState new_gs = genChild_gameState(gs);

	if (wallType == WallType_H) {
		new_gs.graph.graph[pos.row][pos.col] = ObjectType_WALL_H;
		new_gs.moveTakenToReach.wallType = WallType_H;
	} else {
		new_gs.graph.graph[pos.row][pos.col] = ObjectType_WALL_V;
		new_gs.moveTakenToReach.wallType = WallType_V;
	}

	new_gs.moveTakenToReach.moveType = MoveType_PLACE_WALL;
	new_gs.moveTakenToReach.position = pos;

	successors.push_back(new_gs);
}

vector<GameState> generateSuccessors(GameState gs) {
	vector<GameState> successors;

	helper_movePlayer(gs, Direction_UP, successors);
	helper_movePlayer(gs, Direction_DOWN, successors);
	helper_movePlayer(gs, Direction_LEFT, successors);
	helper_movePlayer(gs, Direction_RIGHT, successors);

	if (gs.players[whoAmI].wallsRemaining == 0) {
		return successors;
	}

	Position new_pos;
	for (int i = 2; i < CURRENT_GAME_MAX_POSITION.row - 2; i += 2) {
		new_pos.row = i;
		for (int j = 2; j < CURRENT_GAME_MAX_POSITION.col - 2; j += 2) {
			new_pos.col = j;

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

			if (alpha < tempGS.utilityVal) {
				alpha = tempGS.utilityVal;
				node.moveToBeTaken = tempGS.moveTakenToReach;
			}

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

			if (beta > tempGS.utilityVal) {
				beta = tempGS.utilityVal;
				node.moveToBeTaken = tempGS.moveTakenToReach;
			}

			if (alpha >= beta) {
				node.utilityVal = alpha;
				return node;
			}

		}
		node.utilityVal = beta;
		return node;
	}
}

GameState getMeMove(GameState gs) {
	gs.level = 0;

	gs.moveTakenToReach.moveType = MoveType_NONE;
	gs.moveTakenToReach.wallType = WallType_None;
	gs.moveTakenToReach.position.row = 0;
	gs.moveTakenToReach.position.col = 0;

	gs.moveToBeTaken.moveType = MoveType_NONE;
	gs.moveToBeTaken.wallType = WallType_None;
	gs.moveToBeTaken.position.row = 0;
	gs.moveToBeTaken.position.col = 0;

	gs.utilityVal = MINUS_INFINITY_THAKKAR;

	gs = alpha_beta(gs, MINUS_INFINITY_THAKKAR, INFINITY_THAKKAR, Wts_final);
	return gs;
}

GameState generateStartGameState(int maxWalls) {
	GameState startGS;
	startGS.alpha = MINUS_INFINITY_THAKKAR;
	startGS.beta = INFINITY_THAKKAR;

	startGS.nodeType = NodeType_MAX_NODE;

	Player p1;
	p1.position.row = 1;
	p1.position.col = (CURRENT_GAME_MAX_POSITION.col - 1) / 2;
	p1.wallsRemaining = maxWalls;
	p1.playerNumber = PlayerNum_P1;

	Player p2;
	p2.position.row = CURRENT_GAME_MAX_POSITION.row - 2;
	p2.position.col = (CURRENT_GAME_MAX_POSITION.col - 1) / 2;
	p2.wallsRemaining = maxWalls;
	p2.playerNumber = PlayerNum_P2;

	startGS.players[PlayerNum_P1] = p1;
	startGS.players[PlayerNum_P2] = p2;

	startGS.turn = PlayerNum_P1;

	for (int i = 0; i < CURRENT_GAME_MAX_POSITION.row; i++) {
		for (int j = 0; j < CURRENT_GAME_MAX_POSITION.col; j++) {
			startGS.graph.graph[i][j] = ObjectType_EMPTY;
		}
	}

	startGS.graph.graph[p1.position.row][p1.position.col] = ObjectType_PLAYER1;
	startGS.graph.graph[p2.position.row][p2.position.col] = ObjectType_PLAYER2;

	return startGS;
}

#endif	/* HELPER_H */
