/* pure logical arithmetic to evaluate
 * possible winning moves and block
 * potential fatalities
 */
 
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
