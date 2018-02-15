#include "Chessboard.h"

class Node {

	private:
		Chessboard data;
		Node* next;

	public:
		Node(const Chessboard& new_data, Node* next_node)
			: data (new_data),
			  next (next_node)
			{}
		
		//Note: A destructor that deletes the 'next' pointer is not needed because
		//the Stack destructor sets each pointer to null before deleting 
		//each Node.

		Chessboard getData(void) {
			return data;
		}

		Node* getNext(void) {
			return next;
		}

		void setNextToNull(void) {
			next = nullptr;
		}
};


