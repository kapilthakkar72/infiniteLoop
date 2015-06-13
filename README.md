# infiniteLoop - Quoridor

* A generic implementation of Quoridor, can be played on any board size & for any specified time limit (decided by the server) <br>

* We have included 3 servers with 9X9, 11X11 & 13X13 configurations <br>

* We have used alpha-beta pruning in min-max tree to generate next step/move. <br>

* At the terminal node, we have used eval function, where we are considering difference in
number of steps and difference between number of walls as follows: <br>

<i> Eval = (SR((P2) - SR((P1) ) + 1.1 * (WR(P1) - WR(P2))</i> <br>
Where, <br>
P1 : Player 1, P2: Player 2, SR: steps remaining and WR: Walls remaining<br>
P1 will always try to maximize this eval value & P2 will always try to minimize this eval value <br>

* The branching factor is dynamic, decided based on the games current situation, & the time left.
The 4 moving positions (Up, Down, Left, Right) are anyways considered. We take the walls position as the positions around the opponent & around the already placed walls. <br><br>

* We are checking upto 4 ply for Player 1 and up to 5 ply for Player 2 at the start of the game. When time left for the game is very less then we are reducing the number of ply by 2 for each player. <br>

* All the parameters are easily configurable, check constants.h & Global Variables.h <br>

* We even implemented RUSH move & REED openings, though could not find it of much use, thus skipped using it in the code. In case needed, they can be used again by simply setting a couple of boolean variables to true. <br>

* It even include a training mode to learn the parameters of the “Eval” function, however we could not find it useful. It may need a minor change. Thus, for now we have fixed the parameters. <br>

* The project is made on eclipse-cpp & thus can be easily imported to eclipse-cpp. <br>

* We have included few bots (thanks to friends for the help) for testing, please see bots folder.
<br><br>

<b> Running Quoridor: </b>

Compile the code using compile.sh as “./compile.sh” <br>
Run the server as “python TkBoard.py”<br>
Run the client as “./client <serverIp> <portNo.> 1/0” (1 for AI mode, 0 for human mode) <br><br>
Obviously you need to run two clients for the game to begin <br>
</t>You can use the same client (AI/Human mode) <br>
</t>or use any client from the bots folder  <br><br>


<b>Moves:</b>

Sending Move: MoveType row col <br>
MoveType: 0 for moving the pawn, 1 for horizontal wall, 2 for vertical wall

