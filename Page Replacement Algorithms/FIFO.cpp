#include <iostream>

using namespace std;
void printarray(int *a, int size){
	for(int  i = 0 ; i< size ; i++)
	{
		if(a[i] !=-1){
			cout << a[i] << "\t";
		}else{
			cout << "X\t" ;
		}
	}
	cout << endl;
}
int sequenialsearch(int *a, int size, int key){
	for(int i=0 ; i<size ; i++)
	{	
		if(key == a[i])	return i;
	}
	return -1;
}
int main(int argc, char**argv){
	int *p; //pointer to store array of memory
	if(argc<2){
		cout<<"Please enter memory size\n";
		return -1;
	}
	int memory_size = stoi(argv[1]); 
	p = new int[memory_size];
	//initalize array 
	for(int i=0; i<memory_size;  i++)
		p[i] = -1;
	
	int s = 0;//no of success
	int f = 0;//no of fault
	int t_data = argc - 2; //no of data
	int index = -1;//fifo  

	for(int j=0; j<t_data ; j++) // allocate data in memory
	{
		int data = stoi(argv[j+2]);
		//search to see if data is already in memory
		int r = sequenialsearch(p,memory_size, data);
		if(r == -1){ // not found
			index++; //fifo order
			if(index>=memory_size) 
				index=0;
			p[index] = data;
			f++;
		}else{
			s++;
		}
		printarray(p,memory_size);
	}

	double success_rate =s*1.0 / t_data;
	cout << "Success rate = " << s << "/" << t_data << "=" << success_rate << endl;
	cout << "Page Fault = " << f << endl;
	delete p; 
	return 0;
}
