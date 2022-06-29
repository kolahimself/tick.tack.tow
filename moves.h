#include <stdio.h>
#include "computer_moves.h"

/* handles all movement queries based on the
 * next player, human or computer
 */

enum game_mode{
	EASY,
	MEDIUM,
	HARD,
	HUMAN
};

extern int mode;

//decides player 1's move given the board
int player1_move(int** board){
    print(board);
    int p = 0;
	int i = 0, j = 0;
	do{
		printf("Player 1, enter a valid unoccuppied square number, 1 - 9: ");
		scanf(" %d", &p);
		while((p < 1 || p > 9)) scanf(" %d", &p);
		i = (p - 1) / 3;
		j = (p - 1) % 3;
	}while(board[i][j] != 0);
    return p;
}

//human player 2's decision action
int human2_move(int** board){
    print(board);
	int p = 0, i = 0, j = 0;
	do{
		printf("Player 2, enter a valid unoccupied square number, 1 - 9: ");
		scanf(" %d", &p);
		while((p < 1 || p > 9)) scanf(" %d", &p);
		i = (p - 1) / 3;
		j = (p - 1) % 3;
	}while(board[i][j] != 0);
    return p;
}

//decides player 2's move given the board
int player2_move(int** board){
	switch(mode){
		case EASY: return computer_move_easy(board);
		case MEDIUM: return computer_move_medium(board);
		case HARD: return computer_move_hard(board);
		case HUMAN: return human2_move(board);
	}
}

//queries and returns the next move given the player
int get_move(int** board, int player){
    return player == 1 ? player1_move(board) : player2_move(board);
}
