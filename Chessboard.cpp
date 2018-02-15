#include "Chessboard.h"
#include "Stack.h"
#include <iostream>

#define board_size 8
#define number_possible_moves 8
#define FAIL 10

Chessboard::Chessboard(void)
: Chessboard(0, 0)
{}
	
//constructor that creates a Chessboard with a knight that begins at the row and column passed
Chessboard::Chessboard(int row, int column)
: board (new int*[board_size]),
  current_row (row),
  current_column (column),
  order_visited (0),
  exhaustive_option_tried (0)
{
	for (int row_index = 0; row_index < board_size; row_index++) {
		board[row_index] = new int[board_size];
		for (int column_index = 0; column_index < board_size ; column_index++) {
			board[row_index][column_index] = -1; //project specification
		}
	}
	//The initial position of the knight has value 0
	board[row][column] = order_visited;
}

//copy constructor that makes a deep copy
Chessboard::Chessboard(const Chessboard& copy)
	: board (nullptr),
	  current_row (copy.current_row),
	  current_column (copy.current_column),
	  order_visited (copy.order_visited),
	  exhaustive_option_tried (copy.exhaustive_option_tried)
{
	board = new int*[board_size];
	for (int index = 0; index < board_size; index++) {
		board[index] = new int[board_size];
	}
	for (int index = 0; index < board_size; index++) {
		for (int j = 0; j < board_size; j++) {
			board[index][j] = copy.board[index][j];
		}

	}
}

//destructor
Chessboard::~Chessboard(void) {
	for (int index = 0; index < board_size; index++) {
		delete [] board[index];
	}
	delete [] board;
}

//overloaded assignment operator that makes a deep copy of the Chessboard on the right hand side (rhs) of the = operator
Chessboard Chessboard::operator = (const Chessboard & rhs) {

	current_row = rhs.current_row;
	current_column = rhs.current_column;
	order_visited = rhs.order_visited;
	exhaustive_option_tried = rhs.exhaustive_option_tried;
	for (int index = 0; index < board_size; index++) {
			delete [] board[index];
	}
	delete [] board;
	board = new int*[board_size];
	for (int index = 0; index < board_size; index++) {
		board[index] = new int[board_size];
	}
	for (int index = 0; index < board_size; index++) {
		for (int j = 0; j < board_size; j++) {
			board[index][j] = rhs.board[index][j];
		}
	}

	return *this;
}

//method that utilizes Warnsdorff's heuristic to find a proper move for the knight;
//returns true if the heuristic was able to find a valid square to move to; returns false if not
bool Chessboard::warnsdorff(void) {
	
	int degree[number_possible_moves]; //stores the degree of each possible move
	
	for (int index = 0; index < board_size; index++) {
		
		int potential_row = current_row + delta_row[index];
		int potential_column = current_column + delta_column[index];
		
		//The degree of each potential move is stored in the degree array.
		//In invalid move has degree FAIL (value 10), which is guaranteed not to be the lowest degree; thus, the knight will not move there.
		if (isValidSquare(potential_row, potential_column)) {
			degree[index] = getDegree(potential_row, potential_column);
		}else {
			degree[index] = FAIL;
		}
	}

	int smallest_degree_index = findSmallestDegreeIndex(degree);
	
	//A smallest_degree_index of -1 means a  valid move was not found, and the method returns false. 
	//It therefore does not execute the instructions below, which actually move the knight.
	if (smallest_degree_index == -1) { //failed
		return false;

	//If a valid move was found, the current row and column are updated accordingly (i.e., the knight is moved)
	}else {
		current_row += delta_row[smallest_degree_index];
		current_column += delta_column[smallest_degree_index];
		order_visited += 1;
		board[this->current_row][this->current_column] = order_visited;
		return true;
	}

}

//method used by the Warnsdorff heuristic to find the degree of each possible move site
int Chessboard::getDegree(int x, int y) {
	
	int degree = 0;
	//the number of squares that are valid moves (0-8) is stored in the degree variable 
	for (int index = 0; index < number_possible_moves; index++) {
		
		int potential_row = x + delta_row[index];
		int potential_column = y + delta_column[index];
		if (isValidSquare(potential_row, potential_column)) {
			degree += 1;
		}
	}
	//The heuristic's goal is to find the option with the smallest degree.
	//However, 0 degree  means there are no possible moves from that location, so we
	//want to prevent 0 from being selected as the smallest degree. Thus,
	//we return FAIL, which has value 10, which will not be smaller than
	//a valid option.
	if (degree == 0) {
		return FAIL;
	}
	else {
		return degree;
	}
}

//method used by the Warnsdorff heuristic to find the smallest degree and return the index
//of the move that corresponds to that degree
int Chessboard::findSmallestDegreeIndex (int degree[]) {
	
	int smallest_degree = degree[0];
	int smallest_degree_index = 0;
	
	for (int index = 1; index < number_possible_moves; index++) {
		if (degree[index] < smallest_degree) {
			smallest_degree = degree[index];
			smallest_degree_index = index;
		}
	}
	//If all options have degree 10, there are no valid moves. This method will return -1, 
	//which will cause the warnsdorff method to return false
	if (smallest_degree == FAIL) {
		return -1; //failed
	}
	
	return smallest_degree_index;
}


//method that finds the next move for the knight by exhaustively trying all possibilities;
//returns true if a valid move was found; returns false if not
bool Chessboard::exhaustive(void) {
	
	bool found_a_valid_square = false;

	for (int index = exhaustive_option_tried; index < board_size; index++) {
		
		int potential_row = current_row + delta_row[index];
		int potential_column = current_column + delta_column[index];
		
		//exhaustive_option_tried stores the number of potential move options tried from the current position.
		//If a state is popped off the stack because the knight reached a dead end, 
		//this variable will allow us to try the next option when we return the knight to its prevoius state.
		//This prevents us from getting stuck in an infinite loop by continously popping and then trying the same bad option.
		exhaustive_option_tried += 1;		
		
		//if a valid move is found, the knight is moved there, and the value stored at that location
		//is set to the order in which it was reached
		if (isValidSquare(potential_row, potential_column)) {
		
			current_row = potential_row;
			current_column = potential_column;
			order_visited += 1;
			board[current_row][current_column] = order_visited;
			found_a_valid_square = true;
			index = board_size; //ends 'for loop
		}
	}

	return found_a_valid_square;
}

//a potential square is a valid location if it's on the board and hasn't already been visited
bool Chessboard::isValidSquare(int row, int column) {
	
	if ((row >= 0) && (row < board_size) && (column >= 0) && (column < board_size) && board[row][column] == -1) {
		return true;
	}
	else {
		return false;
	}

}


//method that runs all 63 moves of the knight
void Chessboard::knightTour(void) {

	Stack * chessStack = new Stack;

	//The allowed number of Warnsdorff moves is 32, or half of the board area
	while (order_visited < (board_size * board_size /2 )) {
		
		//If warnsdorff returns true, a valid option is found, and the new state creted by warnsdorff() is pushed onto the stack.
		if (warnsdorff()) {
			chessStack->push(*this);
		}
		
		//If warnsdorff returns false, a valid option was not found, and the current state is popped off the stack.
		//This will likely never happen, which is why the Warnsdorff heuristic is so successful.
		else {
			chessStack->pop();
			*this = chessStack->getTop();
		}

	}
	//The remainder of the moves are made using the exhaustive method
	while (order_visited < board_size*board_size - 1) {
		
		//If exhaustive() returns true, a vlaid options was found, and the new state created by exhaustive() is pushed onto the stack
		if (exhaustive()) {

			chessStack->push(*this);
			exhaustive_option_tried = 0; //Allow the new state to start from the beginning of the list of possible moves
		}
		//If exhaustive() returns false, a valid move was not found. The current state is popped off the stack
		//and returns to its previous state. temp allows the previous exhaustive_option_tried to be saved so that
		//the next option can be tried (i.e., invalid options are not retried).
		else {
			Chessboard temp = chessStack->getTop();
			chessStack->pop();
			*this = chessStack->getTop();
			exhaustive_option_tried = temp.getExhaustiveOptionTried();


		}
	}
	
	printBoard();
	std::cout << std::endl;

	delete chessStack;
}

int Chessboard::getExhaustiveOptionTried(void) {
	return exhaustive_option_tried;
}

int** Chessboard::getBoard(void) {
	return board;
}

void Chessboard::printBoard(void) {
	std::cout << std::endl;
	for (int i = 0; i < 8; i++) {
		std::cout << std::endl;
		for (int j = 0; j < 8; j++) {
			std::cout << board[i][j] << ' ';
		}
	}
}

int Chessboard::getCurrentRow(void) {
	return current_row;
}

int Chessboard::getCurrentColumn(void) {
	return current_column;
}






