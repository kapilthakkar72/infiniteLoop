/* 
 * File:   main.cpp
 * Author: kapil
 *
 * Created on 11 March, 2015, 7:51 PM
 */

#include <cstdlib>
#include <iostream>

#include "GlobalVariables.h"
#include "Helper.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Starting the InfiniteLoop" << endl;
    
    int max_row = 9; //TODO: shall be taken from input
    int max_col = 9;
    
    //Setting game specific max position
    CURRENT_GAME_MAX_POSITION.x = max_row*2 +1;
    CURRENT_GAME_MAX_POSITION.y = max_col*2 +1;
    
    
    return 0;
}
