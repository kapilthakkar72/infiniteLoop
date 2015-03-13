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

bool isValidPositionForPlayer(Position pos, ObjectType graph[][MAX_COL]) {
    if (pos.x % 2 != 0 || pos.y % 2 != 0) //player can only be at even positions
        return false;

    if (pos.x > CURRENT_GAME_MAX_POSITION.x || pos.y > CURRENT_GAME_MAX_POSITION.y)
        return false;

    if (graph[pos.x][pos.y] == ObjectType_WALL)
        return false;

    return true;
}

bool isPosOccupiedByOtherPlayer(Player player, Position pos, ObjectType graph[][MAX_COL]) {
    if (player.playerNumber == PlayerNum_P1 && graph[pos.x][pos.y] == ObjectType.ObjectType_PLAYER2)
        return true;

    if (player.playerNumber == PlayerNum_P2 && graph[pos.x][pos.y] == ObjectType.ObjectType_PLAYER1)
        return true;

    return false;
}

bool canMoveToDirection(Position pos, Graph g, Direction direction){
    Position new_pos = getNewPositionInDirection(pos, direction);
    return isValidPositionForPlayer(new_pos, g);
}

bool isGoalPosition(Player p) {
    if (p.playerNumber == PlayerNum_P1)
        if (p.position.x == 2)
            return true;
        else
            return false;
    else // player number 2
        if (p.position.x == CURRENT_GAME_MAX_POSITION.x - 1)
        return true;
    else
        return false;
}

//a_star specific

bool nodeGoalPosition(Node n, PlayerNum p_no) {
    if (p_no == PlayerNum_P1)
        if (n.pos.x == 2)
            return true;
        else
            return false;
    else // player number 2
        if (n.pos.x == CURRENT_GAME_MAX_POSITION.x - 1)
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

