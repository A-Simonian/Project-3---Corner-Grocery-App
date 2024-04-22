#include <iostream>
#include <fstream>
#include <string>
#include "GroceryItem.h"
#include <set>

using namespace std;

/*
Method to read data from file 
@returns - set of GroceryItems read in from file
*/

set<GroceryItem> readData() {

	set<GroceryItem> items;
	string itemName;

	//opening of file
	ifstream inFS;
	inFS.open("Inventory.txt");

	//check if file is open
	if (!inFS.is_open()) {
		cout << "Error: Unable to open file" << endl;
		return items;
	}

	//while loop to cycle through file
	while (getline(inFS, itemName)) {

		GroceryItem* item = new GroceryItem(itemName);

		auto existingItem = items.find(*item);

		if (existingItem != items.end()) {

			string name = (*existingItem).getName();
			int quantity = (*existingItem).getQuantity();

			items.erase(existingItem);

			item = new GroceryItem(name, quantity);
		}

		item->addItem(); //adds 1 to quantity for each item read from file

		items.insert(*item);

	}
	inFS.close();

	//Output to file
	ofstream outFS;

	outFS.open("Frequency.txt");

	if (!outFS.is_open()) {
		cout << "Could not open file Frequency.txt" << endl;
		return items;
	}

	for (GroceryItem item : items) {
		outFS << item.getName() << " " << item.getQuantity() << endl;
	}

	outFS.close();

	return items;
}

/*Prints menu for grocer inventory program*/
void PrintMenu() {

	cout << "1. Search for an item" << endl;
	cout << "2. Display all frequencies" << endl;
	cout << "3. Print histogram" << endl;
	cout << "4. Exit" << endl;
	cout << "Select choice: ";
}

/*Searches set to find item
@param items - a set of GroceryItem objects
*/
void SearchItem(set<GroceryItem> items) {
	
	string searchItem;
	bool found = false; //flag to check if item is found

	cout << "Enter item to search for: ";
	cin >> searchItem;
	for (GroceryItem item : items) {
		if (item.getName() == searchItem) {
			cout << item.getName() << " " << item.getQuantity() << endl;
			found = true;
		}
	}

	if (!found) { //message if item not found
		cout << "Item not found" << endl;
	}
	
	cout << endl; //new line for legibility of output
}
/*
Prints all names and quantity of set
@param items - set of GroceryItems
*/
void FrequencyPrint(set<GroceryItem> items) {
	
	for (GroceryItem item : items) {
		cout << item.getName() << " " << item.getQuantity() << endl;
	}
	cout << endl; //new line for legibility of output
}

/*
Prints histogram of all items in set
@param items - set of GroceryItems
*/
void HistogramPrint(set<GroceryItem> items) {

	for (GroceryItem item : items) {
		cout << item.getName() << " " << string(item.getQuantity(), '*') << endl;
	}
	cout << endl;  //new line for legibility of output
}

//Start of main
int main() {
	
	const int SEARCH = 1;
	const int FREQUENCY = 2;
	const int HISTOGRAM = 3;
	const int QUIT = 4;

	int userChoice = -1;

	set<GroceryItem> items; 
	

	cin.exceptions(ios::failbit); //exception for try catch fail

	while (userChoice != QUIT) {

		items = readData();
		PrintMenu();

		try { //start of try block

			cin >> userChoice;

			switch (userChoice) {

			case SEARCH:
				// Prompt user for an item and add it to 'items'
				SearchItem(items);
				break;

			case FREQUENCY:
				// Calculate and display frequencies
				FrequencyPrint(items); 
				break;

			case HISTOGRAM:
				// Create and print histogram
				HistogramPrint(items);
				break;

			case QUIT:
				cout << "Exiting program." << endl;
				break;

			default: //catch for invalid range of int
				cout << "Invalid option. Please choose again. \n" << endl;
			}
		}
		catch (ios_base::failure) { //catch for invalid userchoice. eg user enters string instead of integer for choice. 
			cout << "Invalid input. Please enter a valid choice. \n" << endl;
			cin.clear(); //clears cin of error
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores rest of line of invalid user input
		}
	}


	return 0;
}