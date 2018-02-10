#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
using namespace std;

void swap(arrayManager* a, arrayManager* b){
	arrayManager temp = *a; //take arrayA contents, store it in temp.
	*a = *b; //take arrayB contents, store it in arrayA contents.
	*b = temp; //take temp contents, and store it in arrayB contents.
}  //swap elements.

void sortArrayBubbleSort(arrayManager *arrayResult, int resultSize, int &timeComplex){
	for (int x = 0; x < resultSize; x++){
		timeComplex++; 
		for (int y = 0; y < (resultSize - x - 1); y++){
			timeComplex++;
			if ((arrayResult+y)->i > (arrayResult+y+1)->i) 
				swap(arrayResult+y, arrayResult+y+1); //first check, if arrayB i is greater than array B i+1, swap everything.
			
			else if((arrayResult+y)->i == (arrayResult+y+1)->i && (arrayResult+y)->j > (arrayResult+y+1)->j)
				swap(arrayResult+y, arrayResult+y+1); //second check, if arrayB i matches arrayB i+1, but the j value of arrayB is greater than array B i+1, swap everything.
			timeComplex+=3; 
		}
	}
} //bubble sort algorithm implemented.

void sortArrayQuickSort(arrayManager *array, int left , int right, int &timeComplex){
	int i = left, j = right-1;
      arrayManager tmp;
      arrayManager pivot = array[(left + right-1) / 2];
 
      /* partition */
      while (i <= j) {
            while (array[i].i < pivot.i || array[i].i == pivot.i && array[i].j < pivot.j){
            	i++;
            	timeComplex+=3;
            }
            while (array[j].i > pivot.i || array[j].i == pivot.i && array[j].j > pivot.j){
                  j--;
              	  timeComplex+=3; 
            }
            if (i <= j) {
                  tmp = array[i];
                  array[i] = array[j];
                  array[j] = tmp;
                  i++;
                  j--; 
        	}
        timeComplex+=2; 
  	};
 
      /* recursion */
      if (left < j){
            timeComplex++; 
            sortArrayQuickSort(array, left, j, timeComplex);}
      if (i < right){
            timeComplex++;
            sortArrayQuickSort(array, i, right, timeComplex);}
}