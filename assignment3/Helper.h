/* 
 * File:   Helper.h
 * Author: kapil
 *
 * Created on 11 March, 2015, 8:14 PM
 */

#ifndef HELPER_H
#define	HELPER_H

#include "Structures.h"


int isValidMoveForPlayer(GameState g, int x, int y)
{
    if(g.graph[x][y]==ObjectType.WALL)
        return 0;  // false : can not move
    else if(g.graph[x][y] == ObjectType.EMPTY)
        return 1; // can move 
    else if(g.graph[x][y] == ObjectType.PLAYER1 || g.graph[x][y] == ObjectType.PLAYER2)
        return 2; // make jump
}

bool isGoalPosition(Player p)
{
    if(p.playerNumber == 1)
        if(p.position.x == 2)
            return true;
        else 
            return false;
    else // player number 2
        if(p.position.x == MAX_ROW*2 )
            return true;
        else
            return false;
}

double getHeuristicValue(Player p,Position currentPos)
{
    if(p.playerNumber == 1)
    {
        return 
    }
    else
    {
        
    }
}

void a_star(Graph g, Player p)
{
    Position initial_position = p.position;
    
    priority_queue<Node> queue;
    
    Node n;
    n.g=0;
    
    
}

bool doesPathExist(Graph g, int playerNo)
{
    
    return true;
}

int getNoOfMoves(GameState g,int player)
{
    
    return 0;   
}

double utility(GameState g, Weights w)
{
    int p1walls = g.player1.wallsRemaining;
    int p2walls = g.player2.wallsRemaining;
    
    int walls = p1walls - p2walls;
    
    int noOfMoves1 = getNoOfMoves(g,1);
    int noOfMoves2 = getNoOfMoves(g,2);
    
    int moves = noOfMoves1 - noOfMoves2;
    
    return (w.a_0 * moves + w.a_1 * walls);
}

#endif	/* HELPER_H */

