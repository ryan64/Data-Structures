#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct arrayManager { //struct to store i, j and value per element in array of type struct.
	int i = 0, j = 0;
	double value = 0;
};

void arrayMatrixParse(string file, arrayManager *array, int maxI, int maxJ){
	ifstream infile;
	infile.open(file);
	string currentString;
	int tempI;
	int tempJ;
	double tempvalue;
	int counter = 0;

	while (getline(infile, currentString)){
		stringstream ss(currentString);
		if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; } //skip lines if junk data is in file.
		ss >> tempI >> tempJ >> tempvalue; //hold what is being read in into temporary values.
		if (tempI != maxI || tempJ != maxJ){ //if temporary values are not max values in matrix.
			if (tempvalue!= 0 && !isalpha(tempvalue) && tempI>0 && tempJ>0){ //check if number is 0, or if numbers are negative, or if character is in filestream.
				(array+counter)->i = tempI; //store i in appropriate element in array
				(array+counter)->j = tempJ; //store j in appropriate element in array
				(array+counter)->value = tempvalue; //store value in appropriate element in array
				counter++; //increment counter to go to next element in array.
			}
		}
		else {
		(array+counter)->i = tempI; //store i in appropriate element in array
		(array+counter)->j = tempJ; //store j in appropriate element in array
		(array+counter)->value = tempvalue; /*//store value in appropriate element in array*/ }
	}
	infile.close();
}

void addArrayNonRecursive(arrayManager *arrayA, arrayManager *arrayB, int AandB, int numOfLinesA, int numOfLinesB){
	bool isUnique = true; //initial boolean statement set to true.
	for (int x = 0; x < numOfLinesA; x++){ //outer for loop to control iterations for arrayA
		isUnique = true; //reset boolean statement to true (during for loop execution).
		for (int y = 0; y < AandB; y++){ //inner for loop to control iterations for arrayB
			if ((((arrayA+x)->i) == ((arrayB+y)->i)) && (((arrayA+x)->j) == ((arrayB+y)->j))){ //if (arrayA i == arrayB i && arrayA j == arrayB j)
				(arrayB+y)->value = (arrayB+y)->value + (arrayA+x)->value; //add values together from both files.
				isUnique = false; //set isunique to false.
				break;
			}
		}
		if (isUnique){ //if true, append to end of array B contents from arrayA.
			(arrayB+numOfLinesB)->i = (arrayA+x)->i;
			(arrayB+numOfLinesB)->j = (arrayA+x)->j;
			(arrayB+numOfLinesB)->value = (arrayA+x)->value;
			numOfLinesB++;
		}
	}
}

void swap(arrayManager* a, arrayManager* b){
	arrayManager temp = *a; //take arrayA contents, store it in temp.
	*a = *b; //take arrayB contents, store it in arrayA contents.
	*b = temp; //take temp contents, and store it in arrayB contents.
}  //swap elements.

void sortArray(arrayManager *arrayB, int AandB){
	for (int x = 0; x < AandB; x++){
		for (int y = 0; y < (AandB - x - 1); y++){
			if ((arrayB+y)->i > (arrayB+y+1)->i) swap(arrayB+y, arrayB+y+1); //first check, if arrayB i is greater than array B i+1, swap everything.
			else if((arrayB+y)->i == (arrayB+y+1)->i && (arrayB+y)->j > (arrayB+y+1)->j) swap(arrayB+y, arrayB+y+1); //second check, if arrayB i matches arrayB i+1, but the j value of arrayB is greater than array B i+1, swap everything.
		}
	}
} //bubble sort algorithm implemented.

void printToFile(arrayManager *arrayB, int AandB, string c){
	ofstream outfile;
	outfile.open(c.c_str());

	outfile << "#Matrix C=B+A" << endl;
	for (int x = 0; x < AandB-1; x++){
		if ((arrayB+x)->i <= 0 && (arrayB+x)->j <= 0){continue; } //we dont want to print garbage data.
		if ((arrayB+x)->value == 0){continue; } //we dont want to print garabe data.
		outfile << (arrayB+x)->i << " " << (arrayB+x)->j << " " << fixed << setprecision(2) << (arrayB+x)->value << endl;
	}
	outfile << (arrayB+AandB-1)->i << " " << (arrayB+AandB-1)->j << " " << fixed << setprecision(2) << (arrayB+AandB-1)->value << endl;
	outfile.close();
} //print to file specified by user.

void innerRecursion(int x, int y, int AandB, bool& isUnique, arrayManager *arrayA, arrayManager *arrayB){
	if ((((arrayA+x)->i) == ((arrayB+y)->i)) && (((arrayA+x)->j) == ((arrayB+y)->j))){ //try to add if (arrayA i == arrayB i && arrayA j == arrayB j)
		(arrayB+y)->value = (arrayB+y)->value + (arrayA+x)->value;
		isUnique = false;
	}
	else if (y < AandB) innerRecursion(x, y+1, AandB, isUnique, arrayA, arrayB); //once condition is no longer satisfied, it stops.
}

void outerRecursion(int x, arrayManager *arrayA, arrayManager *arrayB, int AandB, int numOfLinesA, int numOfLinesB, bool isUnique){
	//function called in main.
	if(x >= numOfLinesA) //think of x as the iterator from the for loop in nonRecurise addition. if x is greater or equal to numOfLinesA (arrayA size), stop recursion.
	return;
	innerRecursion(x, 0, AandB, isUnique, arrayA, arrayB); //this is the first part of the recursive process executed.
	if (isUnique){
		(arrayB+numOfLinesB)->i = (arrayA+x)->i;
		(arrayB+numOfLinesB)->j = (arrayA+x)->j;
		(arrayB+numOfLinesB)->value = (arrayA+x)->value;
		numOfLinesB++;
	}
 outerRecursion(x+1, arrayA, arrayB, AandB, numOfLinesA, numOfLinesB, true); //once condition is no longer satisfied, it stops.
}
