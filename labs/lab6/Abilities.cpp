/*
 * Abilities.cpp
 * Comp 15 Fall 2018 
 * Lab Session 6
 * 
 */

#include <iostream>

#include "Abilities.h"

using namespace std;

//
// Allocate and initialize a new AbilityNode
// and return pointer to new node
//
AbilityList::AbilityNode *AbilityList::newAbilityNode(string weapon,
                                                      int strength,
                                                      AbilityNode *nextNode)
        const
{
        AbilityNode *newNode      = new AbilityNode();
        newNode->ability.weapon   = weapon;
        newNode->ability.strength = strength;
        newNode->next             = nextNode;
        return newNode;
}


// constructor
AbilityList::AbilityList()
{
	// start with only your hand
	front = newAbilityNode("hand", 1, NULL);
}

// copy constructor
AbilityList::AbilityList(const AbilityList &source)
{
	// check if there is anything to copy
	if (source.front != NULL) {

		// assign the front of source to temp so that we can use it
		AbilityNode* temp = source.front;
		
		// manually instantiate front because it is a private variable
		front = new AbilityNode;
		front->ability = temp->ability;
		front->next = temp->next;
		AbilityNode* curr = front;

		// deep copy the rest of the LL
		while (temp->next != NULL) {
			temp = temp->next;
			curr->next = new AbilityNode;
			curr = curr->next;
			curr->ability = temp->ability;
			curr->next = temp->next;
		}
	}

}


// assignment (=) overload
AbilityList &AbilityList::operator=(const AbilityList &source)
{
	// check for self-assignment
	if (this != &source) {

		// clean up old linked list so that we can copy into it
		deleteList();

		// assign the front of source to temp so that we can use it
		AbilityNode* temp = source.front;
		
		// manually instantiate front because it is a private variable
		front = new AbilityNode;
		front->ability = temp->ability;
		front->next = temp->next;
		AbilityNode* curr = front;

		// deep copy the rest of the LL into our existing LL
		while (temp->next != NULL) {
			temp = temp->next;
			curr->next = new AbilityNode;
			curr = curr->next;
			curr->ability = temp->ability;
			curr->next = temp->next;
		}
	}
	
	return *this;
}

// destructor
AbilityList::~AbilityList()
{
	deleteList();
}

// Function invoked on the destructor. Releases all memory
void AbilityList::deleteList()
{
	// create a curr pointer that gets the front of our AbilityNode
	AbilityNode* curr = front;

	// if there is something to delete, delete safely while saving the next
	while (curr != NULL) {
		AbilityNode* next = curr->next;
		delete curr;
		curr = next;
	}

	// set front to NULL so that the LL is no longer accessible
	front = NULL;
}

// updates the strength of weapon called "name" to "amount"
void AbilityList::updateAbility(std::string name, int amount)
{
	AbilityNode *curr = front;
	AbilityNode *prev = NULL;

	while (curr != NULL) {
		if (curr->ability.weapon == name) {
			// found the node to update
			curr->ability.strength = amount;
			return;
		}
		prev = curr;
		curr = curr->next;
	}
	// not found, create new node to populate
	curr = newAbilityNode(name, amount, NULL);

	if (prev == NULL) {     // if at front
		front = curr;
	} else {
		prev->next = curr;
	}
}

// determine the strength of a weapon based on the name
// returns -1 if the pirate does not have this ability
int AbilityList::getStrength(std::string name) const
{	
	return getStrengthHelper(name, front);
}

int AbilityList::getStrengthHelper(std::string name, AbilityNode* node) const
{
	if (node == NULL)
		return -1;
	else if (node->ability.weapon == name)
		return node->ability.strength;
	return getStrengthHelper(name, node->next);
}

// returns the number of abilities the a pirate has
int AbilityList::abilityCount() const
{
	return abilityCountHelper(front);
}

// recursive helper for abilityCount
int AbilityList::abilityCountHelper(AbilityNode* node) const 
{
	if (node == NULL)
		return 0;
	return 1 + abilityCountHelper(node->next);
}

// returns the ability by the index
Ability &AbilityList::abilityByIndex(int index) const
{
	// does not do error checking on index!
	AbilityNode *curr = front;
	for (int i = 0; i < index;i++) {
		curr = curr->next;
	}
	return curr->ability;
}

// print the abilities list for a pirate
void AbilityList::printAbilityList() const
{
	// walk the list and print all weapons and abilities
	AbilityNode *curr = front;
	while (curr != NULL) {
		cout << "\t" << curr->ability.weapon << " : "
				<< curr->ability.strength << "\n";
		curr = curr->next;
	}
}

// return total strength: the total strength is the sum
// of all the strengths for the pirate's weapons
int AbilityList::totalStrength() const
{
	int totalStrength = 0;

	// walk the list and calculate total strength
	AbilityNode *curr = front;
	while (curr != NULL) {
		totalStrength += curr->ability.strength;
		curr = curr->next;
	}
	return totalStrength;
}
