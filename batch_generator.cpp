#include <fstream> 
#include <iostream> 
#include <stdlib.h> 
#include <ctime>    

using namespace std;

int main(int c, char** v){
	int n =1000;
	if(c>=2){
		n = stoi( v[1] );
	}
	srand( time(0) ); // generate random based on time
	
	ofstream f;
	f.open("bigfile.txt");
	int r;

	for(int i=0; i<n; i++)
	{
		r = rand()% 20 + 1;
		f << r  << ' ';
	}
	f.close();
	
	return 0;
}
