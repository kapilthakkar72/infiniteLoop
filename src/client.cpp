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
	PlayerNum opponent;

	//Setting game specific max position
	CURRENT_GAME_MAX_POSITION.x = N * 2 + 1;
	CURRENT_GAME_MAX_POSITION.y = M * 2 + 1;

	if (player == 1) {
		whoAmI = PlayerNum_P1;
		opponent = PlayerNum_P2;

	} else {
		whoAmI = PlayerNum_P2;
		opponent = PlayerNum_P1;
	}

	timeLeft = time_left;

	Wts_final.a_0 = 2; //TODO: may be modified later
	Wts_final.a_0 = 1;

	GameState curr_GS = generateStartGameState(K);

	//------Our Code End----

	float TL;
	int om, oro, oc;
	int m, r, c;
	int d = 3;
	//char s[100];
	int x = 1;
	if (player == 1) {

		//----Our Code Start---
		if (isAI) {
			Move move = getMeMove(curr_GS);

			if (move.moveType == MoveType_PLAYER) {
				m = 0;
				curr_GS.graph.graph[curr_GS.players[whoAmI].position.x][curr_GS.players[whoAmI].position.y]
						= ObjectType_EMPTY;
				curr_GS.graph.graph[move.position.x][move.position.y]
						= ObjectType_PLAYER1;
				curr_GS.players[whoAmI].position = move.position;
			}

			else if (move.wallType == WallType_H) {
				curr_GS.graph.graph[move.position.x][move.position.y]
						= ObjectType_WALL_H;
				curr_GS.players[opponent].wallsRemaining -= 1;
				m = 1;
			}

			else { //vertical wall
				curr_GS.graph.graph[move.position.x][move.position.y]
						= ObjectType_WALL_V;
				curr_GS.players[whoAmI].wallsRemaining -= 1;
				m = 2;
			}

			r = move.position.x / 2 + 1;
			c = move.position.y / 2 + 1;
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
		cout << TL << " " << d << endl;
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
		cout << om << " " << oro << " " << oc << " " << d << endl;

		//----Our Code Start---

		if (om == 0) {
			curr_GS.graph.graph[curr_GS.players[opponent].position.x][curr_GS.players[opponent].position.y]
					= ObjectType_EMPTY;

			curr_GS.players[opponent].position.x = oro * 2 - 1;
			curr_GS.players[opponent].position.y = oc * 2 - 1;

			curr_GS.graph.graph[curr_GS.players[opponent].position.x][curr_GS.players[opponent].position.y]
					= playerNum_to_ObjectType(opponent);

			cout << "opponent moved to: " << oro * 2 - 1 << "," << oc * 2 - 1
					<< endl;
		}

		else if (om == 1) {
			curr_GS.graph.graph[oro * 2 - 2][oc * 2 - 2] = ObjectType_WALL_H;
			curr_GS.players[opponent].wallsRemaining -= 1;
		}

		else {
			curr_GS.graph.graph[oro * 2 - 2][oc * 2 - 2] = ObjectType_WALL_H;
			curr_GS.players[opponent].wallsRemaining -= 1;
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
		if (isAI) {
			Move move = getMeMove(curr_GS);

			if (move.moveType == MoveType_PLAYER) {
				m = 0;

				curr_GS.graph.graph[curr_GS.players[whoAmI].position.x][curr_GS.players[whoAmI].position.y]
						= ObjectType_EMPTY;
				curr_GS.graph.graph[move.position.x][move.position.y]
						= playerNum_to_ObjectType(whoAmI);

				curr_GS.players[whoAmI].position = move.position;
			}

			else if (move.wallType == WallType_H) {
				m = 1;
				curr_GS.players[whoAmI].wallsRemaining -= 1;
				curr_GS.graph.graph[move.position.x][move.position.y]
						= ObjectType_WALL_H;
			}

			else { //vertical wall
				m = 2;
				curr_GS.players[whoAmI].wallsRemaining -= 1;
				curr_GS.graph.graph[move.position.x][move.position.y]
						= ObjectType_WALL_V;
			}

			r = move.position.x / 2 + 1;
			c = move.position.y / 2 + 1;
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
		cout << TL << " " << d << endl;
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

