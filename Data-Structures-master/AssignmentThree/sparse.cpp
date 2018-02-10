#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include "ArgumentManager.h"
#include "arraylist.h"
#include "arraysort.h"
#include "arraysearch.h"
using namespace std;

int checkOperation(string operation, string recursive, string storage);
int checkInvalid(string a, string b, int &maxIfileOne, int &maxJfileOne, int &maxIfileTwo, int &maxJfileTwo);
void printToFile(arrayManager *arrayResult, int resultSize, string c); 
void bigOFile(int numOfLinesA, int numOfLinesB, string sort, int timeComplexA, int timeComplexB);

int main(int argc, char *argv[]){
	ArgumentManager am(argc, argv); //code provided by TA's, strings are simply function calls defined by TA's.
	string a = am.get("A"), b = am.get("B"), result = am.get("result"), operation = am.get("operation"), sort = am.get("sort"), storage = am.get("storage");
	int numOfLinesA = 0, numOfLinesB = 0, maxIfileOne = 0, maxJfileOne = 0, maxIfileTwo = 0, maxJfileTwo = 0, counter = 0, timeComplexA = 0, timeComplexB = 0; 
	bool isSortA = true, isSortB = true; 
	ifstream file1, file2;
	ofstream outfile;
	string currentString;

	file1.open(a); //open input file A.
	file2.open(b); //open input file B.

  	if (file1.is_open() && file2.is_open()){ //if both files are open...
			while (getline(file1, currentString)){
				stringstream ss(currentString);
				if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; }
				else
				numOfLinesA++; //get the size of matrix A.
			}
			while (getline(file2, currentString)){
				stringstream ss(currentString);
				if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; }
				else
				numOfLinesB++; //get the size of matrix B.
			}

			int x = checkOperation(operation, sort, storage); //return a number to 'x' using a function call.

			switch(x) { //switch case to control what operation will be performed based on what checkOperation returns.
			case 1:
				if (checkInvalid(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ 
					cout << "ERROR: File 1 and 2 are incompatible together.\n"; outfile.open(result); outfile.close(); return 0; } //check for invalid matrix size
				else {
					int resultSize = maxIfileOne * maxJfileTwo;
					arrayManager *arrayA = new arrayManager[numOfLinesA]; //dynamic array of size input file A
					arrayManager *arrayB = new arrayManager[numOfLinesB]; //dynamic array of size input file B
					arrayManager *arrayResult = new arrayManager[resultSize]; //dynamic array of size input maxIfile1 * maxJfile2
					arrayMatrixParse(a,arrayA, maxIfileOne, maxJfileOne); //parses matrix from file A.
					arrayMatrixParse(b,arrayB, maxIfileTwo, maxJfileTwo); //parses matrix from file B.
					checkSorted(arrayA, numOfLinesA, isSortA);
					checkSorted(arrayB, numOfLinesB, isSortB); 
					multiplyArrays(arrayA, arrayB, arrayResult, numOfLinesA, numOfLinesB, resultSize, isSortA, isSortB, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo, counter);
					sortArrayQuickSort(arrayResult, 0, counter, timeComplexA);
					//sortArrayBubbleSort(arrayResult, counter, timeComplexA); //run a sorting algorithm. 
				 	printToFile(arrayResult, counter, result); //print to output file.
				 	delete[] arrayA; //delete dynamic array
					delete[] arrayB; //delete dynamic array
					delete[] arrayResult; }
				break;
			case 2:
				if (checkInvalid(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ 
					cout << "ERROR: File 1 and 2 are incompatible together.\n"; outfile.open(result); outfile.close(); return 0; }
				else { //almost identical to the code above.
					int resultSize = maxIfileOne * maxJfileTwo;
					arrayManager *arrayA = new arrayManager[numOfLinesA];
					arrayManager *arrayB = new arrayManager[numOfLinesB];
					arrayManager *arrayResult = new arrayManager[resultSize];
					arrayMatrixParse(a,arrayA, maxIfileOne, maxJfileOne);
					arrayMatrixParse(b,arrayB, maxIfileTwo, maxJfileTwo);
					sortArrayQuickSort(arrayA, 0, numOfLinesA, timeComplexA);
					sortArrayQuickSort(arrayB, 0, numOfLinesB, timeComplexB);
					multiplyArrays(arrayA, arrayB, arrayResult, numOfLinesA, numOfLinesB, resultSize, isSortA, isSortB, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo, counter);
					printToFile(arrayResult, counter, result);
					bigOFile(numOfLinesA, numOfLinesB, sort, timeComplexA, timeComplexB); 
					delete[] arrayA;
				 	delete[] arrayB; 
				 	delete[] arrayResult; }
				break;
			case 3:
				if (checkInvalid(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ 
					cout << "ERROR: File 1 and 2 are incompatible together.\n"; outfile.open(result); outfile.close(); return 0; }
				else {
					int resultSize = maxIfileOne * maxJfileTwo;
					arrayManager *arrayA = new arrayManager[numOfLinesA];
					arrayManager *arrayB = new arrayManager[numOfLinesB];
					arrayManager *arrayResult = new arrayManager[resultSize];
					arrayMatrixParse(a,arrayA, maxIfileOne, maxJfileOne);
					arrayMatrixParse(b,arrayB, maxIfileTwo, maxJfileTwo);
					sortArrayBubbleSort(arrayA, numOfLinesA, timeComplexA);
					sortArrayBubbleSort(arrayB, numOfLinesB, timeComplexB);
					multiplyArrays(arrayA, arrayB, arrayResult, numOfLinesA, numOfLinesB, resultSize, isSortA, isSortB, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo, counter); 
					printToFile(arrayResult, counter, result);
					bigOFile(numOfLinesA, numOfLinesB, sort, timeComplexA, timeComplexB);
					delete[] arrayA;
				 	delete[] arrayB;
				 	delete[] arrayResult; }
				break;
			case 4:
				return 0;
			}
		}

    else { //if files are not found.
		cout << "ERROR: File 1 or File 2 not found. \n";
    	outfile.open(result);
    	outfile.close(); //close file stream for file not found error.
    	file1.close(); //close file stream for file not found error.
    	file2.close(); //close file stream for file not found error.
    	return 0;
    }

		file1.close(); //close file stream assuming everything worked.
		file2.close(); //close file stream assuming everything worked.
		return 0;
}

int checkOperation(string operation, string sort, string storage){
	//controls what operation is specified by user, and returns a specific value to be controled by switch case.
	if (operation == "multiply"){
		if ((storage == "array" || storage == "") && (sort == "nosort" || sort == "")){
				cout << "multiply arrays, using nosort" << endl;
				return 1;
		}
		else if ((storage == "array" || storage == "") && (sort == "nlogn")){
				cout << "multiply arrays, using nlogn" << endl;
				return 2;
		}
		else if ((storage == "array" || storage == "") && (sort == "nsquared")){
				cout << "multiply arrays, using nsquared" << endl;
				return 3;
		}
	}
	else if (operation == "add"){
			cout << "ERROR: Adding not implemented." << endl;
			return 4;
	}
	else {
			cout << "ERROR: Adding not implemented." << endl;
			return 4;
	}
	return 0;
}

int checkInvalid(string a,string b, int &maxIfileOne, int &maxJfileOne, int &maxIfileTwo, int &maxJfileTwo){
	ifstream file1, file2;
	string currentString;
	int fileOneI = 0, fileOneJ = 0, fileTwoI = 0, fileTwoJ = 0;
	int tempFileOneI = 0, tempFileOneJ = 0, tempFileTwoI = 0, tempFileTwoJ = 0;

	file1.open(a);
	file2.open(b);

	while(getline(file1, currentString)){
		stringstream ss(currentString);
		if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; }
		ss >> fileOneI >> fileOneJ;

		if (fileOneI > tempFileOneI)
				tempFileOneI = fileOneI;
		if (fileOneJ > tempFileOneJ)
				tempFileOneJ = fileOneJ;
	}
	maxIfileOne = tempFileOneI;
	maxJfileOne = tempFileOneJ;

	while(getline(file2, currentString)){
		stringstream ss(currentString);
		if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; }
		ss >> fileTwoI >> fileTwoJ;

		if (fileTwoI > tempFileTwoI)
				tempFileTwoI = fileTwoI;
		if (fileTwoJ > tempFileTwoJ)
				tempFileTwoJ = fileTwoJ;
	}
	maxIfileTwo = tempFileTwoI;
	maxJfileTwo = tempFileTwoJ;

	if(tempFileOneJ == tempFileTwoI){
		return 1; 
	}

	file1.close();
	file2.close();
	return 0;
}

void printToFile(arrayManager *arrayResult, int counter, string result){
	ofstream outfile;
	outfile.open(result);

	for (int i = 0; i < counter-1; i++){
		if (arrayResult[i].i ==0 && arrayResult[i].j == 0){continue;}
		if (arrayResult[i].value == 0){continue;}
		outfile << arrayResult[i].i << " " << arrayResult[i].j << " " << fixed << setprecision(2) << arrayResult[i].value << endl; 
	}
	outfile << arrayResult[counter-1].i << " " << arrayResult[counter-1].j << " " << fixed << setprecision(2) << arrayResult[counter-1].value << endl;
	outfile.close();
} //print to file specified by user.

void bigOFile(int numOfLinesA, int numOfLinesB, string sort, int timeComplexA, int timeComplexB){
	int bigOnsquaredA = 1.99 * numOfLinesA * numOfLinesA;
	int bigOnsquaredB = 1.99 * numOfLinesB * numOfLinesB; 
	int bigOnlognA = 1.36 * numOfLinesA * numOfLinesA;  
	int bigOnlognB = 1.36 * numOfLinesB * numOfLinesB; 

	ifstream infile("big0.txt");
	ofstream outfile; 
	if (!infile.good()){
		outfile.open("big0.txt");
		outfile << "algorithm  #entries(n)  countComparisons  bigOcountComparisons" << endl; 
	}
	outfile.close(); 
	outfile.open("big0.txt", ios::out|ios::app);
	if (sort == "nsquared"){
		outfile << sort << "        " << numOfLinesA << "               " << timeComplexA << "                 " << bigOnsquaredA << endl; 
		outfile << sort << "        " << numOfLinesB << "               " << timeComplexB << "                 " << bigOnsquaredB << endl; 
	}
	else if (sort == "nlogn"){
		outfile << sort << "           " << numOfLinesA << "               " << timeComplexA << "                 " << bigOnlognA << endl; 
		outfile << sort << "           " << numOfLinesB << "               " << timeComplexB << "                 " << bigOnlognB << endl; 
	}
	outfile.close(); 
}
