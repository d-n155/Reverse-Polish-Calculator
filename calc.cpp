#include <iostream> 
#include <fstream> 
#include <ctype.h>
#include <string> 
#include "dlist.h"

// Function to check to see if the string is a float
static bool isFloatNumber(const std::string& string){
  std::string::const_iterator it = string.begin();
  bool decimalPoint = false;
  int minSize = 0;
  if(string.size()>0 && (string[0] == '-' || string[0] == '+')){
    it++;
    minSize++;
  }
  while(it != string.end()){
    if(*it == '.'){
      if(!decimalPoint) decimalPoint = true;
        else break;
      }else if(!std::isdigit(*it) && ((*it!='f') || it+1 != string.end() || !decimalPoint)){
        break;
      }
      ++it;
    }
  return string.size()>minSize && it == string.end();
}

/*
  Pseudocode: 
  void operation(Dlist list, char operator)
    numb1 = list.RemoveFront() 
    numb2 = list.RemoveFront() 
    if (numb1 != -1 and numb2 != -1)
      swtich(operator): 
        case '+':
          Insert to the front the list (numb1 + numb2);
          break
        case '-':
          Insert to the front the list(numb1 - numb2);
          break
        case '*':
          Insert to the front the list(numb1 * numb2);
          break; 
        case '/'
          Insert to the front the list(numb1 / numb2);
          break 
    else if (numb1 != -1 and numb2 == -1)
      Insert to the front the list(numb1); 
      print "Not enough operands"
*/
void operation(Dlist<float> &list, char operand) {
	if (list.IsEmpty()) {
		std::cout << "Not enough operands" << std::endl;
	}
	else {
		float numb1 = list.RemoveFront();
		if (list.IsEmpty()) {
			std::cout << "Not enough operands" << std::endl;
			list.InsertFront(numb1);
		}
		else {
			float numb2 = list.RemoveFront();
			switch (operand) {
			case '+':
				list.InsertFront(numb1 + numb2);
				break;
			case '-':
				list.InsertFront(numb2 - numb1);
				break;
			case '*':
				list.InsertFront(numb1 * numb2);
				break;
			case '/':
				list.InsertFront(numb1 / numb2);
				break;
			}
		}
	}
}
/*
  void letterOperation(Dlist list, char operator)
    if (list is not empty)
    float numb1 = remove the last element of the list and return it here
      switch(char):
        case 'n':
          Insert to the front the list(numb1 * -1); 
        case 'd':
          Insert to the front the list(numb1); 
          Insert to the front the list(numb1);
        case 'r':
          if (list is not empty)
          float numb2 = remove the last element of the list and return it here; 
            Insert to the front the list(numb2)
            Insert to the front the list(numb1)
          else
            Insert to the front the list(numb1);
            print "Not enough operands."
        case 'p':
          print numb1; 
          Insert to the front the list(numb1);
        case 'c':
          float num = remove the last element of the list and return it here 
          while(num != -1)
            num = list.RemoveFront()
        case 'a':
          float num = remove the last element of the list and return it here 
          while(list is not empty)
            num = remove the last element of the list and return it here
            print num 
            print ' '
          print endl; 
*/
void letterOperation(Dlist<float> &list, char operand) {
	if (!list.IsEmpty()) {
		float numb1 = list.RemoveFront();
		switch (operand) {
		case 'n':
			list.InsertFront(numb1 * -1);
			break;
		case 'd':
			list.InsertFront(numb1);
			list.InsertFront(numb1);
			break;
		case 'r': {
			if (!list.IsEmpty()) {
				float numb2 = list.RemoveFront();
				list.InsertFront(numb2);
				list.InsertFront(numb1);
				break;
			}
			else {
				list.InsertFront(numb1);
				std::cout << "Not enough operands.\n" << std::endl;
				break;
			}
		}
		case 'p':
			std::cout << numb1 << std::endl;
			list.InsertFront(numb1);
			break;
		case 'c': {
			float num = list.RemoveFront();
			while (!list.IsEmpty()) {
				num = list.RemoveFront();
			}
			break;
		}
		case 'a': {
			float num = list.RemoveFront();
			while (num != -1) {
				num = list.RemoveFront();
				std::cout << num << ' ';
			}
			std::cout << std::endl;
			break;
		}
		}
	}
}

/*Pseudocode: 
int main()
  Dlist<float> list
  prompt the user to enter variable string named var

  while (var[0] != 'q' (quit option))
    if (var.length() == 1)
      if (isFloatNumber(var))
        Insert (var) to the front of the list
      else
        if (var[0] == '+' or var[0] == '-' or var[0] == '*' or var[0] == '/')
          operation(list,var[0]);
        if (var[0] == 'n' or var[0] == 'd' or var[0] == 'r' or var[0] == 'p' or var[0] == 'c' or var[0] == 'a')
          letterOperation(list,var[0])
        else
          print "Bad input\n"
    else
      if (var is a float number)
        insert var to the front of the list 
      else
        print "Bad input"
*/
int main(){
  Dlist<float> list; 
  std::string var; 
  // Prompt users to enter values: 
  std::cout << "Input: " << std::endl; 
  std::cin >> var; 

  while (var[0] != 'q'){
    // If the user enter a string that consists only one element
    if (var.length() == 1){
      // If the user enter a valid number
      if (isFloatNumber(var)){
        list.InsertFront(stof(var)); 
      }else{
        // If the user enter one of the operator 
        if (var[0] == '+' or var[0] == '-' or var[0] == '*' or var[0] == '/'){
          operation(list,var[0]);
        }
        if (var[0] == 'n' or var[0] == 'd' or var[0] == 'r' or var[0] == 'p' or var[0] == 'c' or var[0] == 'a'){
          letterOperation(list,var[0]); 
        }
        else{
          std::cout << "Bad input" << std::endl; 
        }
      }
    }
    else{
      // If the user enter a string that consist more than one element 
      // If the user enter a float 
      if (isFloatNumber(var)){
        list.InsertFront(stof(var)); 
      }
      else{
        // If the user enter bad input 
        std::cout << "Bad input" << std::endl; 
      }
    }
  }
  std::cin >> var; 
}
