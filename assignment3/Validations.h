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


bool isValidPositionForPlayer(Position pos, ObjectType graph[][MAX_COL]){
    if(pos.x %2 !=0 || pos.y %2 !=0){ //player can only be at even positions
        return false;
    }
    
    if(pos.x > CURRENT_GAME_MAX_POSITION.x || pos.y > CURRENT_GAME_MAX_POSITION.y){
        return false;
    }
    
    if(graph[pos.x][pos.y])
    
    return true;
}

bool canMoveUp(Position pos, Graph g) {
    Position p_up;
    p_up.x = pos.x-2;
    p_up.y = pos.y;
    return isValidPositionForPlayer(p_up,g);
}

bool canMoveDown(Position pos, Graph g) {
    Position p_up;
    p_up.x = pos.x+2;
    p_up.y = pos.y;
    return isValidPositionForPlayer(p_up,g);
}

bool canMoveRight(Position pos, Graph g) {
    Position p_up;
    p_up.x = pos.x;
    p_up.y = pos.y+2;
    return isValidPositionForPlayer(p_up,g);
}

bool canMoveLeft(Position pos, Graph g) {
    Position p_up;
    p_up.x = pos.x;
    p_up.y = pos.y-2;
    return isValidPositionForPlayer(p_up,g);
}

bool isGoalPosition(Player p) {
    if (p.playerNumber == PlayerNum_P1)
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

//a_star specific
bool nodeGoalPosition(Node n, PlayerNum p_no) {
    if (p_no == PlayerNum_P1)
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

