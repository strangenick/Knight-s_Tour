#include <iostream>
#include "Chessboard.h"
#include "Stack.h"
#include "List.cpp"
#include <stdlib.h>
#include <string.h>

#define total_squares 64

void printList(List* list) {
	std::cout << "\nYour updated list: \n";
	for (int i = 1; i <= list->getSize(); i++) {
		std::cout << i << ": (" << list->getRow(i)+1 << ", " << list->getColumn(i)+1 << ")\n";
	}
}

//The main function is used to control the program through communication with the user.
//User input is taken as strings, and atoi and c_str are used to convert these to int's where necessary.
//'while' loops are used after each 'cin' statament to force the user to enter valid options.
//For row and column values, the user may enter an int from 1-8 rather than 0-7 since the user
//may not be familiar with 0-based indexing. When a user's input is used to create a new node,
//their inputs are decremented by 1 to allow for 0-based indexing by the rest of the program.
int main(void) {

	std::cout << "\nWelcome to the Knight's Tour Program!\n";
	
	std::string user_selection = "0";
	std::string user_row = "0";
	std::string user_column = "0";

	Chessboard cb[total_squares];
	List * user_list = new List;

	while (user_selection != "5") {
		std::cout << "\nPlease select an option below by typing the corresponding number and pressing 'enter.'\n";
		std::cout << "1. Add to the list of initial positions\n2. Delete an initial position from the list\n3. Modify an initial position\n4. Run the Knight's Tour\n5. Exit\n";
		std::cout << "Your selection: ";
		std::cin >> user_selection;
		while (user_selection != "1" && user_selection != "2" && user_selection != "3" && user_selection != "4" && user_selection != "5") {
			std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
			std:: cin >> user_selection;
		}
		
		
		switch (atoi(user_selection.c_str())) {
			
			//user has selected to add a new initial position to the list
			case 1:{
				int size = user_list->getSize();
				std::string add_selection = "0";
				std::cout << "\nWhat would you like to do? :\n" << "1. Simply add new position to the next spot in the list\n2. Add new position to a specific spot of your choice\nYour selection: ";
				std::cin >> add_selection;
				while (add_selection != "1" && add_selection != "2") {
					std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
					std:: cin >> add_selection;
				}	

				switch(atoi(add_selection.c_str())) {
					case 1:
						std::cout << "\nEnter the row for position " << size + 1 << " of the knight (1-8): ";
						std::cin >> user_row;
						while (user_row != "1" && user_row != "2" && user_row != "3" && user_row != "4" && user_row != "5" && user_row != "6" && user_row != "7" && user_row != "8") {
							std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
							std:: cin >> user_row;
						}

						std::cout << "\nEnter the column for position " << size + 1 << " of the knight (1-8): ";
						std::cin >> user_column;
						while (user_column != "1" && user_column != "2" && user_column != "3" && user_column != "4" && user_column != "5" && user_column != "6" && user_column != "7" && user_column != "8") {
							std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
							std:: cin >> user_column;
						}


						if (size == 0) {
							user_list->createFirstNode(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);
						}
						else {
							user_list->insertAtEnd(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);
						}
						break;

					case 2:{
						std::string new_location;
						int size = user_list->getSize();
						std::cout << "\nIn which position in the list would you like to place the new knight position (1-" << size+1 << "): ";
						std::cin >> new_location;
						while (atoi(new_location.c_str()) < 1 || atoi(new_location.c_str()) > size+1) {
							std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
							std:: cin >> new_location;
						}

						std::cout << "\nEnter the row for position " << new_location << " of the knight (1-8): ";
						std::cin >> user_row;
						while (user_row != "1" && user_row != "2" && user_row != "3" && user_row != "4" && user_row != "5" && user_row != "6" && user_row != "7" && user_row != "8") {
							std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
							std:: cin >> user_row;
						}

						std::cout << "\nEnter the column for position " << new_location << " of the knight (1-8): ";
						std::cin >> user_column;
						while (user_column != "1" && user_column != "2" && user_column != "3" && user_column != "4" && user_column != "5" && user_column != "6" && user_column != "7" && user_column != "8") {
							std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
							std:: cin >> user_column;
						}

						if (new_location == "1") {
							if (size == 0) {
								user_list->createFirstNode(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);
							}
							else {
								user_list->insertAtStart(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);
							}
						}
						else if(atoi(new_location.c_str()) == size+1) {
							user_list->insertAtEnd(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);

						}
						else {
							user_list->insertAtX(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1, atoi(new_location.c_str()));
						}
						break;	
						   }
				
				}
				printList(user_list);
				break;
				   
				   }
			
			case 2:{
				int size = user_list->getSize();
				if (size==0) {
					std::cout << "Sorry, there is nothing to delete!\n";
				}
				else {
					std::string position_to_delete = "0";
					std::cout << "\nWhich position would you like to delete (1-" << size << ")? ";
					std::cin >> position_to_delete;
					while (atoi(position_to_delete.c_str()) < 1 || atoi(position_to_delete.c_str()) > size) {
						std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
						std:: cin >> position_to_delete;
					}

					if (position_to_delete == "1") {
						user_list->deleteHead();
					}
					else if (atoi(position_to_delete.c_str()) == user_list->getSize()) {
						user_list->deleteTail();
					}
					else {
						user_list->deleteAtX(atoi(position_to_delete.c_str()));
					}
					printList(user_list);
				}
				break;
				}
			
			case 3:{
				int size = user_list->getSize();
				std::string position_to_modify = "0";
				std::cout << "\nWhich position would you like to modify (1-" << size << ")? ";
				std::cin >> position_to_modify;
				while (atoi(position_to_modify.c_str()) < 1 || atoi(position_to_modify.c_str()) > size) {
					std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
					std:: cin >> position_to_modify;
				}

				std::cout << "What is the new row (1-8)? ";
				std::cin >> user_row;
				while (user_row != "1" && user_row != "2" && user_row != "3" && user_row != "4" && user_row != "5" && user_row != "6" && user_row != "7" && user_row != "8") {
					std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
					std:: cin >> user_row;
				}

				std::cout << "What is the new column (1-8)? ";
				std::cin >> user_column;
				while (user_column != "1" && user_column != "2" && user_column != "3" && user_column != "4" && user_column != "5" && user_column != "6" && user_column != "7" && user_column != "8") {
					std::cout << "Sorry, that is not a valid option!\nPlease re-enter: ";
					std:: cin >> user_column;
				}

				if (position_to_modify == "1") {
					user_list->deleteHead();
					if (size == 0) {
						user_list->createFirstNode(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);
					}
					else {
						user_list->insertAtStart(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1);
					}
				}
				else if (atoi(position_to_modify.c_str()) == size) {
					user_list->deleteTail();
					user_list->insertAtEnd(atoi(user_row.c_str())- 1, atoi(user_column.c_str()) - 1);
				}
				else {
					user_list->deleteAtX(atoi(position_to_modify.c_str()));
					user_list->insertAtX(atoi(user_row.c_str()) - 1, atoi(user_column.c_str()) - 1, atoi(position_to_modify.c_str()));
				}
				printList(user_list);
				break;
				}
			
			case 4:{
				int** board_array[total_squares];
				for (int index = 0; index < user_list->getSize(); index++) {
					cb[index] = Chessboard(user_list->getRow(index+1), user_list->getColumn(index+1));
					std::cout << "\nKnight's Tour for position (" << cb[index].getCurrentRow()+1 << ", " << cb[index].getCurrentColumn()+1 << "):";
					cb[index].knightTour();
					board_array[index]  = cb[index].getBoard();
				}
				break;
				}
			
			case 5:
				   std::cout << "\nThank you for using the Knight's Tour Program! Goodbye!\n\n";
				   break;
		}
	}

	delete user_list;
	return 0;


}

