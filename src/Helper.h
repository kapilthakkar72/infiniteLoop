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

		if (canMoveToDirection(currentNode.pos, g, Direction_UP)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos, Direction_UP);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}

		if (canMoveToDirection(currentNode.pos, g, Direction_DOWN)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos,
					Direction_DOWN);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}

		if (canMoveToDirection(currentNode.pos, g, Direction_LEFT)) {
			Node temp;
			temp.pos = getNewPositionInDirection(currentNode.pos,
					Direction_LEFT);
			temp.g = currentNode.g + 1;
			temp.f = temp.g + getHeuristicValue(p.playerNumber, temp.pos);
			temp.parent = &currentNode;
			temp.numberOfSteps = currentNode.numberOfSteps + 1;
			openList.push(temp);
		}

		if (canMoveToDirection(currentNode.pos, g, Direction_RIGHT)) {
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

//double utility(GameState g, Weights w) {
//    int p1walls = g.player1.wallsRemaining;
//    int p2walls = g.player2.wallsRemaining;
//
//    int walls = p1walls - p2walls;
//
//    //int noOfMoves1 = getNoOfMoves(g, 1);
//    //int noOfMoves2 = getNoOfMoves(g, 2);
//
//    int moves = noOfMoves1 - noOfMoves2;
//
//    return (w.a_0 * moves + w.a_1 * walls);
//}

GameState generateStartGameState(int maxWalls) {
	//TODO: can be used
	GameState startGS;
	startGS.alpha = MINUS_INFINITY;
	startGS.beta = INFINITY;

	startGS.parent = NULL;
	startGS.nodeType = NodeType_MAX_NODE;

	Player p1;
	p1.position.x = 2;
	p1.position.y = (CURRENT_GAME_MAX_POSITION.y + 1) / 2;
	p1.wallsRemaining = maxWalls;
	p1.playerNumber = PlayerNum_P1;

	Player p2;
	p2.position.x = CURRENT_GAME_MAX_POSITION.x - 1;
	p2.position.y = (CURRENT_GAME_MAX_POSITION.y + 1) / 2;
	p2.wallsRemaining = maxWalls;
	p2.playerNumber = PlayerNum_P2;

	startGS.player1 = p1;
	startGS.player2 = p2;

	startGS.turn = p1;

	return startGS;
}

vector<GameState> generateChildren(GameState gs) {
	vector<GameState> children;

	if (canMoveToDirection(gs.turn.position, gs.graph, Direction_UP)) {
	}

	if (canMoveToDirection(gs.turn.position, gs.graph, Direction_DOWN)) {

	}

	if (canMoveToDirection(gs.turn.position, gs.graph, Direction_LEFT)) {

	}

	if (canMoveToDirection(gs.turn.position, gs.graph, Direction_RIGHT)) {

	}

	return children;
}

GameState genChild_gameState(GameState gs) {
	GameState newGS;

	newGS.player1 = gs.player1; //TODO: shall be modified at a later stage
	newGS.player2 = gs.player2; //TODO: shall be modified at a later stage

	if (gs.turn.playerNumber == PlayerNum_P1) {
		//This is obvious - alternate turns
		newGS.nodeType = NodeType_MIN_NODE;
		newGS.turn = newGS.player2;
	} else {
		newGS.nodeType = NodeType_MAX_NODE;
		newGS.turn = newGS.player1;
	}

	newGS.alpha = gs.alpha;
	newGS.beta = gs.beta;

	newGS.graph = gs.graph; //TODO: shall be modified at a later stage
	newGS.move = gs.move; //TODO: shall be modified at a later stage

	newGS.parent = &gs; //the gs is now parent of newGs

	return newGS;

	//TODO: children will be added later
}
#endif	/* HELPER_H */

