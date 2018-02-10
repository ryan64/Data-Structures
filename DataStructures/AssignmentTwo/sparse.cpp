#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include "ArgumentManager.h"
#include "arraylist.h"
#include "linkedlist.h"
using namespace std;

int checkOperation(string operation, string recursive, string storage);
int invalidMatrix(string a, string b, int &maxIfileOne, int &maxJfileOne, int &maxIfileTwo, int &maxJfileTwo);

int main(int argc, char *argv[]){
	ArgumentManager am(argc, argv); //code provided by TA's, strings are simply function calls defined by TA's.
	string a = am.get("A"), b = am.get("B"), c = am.get("C"), operation = am.get("operation"), recursive = am.get("recursive"), storage = am.get("storage");
	int numOfLinesA = 0, numOfLinesB = 0, maxIfileOne = 0, maxJfileOne = 0, maxIfileTwo = 0, maxJfileTwo = 0;
	ifstream file1, file2;
	ofstream outfile;
	string currentString;

  file1.open(a.c_str()); //open input file A.
	file2.open(b.c_str()); //open input file B.

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

			int AandB = numOfLinesA + numOfLinesB; //this will be the size of arrayB (size of input A + input B)
			int x = checkOperation(operation, recursive, storage); //return a number to 'x' using a function call.

			switch(x) { //switch case to control what operation will be performed based on what checkOperation returns.
			case 1:
				if (invalidMatrix(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ cout << "ERROR: File 1 and 2 are incompatible together.\n"; return 0; } //check for invalid matrix size
				else {
					arrayManager *arrayA = new arrayManager[numOfLinesA]; //dynamic array of size input file A
					arrayManager *arrayB = new arrayManager[AandB]; //dynamic array of size input file A + input file B
					arrayMatrixParse(a,arrayA, maxIfileOne, maxJfileOne); //parses matrix from file A.
					arrayMatrixParse(b,arrayB, maxIfileTwo, maxJfileTwo); //parses matrix from file B.
					addArrayNonRecursive(arrayA,arrayB,AandB,numOfLinesA, numOfLinesB); //add array non recursively.
					sortArray(arrayB, AandB); //run a sorting algorithm.
				 	printToFile(arrayB, AandB, c); //print to output file.
				 	delete[] arrayA; //delete dynamic array
					delete[] arrayB; /*delete dynamic array*/ }
				break;
			case 2:
				if (invalidMatrix(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ cout << "ERROR: File 1 and 2 are incompatible together.\n"; return 0; }
				else { //almost identical to the code above.
					arrayManager *arrayA = new arrayManager[numOfLinesA];
					arrayManager *arrayB = new arrayManager[AandB];
					arrayMatrixParse(a,arrayA, maxIfileOne, maxJfileOne);
					arrayMatrixParse(b,arrayB, maxIfileTwo, maxJfileTwo);
					outerRecursion(0,arrayA,arrayB,AandB,numOfLinesA, numOfLinesB, true); //add array recursively.
				 	sortArray(arrayB, AandB);
					printToFile(arrayB, AandB, c);
					delete[] arrayA;
				 	delete[] arrayB; }
				break;
			case 3:
				if (invalidMatrix(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ cout << "ERROR: File 1 and 2 are incompatible together.\n"; return 0; }
				else {
					node *rootA = new node, *rootB = new node;
					linkedListMatrixParse(a, rootA, maxIfileOne, maxJfileOne);
					linkedListMatrixParse(b, rootB, maxIfileTwo, maxJfileTwo);
					addLinkedListNonRecursive(rootA, rootB);
				  sortlinkedList(rootB);
					printToFile(rootB, c);
					deleteList(rootA);
					deleteList(rootB); }
				break;
			case 4:
				if (invalidMatrix(a,b, maxIfileOne, maxJfileOne, maxIfileTwo, maxJfileTwo) == 0){ cout << "ERROR: File 1 and 2 are incompatible together.\n"; return 0; }
				else {
					node *rootA = new node, *rootB = new node;
					linkedListMatrixParse(a, rootA, maxIfileOne, maxJfileOne);
					linkedListMatrixParse(b, rootB, maxIfileOne, maxJfileOne);
					outerRecursion(rootA, rootB);
					sortlinkedList(rootB);
					printToFile(rootB, c);
					deleteList(rootA);
					deleteList(rootB); }
				break;
			case 5:
				return 0;
			}
		}

    else { //if files are not found.
			cout << "ERROR: File 1 or File 2 not found. \n";
    	outfile.open(c.c_str());
    	outfile.close(); //close file stream for file not found error.
    	file1.close(); //close file stream for file not found error.
    	file2.close(); //close file stream for file not found error.
    	return 0;
    }

		file1.close(); //close file stream assuming everything worked.
		file2.close(); //close file stream assuming everything worked.
		return 0;
}

int checkOperation(string operation, string recursive, string storage){
	//controls what operation is specified by user, and returns a specific value to be controled by switch case.
	if (operation == "add"){
		if ((storage == "array" || storage == "") && (recursive == "N" || recursive == "")){
				cout << "adding arrays, non recursively" << endl;
				return 1;
		}
		else if ((storage == "array" || storage == "") && (recursive == "Y")){
				cout << "adding arrays, recursively" << endl;
				return 2;
		}
		else if ((storage == "linkedlist") && (recursive == "N" || recursive == "")){
				cout << "adding linkedlists, non recursively" << endl;
				return 3;
		}
		else if ((storage == "linkedlist") && (recursive == "Y")){
				cout << "adding linkedlists, recursively" << endl;
				return 4;
		}
	}
	else if (operation == "multiply"){
			cout << "ERROR: Multiplication not implemented. Wait until future homework. " << endl;
			return 5;
	}
	else {
			cout << "ERROR: Invalid operation, please type either add or multiply." << endl;
			return 5;
	}
	return 0;
}

int invalidMatrix(string a,string b, int &maxIfileOne, int &maxJfileOne, int &maxIfileTwo, int &maxJfileTwo){
	ifstream file1, file2;
	string currentString;
	int fileOneI = 0, fileOneJ = 0, fileTwoI = 0, fileTwoJ = 0;
	int tempFileOneI = 0, tempFileOneJ = 0, tempFileTwoI = 0, tempFileTwoJ = 0;

	file1.open(a.c_str());
	file2.open(b.c_str());

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

	if(tempFileOneI==tempFileTwoI && tempFileOneJ==tempFileTwoJ){
		return 1;
	}
		file1.close();
		file2.close();
		return 0;
}
