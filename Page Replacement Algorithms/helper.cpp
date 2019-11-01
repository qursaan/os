#include "helper.h"
#include <iostream>

void printArray(int *a, int array_size){
    std::cout << "[ ";
	for(int  i = 0 ; i< array_size ; i++)
	{
		if(a[i] !=-1){
			std::cout << a[i] << " |";
		}else{
			std::cout << "X |" ;
		}
	}
	 std::cout <<"\b]"<< std::endl;
}

int sequenialSearch(int *a, int array_size, int key){
	for(int i=0 ; i<array_size ; i++)
	{
		if(key == a[i])	return i;
	}
	return -1;
}
