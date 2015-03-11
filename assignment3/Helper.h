/* 
 * File:   Helper.h
 * Author: kapil
 *
 * Created on 11 March, 2015, 8:14 PM
 */

#ifndef HELPER_H
#define	HELPER_H

#include "Structures.h"

bool isValidMoveForPlayer(GameState g, int x, int y)
{
    if(g.graph[x][y]==ObjectType.WALL)
        return false;
    else
        return true;
}

bool isGoalPosition(Player p)
{
    if(p.playerNumber == 1)
        if(p.x == 2)
            return true;
        else 
            return false;
    else
        if(p.x == MAX_ROW*2 )
            return true;
        else
            return false;
}

int getNoOfMoves(GameState g,int player)
{
    
    return 0;   
}

double utility(GameState g)
{
    int p1walls = g.player1.wallsRemaining;
    int p2walls = g.player2.wallsRemaining;
    
    int walls = p1walls - p2walls;
    
    int noOfMoves1 = getNoOfMoves(g,1);
    int noOfMoves2 = getNoOfMoves(g,2);
    
    int moves = noOfMoves1 - noOfMoves2;
    
    return (a_0 * moves + a_1 * walls);
}

#endif	/* HELPER_H */

