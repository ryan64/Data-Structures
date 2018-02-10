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
	int temp[2] = {0};
	double tempValue = 0; 
	int counter = 0;

	while (getline(infile, currentString)){
		stringstream ss(currentString); 
		ss >> temp[0] >> temp[1] >> tempValue; 
		if (currentString.length() == 0 || currentString[0] == '#' || isalpha(currentString[0])){ continue; } //skip lines if junk data is in file.
			(array+counter)->i = temp[0]; //store i in appropriate element in array
			(array+counter)->j = temp[1]; //store j in appropriate element in array
			(array+counter)->value = tempValue; //store value in appropriate element in array
			cout << (array+counter)->i << " " << (array+counter)->j << " " << (array+counter)->value << endl; 
			counter++; //increment counter to go to next element in array.
	}
	cout << endl; 
	infile.close(); 
}
