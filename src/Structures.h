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
#include<queue>

#include "Constants.h"


using namespace std;

struct Position
{
    int x;
    int y;
};

struct Node
{
    Position pos;
    //f(n) = g(n) + h(n)
    double f; 
    double g;
    int numberOfSteps;
    Node *parent;    //TODO: discuss --- need to be a pointer
};

struct Player
{
    Position position;
    int wallsRemaining;
    PlayerNum playerNumber;
};

struct Weights
{
    double a_0; // weight for moves
    double a_1; // weight for walls
};

struct Move
{
    MoveType moveType;
    Position position;
};

struct Graph
{
    ObjectType graph[MAX_ROW*2 +1][MAX_COL*2 +1];
};

struct GameState
{
    Player player1;
    Player player2;
    
    Player turn; //refers to the object of the current player
    NodeType nodeType;
    
    double alpha;
    double beta;
    
    Graph graph;
    Move move;
    
    GameState *parent; //TODO: discuss --- need to be a pointer
    vector<GameState> children;
};

#endif	/* STRUCTURES_H */

