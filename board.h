#include <stdlib.h>

/* manages the tic-tac-toe board to present
 * a simpler interface
 */

//create and return a new board
int** new_board(){
    int** ret = malloc(3 * sizeof(int*));
    for(int i = 0; i < 3; i++){
        ret[i] = malloc(3 * sizeof(int));
        for(int j = 0; j < 3; j++){
            ret[i][j] = 0;
        }
    }
    return ret;
}

//frees space allocated to board
void destroy(int** board){
    for(int i = 0; i < 3; i++){
        free(board[i]);
    }
    free(board);
}

//reset a board contents
void reset(int** board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = 0;
        }
    }
}

//marks a position on the board
//position is 1 - 9 counting from top left
//player is 1 or 2 for X or O respectively
void mark(int** board, int position, int player){
    int i = (position - 1) / 3;
    int j = (position - 1) % 3;
    if(board[i][j]) return;
    if(player < 1 || player > 2) return;
    board[i][j] = player;
}

//checks if a player has three marks in a line
//returns that player number, 0 otherwise
int check_win(int** board){
	//diagonals
	if(board[0][0] & board[1][1] & board[2][2]) return board[0][0];
	if(board[0][2] & board[1][1] & board[2][0]) return board[0][2];

	//vertical and horizontal
	for(int i = 0; i < 3; i++){
		if(board[i][0] & board[i][1] & board[i][2]) return board[i][0];
		if(board[0][i] & board[1][i] & board[2][i]) return board[0][i];
	}
	return 0;
}

extern char padding[35];

//prints the current board and its current contents
void print(int** board){
    printf("The current board is:\n");
    for(int i = 0; i < 3; i++){
        printf("%s _____" " _____" " _____ \n", padding);
        printf("%s|     " "|     " "|     |\n", padding);
		printf("%s", padding);
        for(int j = 0; j < 3; j++){
            int p = board[i][j];
            char c = ' ';
            if(p) c = p == 1 ? 'X' : 'O';
            printf("|  %c  ", c);
        }
        printf("|\n");
        printf("%s|     " "|     " "|     |\n", padding);
        printf("%s _____" " _____" " _____ \n", padding);
    }
}