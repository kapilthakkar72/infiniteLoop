#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <bits/stdc++.h>

#include "Structures.h"
#include "GlobalVariables.h"
#include "Helper.h"

using namespace std;

int N, M, K, time_left, player;
map<string, int> map_to_check_oscillations;

bool checkIsOscillating(Move move) {
	//logic to avoid oscillations--start

	if (move.position.row == 0 && move.position.col == 0) {//this takes care of default scenario
		return false;
	}

	string pos_key = getMePositionKey(move.position);

	map<string, int>::iterator it = map_to_check_oscillations.find(pos_key);
	if (it != map_to_check_oscillations.end()) {
		//element found;
		if (it->second == MAX_TIMES_OSCILLATING) {
			//we are reaching to a position for the MAX_TIMES_OSCILLATING time & map has not changed
			/*map_to_check_oscillations.clear();
			 oscillating_position_not_take = move.position;
			 cout << "got a oscillating position.." << move.position.row << ","
			 << move.position.col << endl;
			 return true;*/
			map_to_check_oscillations.clear();
		}

		else {
			// cout << "it->second" << it->second << endl; //TODO: remo
			map_to_check_oscillations[pos_key] = it->second + 1;
			//cout << "visiting " << pos_key << " the second time" << endl; //TODO: remove
		}

		cout << "visiting " << pos_key << " the second time" << endl;
		return true;
	}

	else { //position not found in the map
		map_to_check_oscillations[pos_key] = 1;
		//cout << "added " << pos_key << " to the map" << endl; //TODO: remove
		//cout << "map size:" << map_to_check_oscillations.size() << endl;//TODO: remove
	}

	return false;
}

Move AI_processing(GameState &curr_GS, int & m) {
	curr_GS = getMeMove(curr_GS);
	Move move = curr_GS.moveToBeTaken;

	move.isValid = true;

	if (checkIsOscillating(move)) {
		//move.isValid = false;

		bool found_random_fine = false;
		while (!found_random_fine) {
			srand(time(NULL));
			int randomVal = (rand() % 4);

			switch (randomVal) {
			case 0:
				if (isValidMoveForPlayer(curr_GS.players[whoAmI].position,
						curr_GS.graphStruct, whoAmI, Direction_UP)) {

					Position new_pos = getNewPositionInDirection(
							curr_GS.players[whoAmI].position, Direction_UP);
					//Move tmp_mov;
					move.position = new_pos;
					//tmp_mov.isValid = true;
					move.moveType = MoveType_PLAYER;
					if (!checkIsOscillating(move)) {
						map_to_check_oscillations.clear();
						string pos_key = getMePositionKey(move.position);
						map_to_check_oscillations[pos_key] = 1;
						cout << "found a random valid move :"
								<< move.position.row << ","
								<< move.position.col << endl;
						found_random_fine = true;
					}
				}
				break;

			case 1:
				if (isValidMoveForPlayer(curr_GS.players[whoAmI].position,
						curr_GS.graphStruct, whoAmI, Direction_DOWN)) {

					Position new_pos = getNewPositionInDirection(
							curr_GS.players[whoAmI].position, Direction_DOWN);
					//Move tmp_mov;
					move.position = new_pos;
					//tmp_mov.isValid = true;
					move.moveType = MoveType_PLAYER;
					if (!checkIsOscillating(move)) {
						map_to_check_oscillations.clear();
						string pos_key = getMePositionKey(move.position);
						map_to_check_oscillations[pos_key] = 1;
						cout << "found a random valid move :"
								<< move.position.row << ","
								<< move.position.col << endl;
						found_random_fine = true;
					}
				}
				break;

			case 2:
				if (isValidMoveForPlayer(curr_GS.players[whoAmI].position,
						curr_GS.graphStruct, whoAmI, Direction_RIGHT)) {

					Position new_pos = getNewPositionInDirection(
							curr_GS.players[whoAmI].position, Direction_RIGHT);
					//Move tmp_mov;
					move.position = new_pos;
					//tmp_mov.isValid = true;
					move.moveType = MoveType_PLAYER;
					if (!checkIsOscillating(move)) {
						map_to_check_oscillations.clear();
						string pos_key = getMePositionKey(move.position);
						map_to_check_oscillations[pos_key] = 1;
						cout << "found a random valid move :"
								<< move.position.row << ","
								<< move.position.col << endl;
						found_random_fine = true;
					}
				}
				break;

			case 3:
				if (isValidMoveForPlayer(curr_GS.players[whoAmI].position,
						curr_GS.graphStruct, whoAmI, Direction_LEFT)) {

					Position new_pos = getNewPositionInDirection(
							curr_GS.players[whoAmI].position, Direction_LEFT);
					//Move tmp_mov;
					move.position = new_pos;
					//tmp_mov.isValid = true;
					move.moveType = MoveType_PLAYER;
					if (!checkIsOscillating(move)) {
						map_to_check_oscillations.clear();
						string pos_key = getMePositionKey(move.position);
						map_to_check_oscillations[pos_key] = 1;
						cout << "found a random valid move :"
								<< move.position.row << ","
								<< move.position.col << endl;
						found_random_fine = true;
					}
				}
				break;
			}

		}
	}

	if (move.moveType == MoveType_PLAYER) {
		m = 0;
		curr_GS.graphStruct.graph[curr_GS.players[whoAmI].position.row][curr_GS.players[whoAmI].position.col]
				= ObjectType_EMPTY;
		curr_GS.graphStruct.graph[move.position.row][move.position.col]
				= playerNum_to_ObjectType(whoAmI);
		curr_GS.players[whoAmI].position = move.position;
	}

	else if (move.wallType == WallType_H) {
		m = 1;
		curr_GS.players[whoAmI].wallsRemaining -= 1;
		curr_GS.graphStruct.graph[move.position.row][move.position.col]
				= ObjectType_WALL_H;
		map_to_check_oscillations.clear();//clearing the map since I am changing the state now
	}

	else if (move.wallType == WallType_V) {
		m = 2;
		curr_GS.players[whoAmI].wallsRemaining -= 1;
		curr_GS.graphStruct.graph[move.position.row][move.position.col]
				= ObjectType_WALL_V;
		map_to_check_oscillations.clear();//clearing the map since I am changing the state now
	}

	else {
		curr_GS.turn = whoAmI;

		if (HAVE_I_WON) {
			cout << "--pass---" << endl;
			m = 0;
		}

		else {
			DO_I_HAVE_OPTION = false;
			return AI_processing(curr_GS, m);
		}
	}

	return move;
}

int main(int argc, char *argv[]) {
	cout << "Starting the InfiniteLoop...." << endl;

	srand(time(NULL));
	int sockfd = 0, n = 0;
	char recvBuff[1024];
	char sendBuff[1025];
	struct sockaddr_in serv_addr;

	if (argc != 4) {
		printf("\n Usage: %s <ip of server> <port no> \n", argv[0]);
		return 1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error : Could not create socket \n");
		return 1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	//----Our Code Start---
	bool isAI = atoi(argv[3]);
	//----Our Code End---

	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
		printf("\n inet_pton error occured\n");
		return 1;
	}

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\n Error : Connect Failed \n");
		return 1;
	}

	cout << "Quoridor will start..." << endl;

	memset(recvBuff, '0', sizeof(recvBuff));
	n = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
	recvBuff[n] = 0;
	sscanf(recvBuff, "%d %d %d %d %d", &player, &N, &M, &K, &time_left);

	cout << "Player " << player << endl;
	cout << "Time " << time_left << endl;
	cout << "Board size " << N << "x" << M << " :" << K << endl;

	//------Our Code Start----

	//Setting game specific max position
	CURRENT_GAME_MAX_POSITION.row = N * 2 + 1;
	CURRENT_GAME_MAX_POSITION.col = M * 2 + 1;

	if (player == 1) {
		whoAmI = PlayerNum_P1;
		opponent = PlayerNum_P2;
		CUT_OFF = CUTOFF_LEVEL_P1;

	} else {
		whoAmI = PlayerNum_P2;
		opponent = PlayerNum_P1;
		CUT_OFF = CUTOFF_LEVEL_P2;
	}

	timeLeft = time_left;

	Wts_final.a_0 = WTS_FINAL_A0;
	Wts_final.a_1 = WTS_FINAL_A1;

	Wts_changing.a_0 = WTS_CHANGING_A0;
	Wts_changing.a_1 = WTS_CHANGING_A1;

	GameState curr_GS = generateStartGameState(K);

	DO_I_HAVE_OPTION = true;
	IS_FAST_MODE = IS_FAST_MODE_DEFAULT;

	HAVE_OPPONENT_WON = false;
	HAVE_I_WON = false;
	//------Our Code End----

	float TL;
	int om, oro, oc;
	int m, r, c;
	int d = 3;
	//char s[100];
	int x = 1;
	if (player == 1) {

		//----Our Code Start---
		if (isAI || IS_TRAINING_MODE) {
			curr_GS = getMeMove(curr_GS);
			Move move = curr_GS.moveToBeTaken;

			if (move.moveType == MoveType_PLAYER) {
				m = 0;
				curr_GS.graphStruct.graph[curr_GS.players[whoAmI].position.row][curr_GS.players[whoAmI].position.col]
						= ObjectType_EMPTY;
				curr_GS.graphStruct.graph[move.position.row][move.position.col]
						= ObjectType_PLAYER1;
				curr_GS.players[whoAmI].position = move.position;
			}

			else if (move.wallType == WallType_H) {
				curr_GS.graphStruct.graph[move.position.row][move.position.col]
						= ObjectType_WALL_H;
				curr_GS.players[opponent].wallsRemaining -= 1;
				m = 1;
			}

			else if (move.wallType == WallType_V) {
				curr_GS.graphStruct.graph[move.position.row][move.position.col]
						= ObjectType_WALL_V;
				curr_GS.players[whoAmI].wallsRemaining -= 1;
				m = 2;
			}

			r = move.position.row / 2 + 1;
			c = move.position.col / 2 + 1;

			/*cout << "sending move: " << m << ": " << move.position.row << ","
			 << move.position.col << endl;*/
		} else {
			cin >> m >> r >> c;
		}
		//-----Our Code End---

		memset(sendBuff, '0', sizeof(sendBuff));
		string temp;
		//cin >> m >> r >> c;

		snprintf(sendBuff, sizeof(sendBuff), "%d %d %d", m, r, c);
		write(sockfd, sendBuff, strlen(sendBuff));

		memset(recvBuff, '0', sizeof(recvBuff));
		n = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
		recvBuff[n] = 0;
		sscanf(recvBuff, "%f %d", &TL, &d);
		//cout << TL << " " << d << endl;
		if (d == 1) {
			cout << "You win!! Yayee!! :D ";
			x = 0;
		} else if (d == 2) {
			cout << "Loser :P ";
			x = 0;
		}
	}

	while (x) {
		memset(recvBuff, '0', sizeof(recvBuff));
		n = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
		recvBuff[n] = 0;
		sscanf(recvBuff, "%d %d %d %d", &om, &oro, &oc, &d);
		//cout << om << " " << oro << " " << oc << " " << d << endl;

		//----Our Code Start---

		if (!HAVE_OPPONENT_WON) {
			HAVE_OPPONENT_WON = haveTheOpponentWon(curr_GS);
			if (HAVE_OPPONENT_WON)
				cout << ":( :( :( ... OPPONENT WON .... :( :( :(" << endl;
		}

		if (!HAVE_I_WON) {
			HAVE_I_WON = haveIWon(curr_GS);
			if (HAVE_I_WON)
				cout << ":) :) :) ... I WON .... :) :) :)" << endl;
		}

		if (om == 0 && !HAVE_OPPONENT_WON) {
			curr_GS.graphStruct.graph[curr_GS.players[opponent].position.row][curr_GS.players[opponent].position.col]
					= ObjectType_EMPTY;

			curr_GS.players[opponent].position.row = oro * 2 - 1;
			curr_GS.players[opponent].position.col = oc * 2 - 1;

			curr_GS.graphStruct.graph[curr_GS.players[opponent].position.row][curr_GS.players[opponent].position.col]
					= playerNum_to_ObjectType(opponent);

			cout << "opponent moved to: " << oro * 2 - 1 << "," << oc * 2 - 1
					<< endl;
		}

		else if (om == 1) {
			curr_GS.graphStruct.graph[oro * 2 - 2][oc * 2 - 2]
					= ObjectType_WALL_H;
			curr_GS.players[opponent].wallsRemaining -= 1;
			map_to_check_oscillations.clear();//clearing the map since opponent has placed a wall
		}

		else if (om == 2) {
			curr_GS.graphStruct.graph[oro * 2 - 2][oc * 2 - 2]
					= ObjectType_WALL_V;
			curr_GS.players[opponent].wallsRemaining -= 1;
			map_to_check_oscillations.clear();//clearing the map since opponent has placed a wall
		}

		//---Our Code End---


		if (d == 1) {
			cout << "You win!! Yayee!! :D ";
			break;
		} else if (d == 2) {
			cout << "Loser :P ";
			break;
		}
		memset(sendBuff, '0', sizeof(sendBuff));
		string temp;

		//----Our Code Start---
		if (isAI || IS_TRAINING_MODE) {
			bool have_I_got_a_valid_move = false;

			DO_I_HAVE_OPTION = true;

			Move move;
			while (!have_I_got_a_valid_move) {
				have_I_got_a_valid_move = true;

				move = AI_processing(curr_GS, m);

				if (!move.isValid) {
					have_I_got_a_valid_move = false;
					continue;
				}

				r = move.position.row / 2 + 1;
				c = move.position.col / 2 + 1;

				if (move.position.row == 0 && move.position.col == 0) {
					r = 0;
					c = 0;
				}
			}

			//resetting the oscillating position
			oscillating_position_not_take.row = 0;
			oscillating_position_not_take.col = 0;

			cout << "sending move: " << m << ": " << move.position.row << ","
					<< move.position.col << endl;
		}

		else {
			cin >> m >> r >> c;
		}
		//-----Our Code End---


		//cin >> m >> r >> c;
		snprintf(sendBuff, sizeof(sendBuff), "%d %d %d", m, r, c);
		write(sockfd, sendBuff, strlen(sendBuff));

		memset(recvBuff, '0', sizeof(recvBuff));
		n = read(sockfd, recvBuff, sizeof(recvBuff) - 1);
		recvBuff[n] = 0;
		sscanf(recvBuff, "%f %d", &TL, &d);//d=3 indicates game continues.. d=2 indicates lost game, d=1 means game won.
		//cout << TL << " " << d << endl;
		if (d == 1) {
			cout << "You win!! Yayee!! :D ";
			break;
		} else if (d == 2) {
			cout << "Loser :P ";
			break;
		}
	}
	cout << endl << "The End" << endl;
	return 0;
}

