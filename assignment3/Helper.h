/* 
 * File:   Helper.h
 * Author: kapil
 *
 * Created on 11 March, 2015, 8:14 PM
 */

#ifndef HELPER_H
#define	HELPER_H

#include "Structures.h"

// This is just used to define priority of queue

class CompareNodes {
public:

    bool operator()(const Node comp1, const Node comp2) const {
        return ((comp1.f) > (comp2.f));
    }
};

int isValidMoveForPlayer(GameState g, int x, int y) {
    if (g.graph[x][y] == ObjectType.WALL)
        return 0; // false : can not move
    else if (g.graph[x][y] == ObjectType.EMPTY)
        return 1; // can move 
    else if (g.graph[x][y] == ObjectType.PLAYER1 || g.graph[x][y] == ObjectType.PLAYER2)
        return 2; // make jump
}

bool isGoalPosition(Player p) {
    if (p.playerNumber == 1)
        if (p.position.x == 2)
            return true;
        else
            return false;
    else // player number 2
        if (p.position.x == MAX_ROW * 2)
        return true;
    else
        return false;
}

double getHeuristicValue(int playerNumber, Position currentPos) {
    if (playerNumber == 1) {
        // Player 1 will start from top and has to reach to end
        return (MAX_ROW * 2 - currentPos.x);
    } else // for player 2
    {
        // player 2 will start from bottom of the board and has to reach to top of the board
        return (currentPos.x - 2);
    }
}

bool nodeGoalPosition(Node n, int p_no) {
    if (p_no == 1)
        if (n.pos.x == 2)
            return true;
        else
            return false;
    else // player number 2
        if (n.pos.x == MAX_ROW * 2)
        return true;
    else
        return false;
}

bool canMoveUp(Node n, Graph g) {
    if (n.pos.x - 2 > 1 && !g.graph[n.pos.x - 1][n.pos.y] == ObjectType.WALL)
        return true;
    else
        return false;
}

bool canMoveDown(Node n, Graph g) {
    if (n.pos.x + 2 <= MAX_ROW * 2 && !g.graph[n.pos.x + 1][n.pos.y] == ObjectType.WALL)
        return true;
    else
        return false;
}

bool canMoveRight(Node n, Graph g) {
    if (n.pos.y + 2 <= MAX_COLUMN * 2 && !g.graph[n.pos.x][n.pos.y + 1] == ObjectType.WALL)
        return true;
    else
        return false;
}

bool canMoveLeft(Node n, Graph g) {
    if (n.pos.y - 2 > 1 && !g.graph[n.pos.x][n.pos.y - 1] == ObjectType.WALL)
        return true;
    else
        return false;
}

bool presentInClosed(Node n, vector<Node> &closed) {
    for (vector<Node>::iterator it = closed.begin(); it != closed.end(); it++) {
        Node currentNode = *it;
        if (currentNode.pos.x == n.pos.x && currentNode.pos.y == n.pos.y) {
            return true;
        }
    }
    return false;
}

// will return true if path exist, else will return false
// path will be stored in the vector passed as argument 

int a_star(Graph g, Player p) {

    int playerNumber = p.playerNumber;
    priority_queue<Node, vector<Node>, CompareNodes> openList;

    vector<Node> closeList;

    Node n;
    n.g = 0;
    n.pos.x = p.position.x;
    n.pos.y = p.position.y;
    n.f = getHeuristicValue(playerNumber, n.pos);
    n.numberOfSteps = 0;
    n.parent = NULL;

    queue.push(n);

    Node currentNode;

    while (!openList.empty()) {
        // Take out first Node of the queue
        currentNode = openList.top();
        openList.pop();

        if (nodeGoalPosition(currentNode, playerNumber)) {
            // reached to end... stop
            break;
        }

        if (presentInClosed(currentNode, closeList))
            continue;

        // put currentNode in the closed list
        closeList.push_back(currentNode);

        if (canMoveUp(currentNode, g)) {
            Node temp;
            temp.pos.x = currentNode.pos.x - 2;
            temp.pos.y = currentNode.pos.y;
            temp.g = currentNode.g + 1;
            temp.f = temp.g + getHeuristicValue(playerNumber, temp.pos);
            temp.parent = currentNode;
            temp.numberOfSteps = currentNode.numberOfSteps + 1;
            openList.push(temp);
        }

        if (canMoveDown(currentNode, g)) {
            Node temp;
            temp.pos.x = currentNode.pos.x + 2;
            temp.pos.y = currentNode.pos.y;
            temp.g = currentNode.g + 1;
            temp.f = temp.g + getHeuristicValue(playerNumber, temp.pos);
            temp.parent = currentNode;
            temp.numberOfSteps = currentNode.numberOfSteps + 1;
            openList.push(temp);
        }

        if (canMoveLeft(currentNode, g)) {
            Node temp;
            temp.pos.x = currentNode.pos.x;
            temp.pos.y = currentNode.pos.y - 2;
            temp.g = currentNode.g + 1;
            temp.f = temp.g + getHeuristicValue(playerNumber, temp.pos);
            temp.parent = currentNode;
            temp.numberOfSteps = currentNode.numberOfSteps + 1;
            openList.push(temp);
        }

        if (canMoveRight(currentNode, g)) {
            Node temp;
            temp.pos.x = currentNode.pos.x;
            temp.pos.y = currentNode.pos.y + 2;
            temp.g = currentNode.g + 1;
            temp.f = temp.g + getHeuristicValue(playerNumber, temp.pos);
            temp.parent = currentNode;
            temp.numberOfSteps = currentNode.numberOfSteps + 1;
            openList.push(temp);
        }

    }
    if (openList.empty() || !nodeGoalPosition(currentNode, playerNumber)) {
        //path = NULL;
        return -1;
    } else {
        return currentNode.numberOfSteps;
    }

}

bool doesPathExist(Graph g, int playerNo) {

    return true;
}

int getNoOfMoves(GameState g, int player) {

    return 0;
}

double utility(GameState g, Weights w) {
    int p1walls = g.player1.wallsRemaining;
    int p2walls = g.player2.wallsRemaining;

    int walls = p1walls - p2walls;

    int noOfMoves1 = getNoOfMoves(g, 1);
    int noOfMoves2 = getNoOfMoves(g, 2);

    int moves = noOfMoves1 - noOfMoves2;

    return (w.a_0 * moves + w.a_1 * walls);
}

#endif	/* HELPER_H */

