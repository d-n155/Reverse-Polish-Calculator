#include <iostream> 
#include <fstream> 
#include <ctype.h>
#include <string> 
#include "dlist.h"

struct Record {
	int time_stamp; 
	std::string name; 
	std::string status; 
	int duration; 
};


/*Pseudocode
int main()
  Create 4 Dlist queues 
  plat queue
  gold queue 
  silver queue 
  regular queue 

  Prompt the user to enter the name of the file 
  open the file
  maximum_ticks = the first number in the file 
  Create 4 variables: 
  int time_stamp
  string name 
  string status 
  int duration 

  initialize next_tick_call = 0

  for (i = 0; i <= maximum_ticks; i++)
    print "Starting stick" + i 
    while (not the end of file)
      Read the next line into time_stamp
      Read the next line into name
      Read the next line into status
      Read the next line into time_stamp
      // Inserting a caller into a queue
      if (time_stamp == i)
        Create a Record pointer, and allocate it 
        p->time_stamp = time_stamp
				p->name = name
				p->status = status
				p->duration = duration
        // Deciding which queues to add to 
        if (status == "plat") {
					Insert p to the front of plat queue 
				}		
				// Inserting pointer p to gold queue
				else if (status == "gold") {
					Insert p to the front of gold queue
				}
				// Inserting pointer p to silver queue
				else if (status == "silver") {
					Insert p to the front of silver queue
				}
				// Inserting pointer p to regular queue
				else if (status == "none") {
					Insert p to the front of regular queue 
				}
        D 
*/ 
int main()
{
	// Creating 4 queues 
	Dlist<Record*> plat; 
	Dlist<Record*> gold; 
	Dlist<Record*> silver;
	Dlist<Record*> regular;
	std::ifstream myFile; 

	// Prompt the user to enter the file name 
	std::string fileName; 
	std::cout << "File name: "; 
	std::cin >> fileName; 

	myFile.open(fileName); 

	// Getting the maximum number of ticks
	int maximum_ticks; 
	myFile >> maximum_ticks; 
	std::cout << maximum_ticks << std::endl;

	int time_stamp;
	std::string name; 
	std::string status; 
	int duration; 

	int next_tick_call = 0; 

	// Starting to push the caller information
	// into the queues 
	for (int i = 0; i <= maximum_ticks; i++) {
		std::cout << "Starting tick #" << i << std::endl; 
		// Display who called 
		while (!myFile.eof()) {
			myFile >> time_stamp; 
			myFile >> name; 
			myFile >> status; 
			myFile >> duration;
			// Inserting a caller into a queue 
			if (time_stamp == i) {
				Record *p = new Record; 
				p->time_stamp = time_stamp; 
				p->name = name; 
				p->status = status; 
				p->duration = duration; 
				// Deciding which queues to add to 
				// Inserting pointer p to plat queue
				if (status == "plat") {
					plat.InsertFront(p); 
				}		
				// Inserting pointer p to gold queue
				else if (status == "gold") {
					gold.InsertFront(p);
				}
				// Inserting pointer p to silver queue
				else if (status == "silver") {
					silver.InsertFront(p);
				}
				// Inserting pointer p to regular queue
				else if (status == "none") {
          p->status = "regular";
					regular.InsertFront(p); 
				}
				// Display who just got inserted
				std::cout << "Call from " << name << " a " << status << " member\n"; 
			}
		}; 
		myFile.clear(); 
		myFile.seekg(1); 
		// If not busy, display who will get the answer 
		bool flag = false;
		Record *a = new Record;
		if (next_tick_call == i) {
			// Look through each queue
			if (!plat.IsEmpty()) {
				a = plat.RemoveFront();
				flag = true;
				next_tick_call = a->duration + i;
			}
			else if (!gold.IsEmpty()) {
				a = gold.RemoveFront(); 
				flag = true;
				next_tick_call = a->duration + i;

			}
			else if (!silver.IsEmpty()) {
				a = silver.RemoveFront(); 
				flag = true;
				next_tick_call = a->duration + i;

			}
			else if (!regular.IsEmpty()) {
				a = regular.RemoveFront(); 
				flag = true;
				next_tick_call = a->duration + i;
			}
		}
		if (flag == true) {
			std::cout << "Answering call from " << a->name << std::endl;
		}
		
	}
}