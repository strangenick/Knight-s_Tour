#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#define board_size 8
#define number_possible_moves 8

class Chessboard {
	private:
			int** board; //stores the order in which each chessboard square is visited
			int current_row;
			int current_column;
			int order_visited;
			
			//exhaustive_option_tried stores the number of potential move options tried from the current position.
			//If a state is popped off the stack because the knight reached a dead end, 
			//this variable will allow us to try the next option when we return the knight to its prevoius state.
			//This prevents us from getting stuck in an infinite loop by continously popping and then trying the same bad option.
			int exhaustive_option_tried;
			
			//The indices of delta_row and delta_column match up to represent a possible move
			const int delta_row[number_possible_moves] = {1,1,2,2,-1,-1,-2,-2};
			const int delta_column[number_possible_moves] = {2,-2,1,-1,2,-2,1,-1};

	public:
			Chessboard(void);
			Chessboard(int, int);
			Chessboard(const Chessboard& copy);
			~Chessboard(void);
			Chessboard operator = (const Chessboard & rhs);
			bool warnsdorff(void);
			bool exhaustive(void);
			int getDegree(int, int);
			int findSmallestDegreeIndex(int[]);
			bool isValidSquare(int, int);
			void knightTour(void);
			int** getBoard(void);
			void printBoard(void);
			int getExhaustiveOptionTried(void);
			int getCurrentRow(void);
			int getCurrentColumn(void);
};
#endif /* CHESSBOARD_H_ */
