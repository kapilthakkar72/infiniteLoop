# infiniteLoop - A “generic” CPP implementation of Quoridor

* A generic implementation of Quoridor, can be played on any board size & for any specified time limit (decided by the server) <br>

* We have included 3 servers  with 9X9. 11X11 & 13X13 configurations <br>

* We have used alpha-beta pruning in min-max tree to generate next step/move. <br>

* At the terminal node, we have used eval function, where we are considering difference in
number of steps and difference between number of walls as follows: <br>

Eval = (NoOfSteps((P2) - NoOfSteps((P1) ) + 1.1 * (wallsRemaining(P1) - wallsRemaining(P2))
Where, <br>
P1 : Player 1 and P2: Player 2 <br>
Player 1 will always try to maximize this eval value and Player 2 will always try to minimize this eval value <br><br>

* The branching factor is dynamic, decided based on the games current situation, & the time left.
The 4 moving positions (Up, Down, Left, Right) are anyways considered. We take the walls position as the positions around the opponent & around the already placed walls. <br><br>

* We are checking upto 4 ply for Player 1 and up to 5 ply for Player 2 at the start of the game. When time left for the game is very less then we are reducing the number of ply by 2 for each player. <br><br>

* All the parameters are easily configurable, check constants.h & Global Variables.h <br><br>

* We even implemented RUSH move & REED openings, though could not find it of much use, thus skipped using it in the code. In case needed, they can be used again by simply setting a couple of boolean variables to true. <br><br>

* It even include a training mode to learn the parameters of the “Eval” function, however we could not find it useful. It may need a minor change. Thus, for now we have fixed the parameters. <br><br>

* The project is made on eclipse-cpp & thus can be easily imported to eclipse-cpp. <br><br>

* We have included few bots (thanks to our friends) for testing, please see bots folder.


Running Quoridor:

Compile the code using compile.sh as “./compile.sh”
Run the server as “python TkBoard.py”
Run the client as “./client <serverIp> <portNo.> 1/0” (1 for AI mode, 0 for human mode)
Obviously you need to run two clients for the game to begin
You can use the same client (AI/Human mode)
or use any client from the bots folder 


Moves:

Sending Move: MoveType row col
MoveType: 0 for moving the pawn, 1 for horizontal wall, 2 for vertical wall

