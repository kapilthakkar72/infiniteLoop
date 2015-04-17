/* 
 * File:   GlobalVariables.h
 * Author: kt
 *
 * Created on March 11, 2015, 10:42 PM
 */

#ifndef GLOBALVARIABLES_H
#define	GLOBALVARIABLES_H

#include "Structures.h"

Weights Wts_final;
Weights Wts_changing;

Position CURRENT_GAME_MAX_POSITION; //initialized in the main
int CURRENT_GAME_MAX_WALLS;

PlayerNum whoAmI;
PlayerNum opponent;

int CUT_OFF;

double timeLeft;

bool DO_I_HAVE_OPTION;

bool IS_FAST_MODE;
bool IS_SUPER_FAST_MODE;

bool HAVE_OPPONENT_WON;
bool HAVE_I_WON;

bool DO_I_HAVE_WALLS_LEFT;

//used for walls
bool IS_FIRST_ALARM_RAISED;
bool IS_SECOND_ALARM_RAISED;

Position oscillating_position_not_take;

#endif	/* GLOBALVARIABLES_H */

