#include <cstdlib>
#ifndef __DLIST_H__
#define __DLIST_H__


/***************************************
 * Do not modify the class declarations!
 ***************************************/
class emptyList {
	// OVERVIEW: an exception class
};

template <typename T>
class Dlist {
	// OVERVIEW: contains a double-ended list of Objects

public:
	// Operational methods
	void displayList();

	bool IsEmpty();
	// EFFECTS: returns true if list is empty, false otherwise


	void InsertFront(const T &o);
	// MODIFIES this
	// EFFECTS inserts o at the front of the list

	void InsertBack(const T &o);
	// MODIFIES this
	// EFFECTS inserts o at the back of the list

	T RemoveFront();
	// MODIFIES this
	// EFFECTS removes and returns first object from non-empty list
	//         throws an instance of emptyList if empty

	T RemoveBack();
	// MODIFIES this
	// EFFECTS removes and returns last object from non-empty list
	//         throws an instance of emptyList if empty


	// Maintenance methods
	Dlist();                                   // ctor
	Dlist(const Dlist &l);                     // copy ctor
	Dlist &operator=(const Dlist &l);          // assignment
	~Dlist();                                  // dtor

private:
	// A private type
	struct node {
		node   *next;
		node   *prev;
		T      o;
	};

	node   *first; // The pointer to the first node (0 if none)
	node   *last;  // The pointer to the last node (0 if none)
	//How us this different than the doubly linked list in class?

	// Utility methods

	void MakeEmpty();
	// EFFECT: called by constructors to establish empty
	// list invariant

	void RemoveAll();
	// EFFECT: called by destructor and operator= to remove and destroy
	// all list nodes

	void CopyAll(const Dlist &l);
	// EFFECT: called by copy constructor/operator= to copy nodes
	// from a source instance l to this instance

};

/**** DO NOT MODIFY ABOVE THIS LINE *****/

/***************************************
 *ADD  Member function implementations here
 ***************************************/

 // OPERATIONAL METHODS:
 /*Pseudocode
 bool Dlist<T>:IsEmpty()
  if (first = nullptr)
    return true; 
  else 
    return false
 */ 
template <typename T>
bool Dlist<T>::IsEmpty() {
	// EFFECTS: returns true if list is empty, false otherwise
	if (first == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

/*
  void Dlist<T>::InsertFront(const T &o){
    dynamically allocate temp
    temp->o = o; 
    if (list is empty)
      temp->next = nullptr
      first = templast = temp
    else
      first->prev = temp
      temp->next = first
      first = temp
  }
*/
template <typename T>
void Dlist<T>::InsertFront(const T &o) {
	// MODIFIES this
	// EFFECTS inserts o at the front of the list
	node *temp = new node();
	temp->o = o;
	temp->prev = nullptr;
	if (first == nullptr) {
		temp->next = nullptr;
		first = temp;
		last = temp;
	}
	else {
		first->prev = temp;
		temp->next = first;
		first = temp;
	}
}

/*Pseudocode 
  void Dlist<T>::InsertBack(const T &o){
    dynamically allocate temp
    temp->o = o; 
    temp->next = nullptr
    if (list is empty)
      temp->prev = nullptr
      first = temp
      last = temp
    else
      last->next = temp
      temp->prev = last
      last = temp
  }
*/
template <typename T>
void Dlist<T>::InsertBack(const T &o) {
	// MODIFIES this
	// EFFECTS inserts o at the back of the list
	node *temp = new node();
	temp->o = o;
	temp->next = nullptr;

	if (IsEmpty()) {
		temp->prev = nullptr;
		first = temp;
		last = temp;
	}
	else {
		last->next = temp;
		temp->prev = last;
		last = temp;
	}
}

/*
  Pseudocodce 
  if (the list is empty)
    return 0
  else 
    new node = first; 
    first = first->next 
    T temp_data = temp->o
    delete temp
    return temp_data
*/
template <typename T>
T Dlist<T>::RemoveFront() {
	// MODIFIES this
	// EFFECTS removes and returns first object from non-empty list
	//         throws an instance of emptyList if empty
	if (IsEmpty()) {
		return 0;
	}
	else {
		node *temp = first;
		first = first->next;
		T temp_data = temp->o;
		delete temp;
		return temp_data;
	}
}


/*
  Pseudocodce 
  if (the list is empty)
    return 0
  else 
    node *temp = last;
		last = last->prev;
		last->next = nullptr;
		delete[] temp;
		return last->o;
*/
template <typename T>
T Dlist<T>::RemoveBack() {
	// MODIFIES this
	// EFFECTS removes and returns last object from non-empty list
	//         throws an instance of emptyList if empty
	if (IsEmpty()) {
		return 0;
	}
	else {
		node *temp = last;
		last = last->prev;
		last->next = nullptr;
		delete[] temp;
		return last->o;
	}
}

/*
  Pseudocode: 
  node *curr = first;
	int i = 1;
	while (current node is not nullptr) {
		print current node data
		curr = curr->next;
	}
*/
// UTILITY METHODS
template <typename T>
void Dlist<T>::displayList() {
	// Traverse through the list 
	node *curr = first;
	std::cout << "The list is: ";
	int i = 1;
	while (curr != nullptr) {
		std::cout << "Element #" << i << ": " << curr->o << std::endl;
		curr = curr->next;
		i++;
	}
}


template <typename T>
void Dlist<T>::MakeEmpty() {
	// EFFECT: called by constructors to establish empty
	// list invariant
	first = nullptr;
	last = nullptr;

	/* testing
	std::cout << first << std::endl;
	std::cout << last;
	*/
}

/*
  node curr = first node
  node next; 
  while (curr is not nullptr)
    next = curr->next 
    delete curr
    curr = next
  first = nullptr
  last = nullptr
*/
template <typename T>
void Dlist<T>::RemoveAll() {
	// EFFECT: called by destructor and operator= to remove and destroy
	// all list nodes
	node *curr = first;
	node *nxt;
	while (curr != nullptr) {
		nxt = curr->next;
		delete curr;
		curr = nxt;
	}
	first = nullptr;
	last = nullptr;
}

/*
  node curr 
  curr = list first node 
  while (curr is not nullptr)
    Insert curr data into the back of the list 
    curr = curr->next
*/
template <typename T>
void Dlist<T>::CopyAll(const Dlist &l) {
	// EFFECT: called by copy constructor/operator= to copy nodes
	// from a source instance l to this instance
	node *curr;
	curr = l.first;
	while (curr != nullptr) {
		InsertBack(curr->o);
		curr = curr->next;
	}
}

// MAINTAINANCE METHODS: 
template <typename T>
Dlist<T>::Dlist() {
	// ctor
	MakeEmpty();

}

template <typename T>
Dlist<T>::Dlist(const Dlist &l) {
	// copy ctor
	RemoveAll();
	CopyAll(l);
}

template <typename T>
Dlist<T>& Dlist<T>::operator=(const Dlist &l) {
	// Remove all the element before copy the element; 
	RemoveAll();

	// Copy the element from l to our object 
	CopyAll(l);

	return *this;
}

template <typename T>
Dlist<T>::~Dlist() {
	// dtor
	RemoveAll();
}

/* this must be at the end of the file */
#endif /* __DLIST_H__ */

