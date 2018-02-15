#include <stdexcept>
#include "Stack.h"


Stack::Stack(void)
: top (nullptr),
  size (0)
{}

Stack::~Stack(void) {
	
	//manages memory by popping each state off the stack
	while (!isEmpty()) {
		pop();
	}
}

void Stack::push(const Chessboard& element) {
	top = new Node(element, top);
	size += 1;
}

void Stack::pop(void) {
	if (!isEmpty()) {
		
		//move the top the next node, then delete the current top
		size -= 1;
		Node* currentTop = top;
		top = top->getNext();
		currentTop->setNextToNull();
		delete currentTop;

	}
	else {
		throw std::out_of_range("The stack is empty!");
	}

}

Chessboard Stack::getTop(void) {
	return top->getData();
}

bool Stack::isEmpty(void) {
	
	return (size==0);
}

int Stack::getSize(void) {
	return size;
}
