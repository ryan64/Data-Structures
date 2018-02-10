#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct node { //same as arraylist except now were including two pointers, next and previous to traverse through the linkedlist.
	int i = 0, j = 0;
	double value = 0;
	node *next = nullptr, *previous = nullptr;
};

void linkedListMatrixParse(string file, node *current, int maxI, int maxJ){
	ifstream infile;
	infile.open(file);
	string currentString;
	int tempI;
	int tempJ;
	double tempvalue;

	while(getline(infile, currentString)){
		stringstream ss(currentString);
		if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; } //skip lines if junk data is in file.
		ss >> tempI >> tempJ >> tempvalue; //hold  what is being read in into temporary values.
		if (tempI != maxI || tempJ != maxJ){ //if temporary values are not max values in matrix.
			if (tempvalue!= 0 && !isalpha(tempvalue) && tempI>0 && tempJ>0){ //check if number is 0, or if numbers are negative, or if character is in filestream.
					current->i = tempI;  //store i in appropriate element in array
					current->j = tempJ; //store j in appropriate element in array
					current->value = tempvalue; //store value in appropriate element in array
					current->next = new node; //create a new node if more parsing is necessary.
					current->next->previous = current; //the next node will have its previous pointer set to the current node
					current = current->next; //current pointer will now point to next node
				}
			}
		else {
		current->i = tempI; //store i in appropriate element in array
		current->j = tempJ; //store j in appropriate element in array
		current->value = tempvalue; /*store value in appropriate element in array*/}
	}
	infile.close();
}

void addLinkedListNonRecursive(node *currentA, node *currentB){
	bool isUnique = true; //initial boolean statement set to true.
	node *rootB = currentB; //rootB is literally just a holder for the head node.
	node *previousB;

	while(currentA){ //outer for loop to control iterations for arrayA
		isUnique = true; //reset boolean statement to true.
		while(currentB){ //inner for loop to control iterations for arrayB
			if (currentA->i == currentB->i && currentA->j == currentB->j){ //if (arrayA i == arrayB i && arrayA j == arrayB j)
				currentB->value += currentA->value; //add values together from both files.
				isUnique = false; //set isunique to false.
				break;
			}
			previousB = currentB; //previousB is node of currentB
			currentB = currentB->next; //currentB will point to next node.
		}
		if (isUnique){ //if true, append to end of array B.
			currentB = new node; //currentB = new node being appended.
			currentB->i = (currentA)->i; //currentB i is equal currentA i
			currentB->j = (currentA)->j; //currentB j is equal currentA j
			currentB->value = (currentA)->value; //currentB value equal currentA value
			currentB->previous = previousB; //previousB node is being set to the previous of currentB
			previousB->next = currentB; //currentB node is being set to the next node of previousB
		}
		currentA = currentA->next; //currentA is now pointing to next node;
		currentB = rootB; //currentB will be reset to head node.
	}
}

void swap(node* a, node* b){
	node temp = *a; //temp will be set to pointer a
	a->i = b->i; //value of a i will be equal to b i
	a->j = b->j; //value of a j will be equal to b j
	a->value = b->value; //value of a value will be equal to b value
	b->i = temp.i; //value of b i will be equal to temp i
	b->j = temp.j; //value of b j will be equal to temp j
	b->value = temp.value; ////value of b value will be equal to temp value
}  //swap elements.

void sortlinkedList(node *current){
	node *rootB = current; //rootB is literally just a holder for the head node.
	bool isSwapped = true; //boolean statement isSwapped set to true
	while (isSwapped){ // while isSwapped is true
		isSwapped = false; //set isSwapped to false, the inner while loop will control when its set to true again.
		while (current->next){ //while theres a next node
			if ((current)->i > (current)->next->i){ //first check, if current i is greater than next currents i, swap everything.
				swap(current, current->next);
				isSwapped = true;	/*isSwapped is set to true*/}
			else if((current)->i == (current)->next->i && (current)->j > (current)->next->j){ //second check, if current i matches next currents i, but the j value of current is greater than next currents i, swap everything.
				swap(current, current->next);
				isSwapped = true; }
			current = current->next;
		}
		current = rootB; //reset current to the head node of B
	}
} //bubble sort algorithm implemented.

void printToFile(node *currentB, string c){
	ofstream outfile;
	outfile.open(c.c_str());
	node *rootB = currentB;

	outfile << "#Matrix C=B+A" << endl;
	while (currentB){
		if ((currentB)->i <= 0 && (currentB)->j <= 0){currentB = currentB->next; continue;}
		if ((currentB)->value == 0){currentB = currentB->next; continue;}
		if ((currentB)->next == NULL){currentB = currentB->next; continue; }
		outfile << (currentB)->i << " " << (currentB)->j << " " << fixed << setprecision(2) << (currentB)->value << endl;
		currentB = currentB->next;
	}
	currentB = rootB;
	while(currentB){
		if (currentB->next == NULL){
			outfile << (currentB)->i << " " << (currentB)->j << " " << fixed << setprecision(2) << (currentB)->value << endl;
		}
		currentB = currentB->next;
	}
	currentB = rootB;
	outfile.close();
} //print to file specified by user.

void innerRecursion(bool &isUnique, node *currentA, node *&currentB, node *&previousB ){
	if (!currentB)
		return;
	if (currentA->i == currentB->i && currentA->j == currentB->j){ //if (arrayA i == arrayB i && arrayA j == arrayB j)
		currentB->value += currentA->value; //add values together from both files.
		isUnique = false; //set isunique to false.
		return;
	}
	previousB = currentB;
	currentB = currentB->next;
	innerRecursion(isUnique, currentA, currentB, previousB);
}

void outerRecursion(node *currentA, node *currentB){
	if (!currentA)
	return;
	bool isUnique = true;
	node *rootB = currentB, *previousB;

	innerRecursion(isUnique, currentA, currentB, previousB);

	if (isUnique){ //if true, append to end of array B.
		currentB = new node;
		currentB->i = (currentA)->i;
		currentB->j = (currentA)->j;
		currentB->value = (currentA)->value;
		currentB->previous = previousB;
		previousB->next = currentB;
	}
	outerRecursion(currentA->next, rootB);
}

void deleteList(node* current){ //need to delete linkedlists when theyre no longer in use, to prevent memory from being waisted.
   while (current->next){
		   current = current->next;
		   delete current->previous;
   }
	 delete current;
}
