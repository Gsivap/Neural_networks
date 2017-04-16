#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {

	//Create a dynamic array to hold the values
	vector<int> numbers;
        vector<int> labels;
	int arr[1568000];
	int oneh [100000];
	//Create an input file stream
	ifstream in("file.txt",ios::in);
        

	/*
            As long as we haven't reached the end of the file, keep reading entries.
	*/
        int itern,il = 0;
	int number;  
	int la;
        while ( itern < 10000*784) {
		//Add the number to the end of the array
                in >> number;
		
		numbers.push_back(number);
		itern++;
	}

	//Close the file stream
	in.close();
ifstream l("onehot.txt",ios::in);
	        while (il < 1*10) {
		//Add the number to the end of the array
                l >> la;
		//printf("%d\n",la);
		labels.push_back(la);
		il++;
	}

	//Close the file stream
	l.close();
	

/*
	//Display the numbers
	//for (int iter = 0; iter <=4;iter++)
	//for(int j=0 ; j <2000; j++)
	for (int i=0; i<784; i++) {
		arr[0*784 + i] = numbers[((1*2000+0)*784)-1 + i];
		printf("%d\n",arr[0*784 + i]);
	}

/*
	for (int a = 0; a <=4;a++)
	for(int b=0 ; b <2000; b++)
	for (int c=0; c<10; c++) {
		oneh[b*10 + c] = labels[(a*2000+b)*10 + c];
		//printf("%d,iteration = %d\n",arr[j][i],j);
	}

	for (int check =0; check <784;check++)
		printf("%d\n",arr[check]);
*/
	return 0;

}
