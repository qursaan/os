#include "helper.h"
#include <iostream>

void printArray(int *a, int array_size)
{
    std::cout << "[ ";
    for(int  i = 0 ; i< array_size ; i++)
    {
        std::cout << a[i] << " |";
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
