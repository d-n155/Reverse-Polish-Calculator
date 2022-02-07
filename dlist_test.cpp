#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

enum Job {STUDENT, FACULTY, STAFF};

struct Record {
  string name;
  string uniqname;
  Job job;
};

int main() {

  Dlist<Record*> catsweb; //records are big, so store pointer

  Record* p = new Record;
  p->name = "Andrew DeOrio";
  p->uniqname = "awdeorio";
  p->job = FACULTY;
  catsweb.InsertFront(p);

  // do something with "catsweb"
  p->name = "Anthony"; 
  p->uniqname = "adsfasdf";
  p->job = STUDENT; 
  catsweb.InsertBack(p);
  
  // don't forget to delete objects on the heap
  while ( !catsweb.IsEmpty() ) {
    Record *r = catsweb.RemoveFront();
    cout << r->uniqname << endl;
    delete r;
  }

  return 0;
}
