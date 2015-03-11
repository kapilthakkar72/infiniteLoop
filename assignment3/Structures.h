/* 
 * File:   Structures.h
 * Author: kapil
 *
 * Created on 11 March, 2015, 8:07 PM
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

#include<stdio.h>
#include<vector>

#define MAX_ROW 9
#define MAX_COLUMN 9

using namespace std;

struct Player
{
    int x;
    int y;
    int wallsRemaining;
    int playerNumber;
};

struct GameState
{
    Player player1;
    Player player2;
    int turn;
    double alpha;
    double beta;
    Graph graph;
    GameState parent;
    int count; // To keep track of number of moves
    vector<GameState> children;
};

enum ObjectType
{
    WALL, PLAYER1, PLAYER2, EMPTY
};

struct Graph
{
    ObjectType graph[MAX_ROW*2 +1 ][MAX_COLUMN*2 +1];
};



#endif	/* STRUCTURES_H */

