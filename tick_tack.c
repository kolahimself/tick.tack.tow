#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* an implementation of the tic-tac-toe game in c
 * update: it's good, and memcheck clean too
 * oh, you don't beleive me? then challenge the
 * great Wumpus, the Wise!
 */

//ouch, global variables, i know
enum game_mode{
	EASY,
	MEDIUM,
	HARD,
	HUMAN
};
int mode = HUMAN;
char padding[35];

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

//print welcome message
void welcome(){
    printf("Welcome Explorer!!\nI am Wumpus the Wise, and I "
    "challenge you to a game of Tic-Tac-Toe.\n"
    "Do you dare enter, young adventurer?\n");
}

//winning move, assumes self has player value 2
//returns a move that wins, or 0 otherwise
int find_winning_move(int** board){
	//diagonals
	if(board[0][0] + board[1][1] + board[2][2] == 2 * 2){				//possibly two 2 marks
		if(!(board[0][0] == 1 || board[1][1] == 1)){					//filter false positives
			int ret = board[0][0] == 0 ? 1 : (board[1][1] == 0 ? 5 : 9);
			return ret;
		}
	}
	if(board[0][2] + board[1][1] + board[2][0] == 2 * 2){				//possible two 2 marks
		if(!(board[0][2] == 1 || board[1][1] == 1)){					//false positives
			int ret = board[0][2] == 0 ? 3 : (board[1][1] == 0 ? 5 : 7);
			return ret;
		}
	}

	//vertical and horizontal
	for(int i = 0; i < 3; i++){
		if(board[i][0] + board[i][1] + board[i][2] == 2 * 2){			//possible two 2 marks
			if(!(board[i][0] == 1 || board[i][1] == 1)){				//false positive
				int ret = board[i][0] == 0 ? (3*i + 1) : (board[i][1] == 0 ? (3*i + 2) : (3*i + 3));
				return ret;
			}
		}
		if(board[0][i] + board[1][i] + board[2][i] == 2 * 2){			//possible two 2 marks
			if(!(board[0][i] == 1 || board[1][i] == 1)){				//filter false positive
				int ret = board[0][i] == 0 ? (1 + i) : (board[1][i] == 0 ? (4 + i) : (7 + i));
				return ret;
			}
		}
	}
	return 0;
}

//defense, assumes the opponent has player value 1
//returns a move that blocks potential loss, or 0 if none
int find_blocking_move(int** board){
	//diagonals
	if(board[0][0] == 1 || board[1][1] == 1){							//there exists 1 marks
		if(board[0][0] + board[1][1] + board[2][2] == 2 * 1){			//exactly and only two 1 marks
			int ret = board[0][0] == 0 ? 1 : (board[1][1] == 0 ? 5 : 9);
			return ret;
		}
	}
	if(board[0][2] == 1 || board[1][1] == 1){							//there exists 1 marks
		if(board[0][2] + board[1][1] + board[2][0] == 2 * 1){			//exactly and only two 1 marks
			int ret = board[0][2] == 0 ? 3 : (board[1][1] == 0 ? 5 : 7);
			return ret;
		}
	}

	//vertical and horizontal
	for(int i = 0; i < 3; i++){
		if(board[i][0] == 1 || board[i][1] == 1){						//there exists 1 marks
			if(board[i][0] + board[i][1] + board[i][2] == 2 * 1){		//exactly and only two 1 marks
				int ret = board[i][0] == 0 ? (3*i + 1) : (board[i][1] == 0 ? (3*i + 2) : (3*i + 3));
				return ret;
			}
		}
		if(board[0][i] == 1 || board[1][i] == 1){						//there exists 1 marks
			if(board[0][i] + board[1][i] + board[2][i] == 2 * 1){		//exactly and only two 1 marks
				int ret = board[0][i] == 0 ? (1 + i) : (board[1][i] == 0 ? (4 + i) : (7 + i));
				return ret;
			}
		}
	}
	return 0;
}


//stupid decision making, random choosing
int computer_move_easy(int** board){
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
//by making winning moves, or else blocking a losing one
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
		printf("Enter game mode, h for human, defaults to vs computer:\n");
		char m;
		scanf(" %c", &m);
		if(m == 'h') {
			mode = HUMAN;
			printf("Mode selected: Human,\n");
		}else{
			printf("Enter difficulty, m for medium, h for hard, defaults to easy:\n");
			scanf(" %c", &m);
			if(m == 'm'){
				mode = MEDIUM;
				printf("Mode selected: Medium,\n");
			}else if(m == 'h'){
				mode = HARD;
				printf("Mode selected: Hard,\n");
			}else{
				mode = EASY;
				printf("Mode selected: Easy,\n");
				srand(time(0));
			}
			welcome();
		}

		int player = 1;
		printf("Enter f for player 2 to go first, else player 1 goes first: \n");
		scanf(" %c", &m);
		if(m == 'f') player = 2;
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