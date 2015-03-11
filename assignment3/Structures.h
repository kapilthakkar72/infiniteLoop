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

struct Node
{
    Position pos;
    //f(n) = g(n) + h(n)
    double f; 
    double g;
    int numberOfSteps;
    Node parent;    
};

struct Position
{
    int x;
    int y;
};

struct Player
{
    Position position;
    int wallsRemaining;
    int playerNumber;
};

struct Weights
{
    double a_0; // weight for moves
    double a_1; // weight for walls
};

enum MoveType
{
    Move_Player, PlaceWall
    
};

struct Move
{
    MoveType moveType;
    Position position;
};

enum NodeType
{
    MIN_NODE, MAX_NODE
};

struct GameState
{
    Player player1;
    Player player2;
    int turn;
    double alpha;
    double beta;
    Graph graph;
    Move move;
    GameState parent;
    int count; // To keep track of number of moves
    NodeType nodeType;
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

