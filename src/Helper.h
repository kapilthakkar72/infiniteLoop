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

int getHeuristicValue(PlayerNum playerNumber, Position currentPos) {
	if (playerNumber == PlayerNum_P1) {
		// Player 1 will start from top and has to reach to end
		int temp = CURRENT_GAME_MAX_POSITION.row - currentPos.row - 1;
		temp /= 2;
		return temp;
	}

	else {
		// player 2 will start from bottom of the board and has to reach to top of the board
		return ((currentPos.row - 1) / 2);
	}
}

void helper_a_star(Node & currentNode, Graph & g, Player & p,
		priority_queue<Node, vector<Node> , CompareNodes> & openList,
		Direction direction, PlayerNum turn) {

	if (!isValidMoveForPlayer(currentNode.pos, g, turn, direction)) {
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
int a_star(Graph g, Player p, PlayerNum turn) {

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

		helper_a_star(currentNode, g, p, openList, Direction_UP, turn);
		helper_a_star(currentNode, g, p, openList, Direction_DOWN, turn);
		helper_a_star(currentNode, g, p, openList, Direction_LEFT, turn);
		helper_a_star(currentNode, g, p, openList, Direction_RIGHT, turn);
	}

	if (!nodeGoalPosition(currentNode, p.playerNumber)) {
		//path = NULL;
		return -1;
	} else {
		return currentNode.numberOfSteps;
	}
}

//here pos denotes the middle of the wall
bool isValidPositionForWall(Position wall_pos, GameState gs, WallType wallType) {

	Graph graph = gs.graphStruct;

	if (wall_pos.row % 2 != 0 || wall_pos.col % 2 != 0) //walls can only be at even positions
		return false;

	if (IS_FAST_MODE) {
		Position opp_pos = whereIsMyOpponent(gs);

		if (abs(wall_pos.row - opp_pos.row) > 1)
			return false;

		if (abs(wall_pos.col - opp_pos.col) > 1)
			return false;
	}

	if (wall_pos.row <= 1 || wall_pos.col <= 1)
		return false;

	if (wall_pos.row >= CURRENT_GAME_MAX_POSITION.row - 2 || wall_pos.col
			>= CURRENT_GAME_MAX_POSITION.col - 2) {
		//we have subtracted 2 because the pos denotes the middle
		return false;
	}

	if (gs.graphStruct.graph[wall_pos.row][wall_pos.col] == ObjectType_WALL_H)
		return false;

	if (gs.graphStruct.graph[wall_pos.row][wall_pos.col] == ObjectType_WALL_V)
		return false;

	Graph tempGraph = graph;

	switch (wallType) {
	case WallType_H:
		if (graph.graph[wall_pos.row][wall_pos.col + 2] == ObjectType_WALL_H)
			return false;
		if (graph.graph[wall_pos.row][wall_pos.col - 2] == ObjectType_WALL_H)
			return false;

		tempGraph.graph[wall_pos.row][wall_pos.col] = ObjectType_WALL_H;
		break;

	case WallType_V:
		if (graph.graph[wall_pos.row + 2][wall_pos.col] == ObjectType_WALL_V)
			return false;
		if (graph.graph[wall_pos.row - 2][wall_pos.col] == ObjectType_WALL_V)
			return false;

		tempGraph.graph[wall_pos.row][wall_pos.col] = ObjectType_WALL_V;
		break;

	case WallType_None:
		cout << "Error---shall never come here" << endl;
		exit(1);
		break;
	}

	//placing a wall shall not block any player
	if (a_star(tempGraph, gs.players[PlayerNum_P1], gs.turn) == -1)
		return false;

	if (a_star(tempGraph, gs.players[PlayerNum_P2], gs.turn) == -1)
		return false;

	return true;
}

Utility utility(GameState g, Weights w) {
	Utility utility;

	int p1walls = g.players[PlayerNum_P1].wallsRemaining;
	int p2walls = g.players[PlayerNum_P2].wallsRemaining;

	int walls;
	//if (whoAmI == PlayerNum_P1)
	walls = p1walls - p2walls;
	//else
	//walls = p2walls - p1walls;

	//int noOfMoves1 = -1;
	//int noOfMoves2 = -1;

	/*if (whoAmI == PlayerNum_P1 && HAVE_OPPONENT_WON)
	 noOfMoves2 = 0;

	 if (whoAmI == PlayerNum_P1 && HAVE_I_WON)
	 noOfMoves1 = 0;

	 if (whoAmI == PlayerNum_P2 && HAVE_OPPONENT_WON)
	 noOfMoves1 = 0;

	 if (whoAmI == PlayerNum_P2 && HAVE_I_WON)
	 noOfMoves2 = 0;*/

	//if (noOfMoves1 != -1)
	int noOfMoves1 = a_star(g.graphStruct, g.players[PlayerNum_P1], g.turn);

	//if (noOfMoves2 != -1)
	int noOfMoves2 = a_star(g.graphStruct, g.players[PlayerNum_P2], g.turn);

	int moves;
	//if (whoAmI == PlayerNum_P1)
	moves = noOfMoves2 - noOfMoves1;
	//else
	//moves = noOfMoves1 - noOfMoves2;

	//utility.utilityVal = w.a_0 * moves + w.a_1 * walls;

	utility.utilityVal = w.a_0 * moves + w.a_1 * walls;

	//if (!HAVE_OPPONENT_WON)
	//utility.utilityVal += w.a_1 * walls; //TODO: may be -- think later if req

	utility.moves_diff = moves;
	utility.walls_diff = walls;

	if (DO_I_HAVE_OPTION && !HAVE_OPPONENT_WON) {

		if (whoAmI == PlayerNum_P1 && noOfMoves2 == 0) {
			utility.utilityVal = MINUS_INFINITY_THAKKAR;
		}

		if (whoAmI == PlayerNum_P2 && noOfMoves1 == 0) {
			utility.utilityVal = INFINITY_THAKKAR;
		}
	}

	return utility;
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

	newGS.graphStruct = gs.graphStruct; //modified at a later stage

	newGS.level = gs.level + 1;
	return newGS;
}

void helper_movePlayer(GameState gs, Position old_pos, Direction direction,
		vector<GameState> & successors);

void playerBehindHandler(GameState gs, Position old_pos, Direction direction,
		vector<GameState> & successors) {
	Position tmp_pos = old_pos;

	switch (direction) {
	case Direction_UP:
		tmp_pos.row -= 2;
		break;

	case Direction_DOWN:
		tmp_pos.row += 2;
		break;

	case Direction_LEFT:
		tmp_pos.col -= 2;
		break;

	case Direction_RIGHT:
		tmp_pos.col += 2;
		break;
	}

	if (isValidMoveForPlayer(tmp_pos, gs.graphStruct, gs.turn, direction)) {
		//Move to place behind the opponent
		helper_movePlayer(gs, tmp_pos, direction, successors);
		return; //return since no sideways checking here
	}

	//Can't move behind the opponent, move sideways of opponent
	if (direction == Direction_DOWN || direction == Direction_UP) {
		helper_movePlayer(gs, tmp_pos, Direction_LEFT, successors);
		helper_movePlayer(gs, tmp_pos, Direction_RIGHT, successors);
	}

	if (direction == Direction_LEFT || direction == Direction_RIGHT) {
		helper_movePlayer(gs, tmp_pos, Direction_UP, successors);
		helper_movePlayer(gs, tmp_pos, Direction_DOWN, successors);
	}
}

void helper_movePlayer(GameState gs, Position old_pos, Direction direction,
		vector<GameState> & successors) {

	if (!isValidMoveForPlayer(old_pos, gs.graphStruct, gs.turn, direction)) {
		return;
	}

	if (isPosOccupiedByOtherPlayer(gs, old_pos, direction)) {
		playerBehindHandler(gs, old_pos, direction, successors);
		return;
	}

	else {
		GameState new_GS = genChild_gameState(gs);
		Position new_pos = getNewPositionInDirection(old_pos, direction);
		new_GS.players[gs.turn].position = new_pos;
		new_GS.moveTakenToReach.moveType = MoveType_PLAYER;
		new_GS.moveTakenToReach.position = new_pos;
		new_GS.graphStruct.graph[new_pos.row][new_pos.col] = playerNum_to_ObjectType(
				gs.turn); //new position of player
		new_GS.graphStruct.graph[gs.players[gs.turn].position.row][gs.players[gs.turn].position.col]
				= ObjectType_EMPTY; //the previous position is of-course empty

		successors.push_back(new_GS);
	}
}

void helper_placeWall(GameState gs, vector<GameState> & successors,
		WallType wallType, Position wall_pos) {

	if (!isValidPositionForWall(wall_pos, gs, wallType)) {
		return;
	}

	GameState new_gs = genChild_gameState(gs);

	if (wallType == WallType_H) {
		new_gs.graphStruct.graph[wall_pos.row][wall_pos.col] = ObjectType_WALL_H;
		new_gs.moveTakenToReach.wallType = WallType_H;
	} else {
		new_gs.graphStruct.graph[wall_pos.row][wall_pos.col] = ObjectType_WALL_V;
		new_gs.moveTakenToReach.wallType = WallType_V;
	}

	new_gs.moveTakenToReach.moveType = MoveType_PLACE_WALL;
	new_gs.moveTakenToReach.position = wall_pos;

	new_gs.players[gs.turn].wallsRemaining -= 1;

	successors.push_back(new_gs);
}

vector<GameState> generateSuccessors(GameState gs) {
	vector<GameState> successors;

	Position old_pos = gs.players[gs.turn].position;

	bool haveCurrentTurnWon = haveThePlayerWon(gs, old_pos, gs.turn);

	if (!haveCurrentTurnWon) {
		helper_movePlayer(gs, old_pos, Direction_UP, successors);
		helper_movePlayer(gs, old_pos, Direction_DOWN, successors);
		helper_movePlayer(gs, old_pos, Direction_LEFT, successors);
		helper_movePlayer(gs, old_pos, Direction_RIGHT, successors);
	}

	if (gs.players[gs.turn].wallsRemaining == 0) {
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

GameState alpha_beta(GameState node, Utility alpha, Utility beta, Weights w) {

	if (node.level == CUT_OFF) {
		node.utility = utility(node, w);
		return node;
	}

	if (node.nodeType == NodeType_MAX_NODE) {
		vector<GameState> successors = generateSuccessors(node);

		for (vector<GameState>::iterator it = successors.begin(); it
				!= successors.end(); it++) {
			GameState tempGS = alpha_beta(*it, alpha, beta, w);

			if (alpha.utilityVal < tempGS.utility.utilityVal) {
				alpha = tempGS.utility;
				node.moveToBeTaken = tempGS.moveTakenToReach;
			}

			if (alpha.utilityVal >= beta.utilityVal) {
				//cout << "-----------PRUNED MAX_NODE----------" << endl;
				node.utility = beta;
				return node;
			}

		}
		node.utility = alpha;
		return node;
	}

	else { //MIN_NODE
		vector<GameState> successors = generateSuccessors(node);

		for (vector<GameState>::iterator it = successors.begin(); it
				!= successors.end(); it++) {
			GameState tempGS = alpha_beta(*it, alpha, beta, w);

			if (beta.utilityVal > tempGS.utility.utilityVal) {
				beta = tempGS.utility;
				node.moveToBeTaken = tempGS.moveTakenToReach;
			}

			if (alpha.utilityVal >= beta.utilityVal) {
				//cout << "-----------PRUNED MIN_NODE----------" << endl;
				node.utility = alpha;
				return node;
			}

		}
		node.utility = beta;
		return node;
	}
}

GameState getMeMove(GameState gs) {
	gs.turn = whoAmI;

	gs.level = 0;

	gs.moveTakenToReach.moveType = MoveType_NONE;
	gs.moveTakenToReach.wallType = WallType_None;
	gs.moveTakenToReach.position.row = 0;
	gs.moveTakenToReach.position.col = 0;

	gs.moveToBeTaken.moveType = MoveType_NONE;
	gs.moveToBeTaken.wallType = WallType_None;
	gs.moveToBeTaken.position.row = 0;
	gs.moveToBeTaken.position.col = 0;

	gs.utility.utilityVal = MINUS_INFINITY_THAKKAR;

	Utility alpha;
	alpha.utilityVal = MINUS_INFINITY_THAKKAR;
	alpha.moves_diff = 0;
	alpha.walls_diff = 0;

	Utility beta;
	beta.utilityVal = INFINITY_THAKKAR;
	beta.moves_diff = 0;
	beta.walls_diff = 0;

	//I am just a step away from the destination
	if (whoAmI == PlayerNum_P1 && gs.players[whoAmI].position.row
			== CURRENT_GAME_MAX_POSITION.row - 4 && isValidMoveForPlayer(
			gs.players[whoAmI].position, gs.graphStruct, gs.turn, Direction_DOWN)) {
		Move move;
		move.moveType = MoveType_PLAYER;
		move.position = getNewPositionInDirection(gs.players[whoAmI].position,
				Direction_DOWN);
		gs.moveToBeTaken = move;
		return gs;
	}

	if (whoAmI == PlayerNum_P2 && gs.players[whoAmI].position.row == 3
			&& isValidMoveForPlayer(gs.players[whoAmI].position, gs.graphStruct,
					gs.turn, Direction_UP)) {
		Move move;
		move.moveType = MoveType_PLAYER;
		move.position = getNewPositionInDirection(gs.players[whoAmI].position,
				Direction_UP);
		gs.moveToBeTaken = move;
		return gs;
	}

	if (!IS_TRAINING_MODE) {
		gs = alpha_beta(gs, alpha, beta, Wts_final);
	}

	else {
		if (whoAmI == PlayerNum_P2) { //player2 is static (not changing wts)
			gs = alpha_beta(gs, alpha, beta, Wts_final);
		}

		else { //player1 is dynamic (change weights)
			Utility myUtility = utility(gs, Wts_changing);
			gs = alpha_beta(gs, alpha, beta, Wts_changing);

			int moves_diff_diff = gs.utility.moves_diff - myUtility.moves_diff;
			int walls_diff_diff = gs.utility.walls_diff - myUtility.walls_diff;

			double denominator = abs(moves_diff_diff) + abs(walls_diff_diff);

			if (denominator == 0)
				return gs;

			Wts_changing.a_0 += moves_diff_diff / denominator;
			Wts_changing.a_1 += walls_diff_diff / denominator;

			cout << "wts changed --- " << endl;
			cout << "a_0: " << Wts_changing.a_0 << endl;
			cout << "a_1: " << Wts_changing.a_1 << endl;
		}
	}

	return gs;
}

GameState generateStartGameState(int maxWalls) {
	GameState startGS;

	if (whoAmI == PlayerNum_P1) {
		startGS.nodeType = NodeType_MAX_NODE;
		startGS.turn = PlayerNum_P1;
	} else {
		startGS.nodeType = NodeType_MIN_NODE;
		startGS.turn = PlayerNum_P2;
	}

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

	for (int i = 0; i < CURRENT_GAME_MAX_POSITION.row; i++) {
		for (int j = 0; j < CURRENT_GAME_MAX_POSITION.col; j++) {
			startGS.graphStruct.graph[i][j] = ObjectType_EMPTY;
		}
	}

	startGS.graphStruct.graph[p1.position.row][p1.position.col] = ObjectType_PLAYER1;
	startGS.graphStruct.graph[p2.position.row][p2.position.col] = ObjectType_PLAYER2;

	return startGS;
}

#endif	/* HELPER_H */
