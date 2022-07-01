#include <stdio.h>
#include <time.h>
#include "find_moves.h"

/* handles the logic/illogic of the 
 * computer's decisions given a board,
 * prints the decision and returns the
 * selected integer value
 */

//stupid decision making, random choosing
int computer_move_easy(int** board){
	srand(time(0));
	int p = 1;
	int i = 0, j = 0;
	do{
		p = (rand() % 9) + 1;
		i = (p - 1) / 3;
		j = (p - 1) % 3;
	}while(board[i][j] != 0);
    printf("The great Wumpus has randomly chosen: %d\n", p);
    return p;
}

//a tad more intelligent, plans a step further
//by making winning moves, or else blocking a losing one.
//if not possible, pick randomly
int computer_move_medium(int** board){
	int move = find_winning_move(board);
	if(move){
		printf("The great Wumpus has decided on: %d\n", move);
		return move;
	}
	move = find_blocking_move(board);
	if(move){
		printf("The great Wumpus has decided on: %d\n", move);
		return move;
	}
	return computer_move_easy(board);
}

//improves on medium by introducing a little strategy?
//plans two moves ahead and prefers to occupy corners first
int computer_move_hard(int** board){
	int move = find_winning_move(board);
	if(move){
		printf("The great Wumpus has decided on: %d\n", move);
		return move;
	}
	move = find_blocking_move(board);
	if(move){
		printf("The great Wumpus has decided on: %d\n", move);
		return move;
	}

	//find possible win in two
	//diagonal
	if(board[0][0] + board[1][1] + board[2][2] == 1 * 2){				//possible solo 2 mark
		if(!(board[0][0] == 1 || board[1][1] == 1)){					//false positive
			move = board[0][0] == 0 ? 1 : 9;							//prefer corners
			printf("The great Wumpus has thoughtfully chosen: %d\n", move);
			return move;
		}
	}
	if(board[0][2] + board[1][1] + board[2][0] == 1 * 2){				//possible solo 2 mark
		if(!(board[0][2] == 1 || board[1][1] == 1)){					//filter false positives
			move = board[0][2] == 0 ? 3 : 7;							//prefer corners
			printf("The great Wumpus has thoughtfully chosen: %d\n", move);
			return move;
		}
	}
	//vertical and horizontal
	for(int i = 0; i < 3; i++){
		if(board[i][0] + board[i][1] + board[i][2] == 1 * 2){			//possibly a single 2 mark
			if(!(board[i][0] == 1 || board[i][1] == 1)){				//filter false positive
				move = board[i][0] == 0 ? (3*i + 1) : (3*i + 3);		//again, temd towards corners
				printf("The great Wumpus has thoughtfully chosen: %d\n", move);
				return move;
			}
		}
		if(board[0][i] + board[1][i] + board[2][i] == 1 * 2){			//possible 2 mark solo
			if(!(board[0][i] == 1 || board[1][i] == 1)){				//false positive
				move = board[0][i] == 0 ? (1 + i) : (7 + i);			//tend towards corners
				printf("The great Wumpus has thoughtfully chosen: %d\n", move);
				return move;
			}
		}
	}

	//still nothing? pick a corner then
	int corners[] = {0, 2};
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			if(board[corners[i]][corners[j]] == 0){
				move = corners[i] * 3 + corners[j] + 1;
				printf("The great Wumpus has settled with move: %d\n", move);
				return move;
			}
		}
	}

	//whoa, all corners taken? i give up
	return computer_move_easy(board);
}