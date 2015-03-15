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

PlayerNum whoAmI;
PlayerNum opponent;

int CUT_OFF;

double timeLeft;

bool DO_I_HAVE_OPTION;

#endif	/* GLOBALVARIABLES_H */
