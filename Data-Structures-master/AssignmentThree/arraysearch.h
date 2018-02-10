#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void checkSorted(arrayManager *array, int numOfLines, bool &isSort){
	for (int x = 0; x < numOfLines; x++){
		for (int y = 0; y < (numOfLines - x - 1); y++){
			if ((array+y)->i > (array+y+1)->i){ isSort = false; break;  }
			else if((array+y)->i == (array+y+1)->i && (array+y)->j > (array+y+1)->j){ isSort = false; break; }
		}
		if (isSort == false){ break; }
	}
}

int sequentialSearch(arrayManager *array, int numOfLines, int i, int j){
	bool isFound = false; 
	for (int x = 0; x < numOfLines; x++){
		if ((array[x].i == i && array[x].j == j)){isFound = true; return x;}
	}
	if (isFound == false){return -1;}
}

int binarySearch(arrayManager *array, int numOfLines, int i, int j){
	int min = 0;  
	int max = numOfLines; 
	while (min <= max) {
            int pivot = ((min + max) / 2);  
            if (array[pivot].i == i){
            	if (array[pivot].j == j){
                  return pivot;
              	}
              	else if (array[pivot].j > j){
              		max = pivot - 1; 
              	}
              	else 
              		min = pivot + 1; 
            }
            else if (array[pivot].i > i)
                  max = pivot - 1;
            else
                  min = pivot + 1;
     }
  	return -1;
}

void multiplyArrays(arrayManager *arrayA, arrayManager *arrayB, arrayManager *arrayResult, int numOfLinesA, int numOfLinesB, int resultSize, bool &isSortA, bool &isSortB, int maxIFileOne, int maxJFileOne, int maxIFileTwo, int maxJFileTwo, int &counter){
	if (isSortA == true && isSortB == true){
		cout << "Multiplying using binarySearch" << endl;
		for (int i = 0; i < maxIFileOne; i++){
			for (int j = 0; j < maxJFileTwo; j++){
				for (int k = 0; k < maxJFileOne; k++){
					int posA = binarySearch(arrayA, numOfLinesA, i+1, k+1);
					int posB = binarySearch(arrayB, numOfLinesB, k+1, j+1);
					if (posA == -1 || posB == -1 /*|| arrayA[posA].value == 0 || arrayB[posB].value == 0*/){continue; }
					else { 
						int posC = sequentialSearch(arrayResult, resultSize, i+1, j+1); 
						if (posC == -1){
							arrayResult[counter].i = i+1; 
							arrayResult[counter].j = j+1; 
							arrayResult[counter].value = arrayA[posA].value * arrayB[posB].value;
							counter++; 
						}
						else {
							arrayResult[posC].value += arrayA[posA].value * arrayB[posB].value;
						}
					}
				}
			}
		}
	} 
	else{
		cout << "Multiplying using sequentialSearch" << endl; 
		for (int i = 0; i < maxIFileOne; i++){
			for (int j = 0; j < maxJFileTwo; j++){
				for (int k = 0; k < maxJFileOne; k++){
					int posA = sequentialSearch(arrayA, numOfLinesA, i+1, k+1);
					int posB = sequentialSearch(arrayB, numOfLinesB, k+1, j+1);
					if (posA == -1 || posB == -1 /*|| arrayA[posA].value == 0 || arrayB[posB].value == 0*/){continue; }
					else { 
						int posC = sequentialSearch(arrayResult, resultSize, i+1, j+1); 
						if (posC == -1){
							arrayResult[counter].i = i+1; 
							arrayResult[counter].j = j+1; 
							arrayResult[counter].value = arrayA[posA].value * arrayB[posB].value;
							counter++; 
						}
						else {
							arrayResult[posC].value += arrayA[posA].value * arrayB[posB].value;
						}
					}
				}
			}
		}
	}
}