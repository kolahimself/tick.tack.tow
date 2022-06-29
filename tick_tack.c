#include <stdio.h>
#include "board.h"
#include "moves.h"

/* an implementation of the tic-tac-toe game in c
 * update: it's good, and memcheck clean too
 * oh, you don't beleive me? then challenge the
 * great Wumpus, the Wise!
 */

//ouch, global variables, i know
int mode = HUMAN;
char padding[35];

//print welcome message
void welcome(){
    printf("Welcome Explorer!!\nI am Wumpus the Wise, and I "
    "challenge you to a game of Tic-Tac-Toe.\n"
    "Do you dare enter, young adventurer?\n");
}

int main(){

    int** board = new_board();
	int done = 0;
	int p1 = 0, p2 = 0;

	//init padding
	for(int c = 0; c < 34; c++){
		padding[c] = ' ';
	}
	padding[34] = '\0';

	//game loop
	while(!done){
		printf("Enter h to change game mode to human, defaults to vs computer:\n");
		char m;
		scanf(" %c", &m);
		if(m == 'h') {
			mode = HUMAN;
			printf("Mode selected: Human,\n");
		}else{
			printf("Enter difficulty, e for easy, m for medium, h for hard, defaults to hard:\n");
			scanf(" %c", &m);
			if(m == 'm'){
				mode = MEDIUM;
				printf("Mode selected: Medium.\n");
			}else if(m == 'h'){
				mode = HARD;
				printf("Mode selected: Hard.\n");
			}else if(m == 'e'){
				mode = EASY;
				printf("Mode selected: Easy.\n");
				srand(time(0));
			}else{
				mode = HARD;
				printf("Mode selected: Hard.\n");
			}
			welcome();
		}

		int player = 2;
		printf("Enter f for player 1 to go first, else player 2 goes first: \n");
		scanf(" %c", &m);
		if(m == 'f') player = 1;
		printf("Player %d will go first.\n", player);
		for(int i = 0; i < 9; i ++){
			int position = get_move(board, player);
			mark(board, position, player);

			int w = check_win(board);
			if(w){
				printf("%s", padding);
				printf("Player %d has won, game over!\n", w);
				print(board);
				if(w == 1) p1++;
				else p2++;
				break;
			}
			player = player == 1 ? 2 : 1;

			if(i == 8){
				printf("%sGame over, it is a draw:\n", padding);
				print(board);
			}
		}
		
		printf("Current cumulative score for player 1 is %d\n", p1);
		printf("Current cumulative score for player 2 is %d\n", p2);

		printf("Enter r to restart, anything else to cancel: \n");
		char cont;
		scanf(" %c", &cont);
		if(cont != 'r') done = 1;
		else reset(board);
		printf("\n");
	}
	printf("All right, then. See ya!\n");
    destroy(board);
    
    return 0;
}