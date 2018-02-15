class List {
	private:
		struct node {
			
			//Each node contains a row and column entered by the user,
			//as well as a pointer to the next node in the list
			int row;
			int column;
			node * next;

			node(int r, int c) 
			: row (r),
			  column (c),
			  next (nullptr)
			{}
			
			//overloaded destructor that returns dynamically allocated memory to the OS
			~node(void) {
				delete next;
			}

			int getRow(void) {
				return row;
			}

			int getColumn(void) {
				return column;
			}
		};
		
		//head and tail point to the end nodes of the list
		node *head;
		node *tail;
		int size;

	public:
		List(void) 
		: head (nullptr),
		  tail (nullptr),
		  size (0)
		 {}
		
		//destructor that deletes all nodes with one instruction, since each one points to the next,
		//and the pointers are deleted in the node destructor
		~List(void) {
			delete head;
		}

		void createFirstNode(int r, int c) {
			node * welcome = new node(r, c);
			head = tail = welcome;
			size += 1;
			
		}
		
		void insertAtEnd(int r, int c) {
			node * welcome = new node(r, c);
			
			//need to control for this potential issue; if not, tail->next = welcome will fail
			if (tail == nullptr) {
				head->next = welcome;
				tail = welcome;
			}

			tail->next = welcome; //new link
			tail = welcome;
			size += 1;
						
		}

		void insertAtStart(int r, int c) {
			node * welcome = new node(r, c);
			welcome->next = head; //new link
			head = welcome;
			size += 1;
		}

		void insertAtX(int r, int c, int x) {
			node * before;
			node * current = head;
			node * welcome = new node(r, c);
			
			//loop through the list until you find the correct position
			for (int i = 1; i < x; i++) {
				before = current;
				current = current->next;
			}
			
			//insert new node there:
			before->next = welcome;
			welcome->next = current;
			size += 1;
		}

		void deleteHead(void) {
			node * temp = head;
			head = head->next; //point head at next node
			
			//need to control for these cases; if not, bad deletions occur
			if (size == 1) {
				tail = nullptr;
			}else {
				temp->next = nullptr;
			}
			delete temp; //delete former head
			size -= 1;
		}

		void deleteTail(void) {
			
			//need access to last and second-to-last node
			node * current = head;
			node * before;

			while (current->next != nullptr) {
				before = current; //ultimately points to second-to-last node
				current = current->next; //ultimately points to tail
			}
			before->next = nullptr;
			tail = before; //point tail to second-to-last-node
			delete current; //delete former tail
			size -= 1;
		}

		void deleteAtX(int x) {
			node * current = head;
			node * before;
			
			//loop through until link X is found
			for (int i = 1; i < x; i++) {
				before = current;
				current = current->next;
			}
			before->next = current->next; //Nothing points to the X link now, so it can be deleted
			current->next = nullptr; //prevent bad delete
			delete current;
			size -= 1;
		}

		int getSize(void) {
			return size;
		}
		
		//returns the row value at link x
		int getRow(int x) {
			node * current = head;
			for (int i = 1; i < x; i++) {
				current = current->next;
			}
			return current->getRow();
		}
		
		//returns the column value at link x
		int getColumn(int x) {
			node * current = head;
			for (int i = 1; i < x; i++) {
				current = current->next;
			}
			return current->getColumn();
		}


};
