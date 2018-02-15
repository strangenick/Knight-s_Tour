#ifndef STACK_H
#define STACK_H

#include "Node.cpp"

class Stack {

	private:
		Node* top;
		int size;

	public:
		Stack(void);
		~Stack(void);
		void push(const Chessboard& element);
		void pop(void);
	    	Chessboard getTop(void);
		bool isEmpty(void);
		int getSize(void);

};

#endif //STACK_H
