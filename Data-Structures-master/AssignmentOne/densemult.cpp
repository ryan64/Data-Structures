#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "ArgumentManager.h"
using namespace std;
 
int size = 0; //holds value for size of matrix. 
int errorCheck(string a, string c); 
void parseData(double array[20][20], string a); //function declarations. 
void matrixMult(double array[20][20], double multArray[20][20]); 
void outputFile(double multArray[20][20], string c); 

int main(int argc, char *argv[]){
	ifstream infile; 
	ofstream outfile; 
	double array [20][20]; //declare array of maximum size that will store input file data.  
	double multArray [20][20]; //declare array of maximum size that will store the answer. 

	ArgumentManager am(argc, argv);
    string a = am.get("A");
    string c = am.get("C");
	infile.open(a.c_str()); //Open file based off argument 'String a'. 
	
	//if the file was found. 
	if (infile.is_open()){
		int numberRet = errorCheck(a, c);
		if (numberRet == 1){
			cout << "File is empty... aborting" << endl; 
			outfile.open(c.c_str()); 
			outfile.close(); 
			return 0; 
		}
		else if (numberRet == 2){
			cout << "File contains rectangular matrix... aborting" << endl; 
			outfile.open(c.c_str()); 
			outfile.close();
			return 0; 
		}
		else 
		parseData(array, a); //parse data and store in array. 
		matrixMult(array, multArray); //multiply matrix by itself and store in multArray. 
		outputFile(multArray, c); //output data to file based off argument 'String c'. 
		cout << "A: " << a << endl << "C: " << c << endl;
	}

	//if the file was not found. 
	else
	cout << "File not found... aborting" << endl; 
	infile.close(); //close file stream. 
	return 0; 
}

int errorCheck(string a, string c){
	int tempCol = 0; 
	int tempRow = 0; 
	ifstream infile; 
	string currentString;

	infile.open(a.c_str()); 
	getline(infile, currentString); 
	if (currentString.length() == 0) { //if file is empty. 
		return 1; 
	}

	else 
	getline(infile, currentString); 
	for (int i = 0; i < currentString.length(); i++){ //for loop will count number of columns.  
		if (currentString[i] == ' '){
			tempCol++; 
		}
	}
	tempCol = tempCol + 1;
	infile.close(); 
	infile.open(a.c_str()); 
	getline(infile, currentString); 
	while(!infile.eof()){ //for loop will count number of rows. 
	getline(infile, currentString);
	tempRow++; 			
	}
	tempRow = tempRow - 1;

	if (tempCol != tempRow){ //check to see that it is a square matrix. 
	return 2; 
	}
}

void parseData(double array[20][20], string a){
	ifstream infile; 
	infile.open(a.c_str()); 
	string currentString; 
	getline(infile, currentString); //Grabs first line of text file. 'Ex. # Matrix A, I matrix, notice zero entries are omitted, 2 dimensions
	getline(infile, currentString); //Grabs second line of text file. Or the first row of matrix.

	for (int i = 0; i < currentString.length(); i++){ //for loop will count the instances of ' ' and increment size by that number. 
		if (currentString[i] == ' '){
			size++; 
		}
	}

	size = size + 1; //because there is a space between the numbers, size needs to be incremented by 1, to determine amount of columns. 
	infile.close(); //close file stream, to reset point at which file stream is reading input file. 
	infile.open(a.c_str()); //open file again. 
	getline(infile, currentString); //grab first line of text file. 

	while (!infile.eof()){ //while not at end of file...
		for (int i = 0; i < size; i++){ //use nested for loop to properly access array blocks. 
			for (int j = 0; j < size; j++){
				infile >> array[i][j]; //parses individual strings and stores them in the necessary blocks in array.
			}
		}
	}

	infile.close(); 
}

void matrixMult(double array[20][20], double multArray[20][20]){
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			multArray[x][y]=0; //initialize contents of multArray to zero, before performing matrix multiplication.
		}
	}
	
	for (int i = 0; i < size; i++){ //triple for loop, the first two to correctly iterate through the array, and the third one to handle matrix mult. 
    	for (int j = 0; j < size; j++){
    		for (int k = 0; k < size; k++){
        	 multArray[i][j] = multArray[i][j] + (array[i][k] * array[k][j]); //store result into multArray. 
    		}
		}
	}
}

void outputFile(double multArray[20][20], string c){
	ofstream outfile; 
	outfile.open(c.c_str()); //open output file stream. 
	for (int i = 0; i < size; i++){ //use nested for loop to properly access array blocks. 
		for (int j = 0; j < size; j++){
			outfile << fixed << setprecision(2) << multArray[i][j] << " "; //modified output to append decimal points. 
		}
		outfile << endl; 
	}
	outfile.close(); //close file stream. 
}