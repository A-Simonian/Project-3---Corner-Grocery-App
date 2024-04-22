#include "GroceryItem.h"

//Implementation of GroceryItem

/*
Constructor for GroceryItem with name only, defaults quantity to 0
@param name - string for name of item
*/
GroceryItem::GroceryItem(std::string& name)
{
	this->name = name;
	quantity = 0;
}

/*
Constructor for GroceryItem with name and quantity
@param name - string for name of item
@param quantity - int value containing the quanity of GroceryItem
*/
GroceryItem::GroceryItem(std::string& name, int quantity)
{
	this->name = name; 
	this->quantity = quantity; 

}

/*
Method to call to get name of GroceryItem variable
@returns - name of item
*/
std::string GroceryItem::getName() const
{
	return name;
}

/*
Method to call to get quantity of GroceryItem variable
@returns - quantity of item
*/
int GroceryItem::getQuantity() const
{
	return quantity;
}

/*Method to update quantity of item by 1*/
void GroceryItem::addItem() 
{
	quantity += 1;
}
/*Method to update quantity of item by -1*/
void GroceryItem::removeItem()
{
	quantity -= 1;
}

bool GroceryItem::operator<(const GroceryItem& other) const
{
	return name.compare(other.getName()) < 0;
}
