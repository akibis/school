/*
 Name: HW1.cpp
 ID: 912642515
 Author: Aleksandr Kibis
 Date: 09/06/13 15:46
 Compiler: 
 Description: ...............
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	cout << "HOMEWORK QUESTION 11" 
		 << endl 
		 << endl;

	// First file
	string firstFile;
	ifstream inStream;
	cout << "Please specify first file path: ";
	cin >> firstFile;
	cout << "\nChosen file path is: " << firstFile << endl;
	inStream.open(firstFile);

	// Fail clause
	if (inStream.fail()){
		cout << "Opening first file failed, the program will now exit.\n";
		exit(1);
	}

	// Vector sizing
	cout << "\nStarting vector sizing.\n";

	int temp = 0;
	int count = 0;
	while (inStream >> temp){
		count++;
	}

	// Vector initialization 
	vector<int> vectorArray(count);
	int firstSize = count;

	// Reset stream to read from beginning
	inStream.clear();
	inStream.seekg(0, ios::beg);

	// Vector first push
	cout << "Starting vector push.\n";

	int i = 0;
	while (inStream >> temp){
		vectorArray[i++] = temp;
	}

	// first vector print

	cout << "First file contents: \n";

	for (int i=0; i< count; i++){
	cout << vectorArray[i] << endl;
	}

	// Close first file
	inStream.close();
	
	// Second file
	string secondFile;
	cout << "\n*********************************\n" 
		 << "Please specify second file path: ";
	cin >> secondFile;
	cout << "\nChosen file path is: " << secondFile << endl;

	inStream.open(secondFile);
	
	// Fail clause
	if (inStream.fail()){
		cout << "Opening second file failed, the program will now exit.\n";
		exit(1);
	}

	// Vector Resize
	cout << "Starting vector sizing.\n";
	
	temp = 0;
	count = 0;
	while (inStream >> temp){
		count++;
	}
	vectorArray.resize(vectorArray.size() + count);

	// Reset stream
	inStream.clear();
	inStream.seekg(0, ios::beg);
	
	// Vector second push
	cout << "Starting vector push.\n";

	while (inStream >> temp){
		vectorArray[i++] = temp;
	}

	// Print unsorted items
	cout << "Pre-sort print: \n";
	
	for (int i=0; i< vectorArray.size(); i++){
	cout << vectorArray[i] << endl;
	}

	// bubble sort
	cout << "Starting bubble sort." << endl;

	bool swapped = true;
	int temp1 = 0;
	int j = 0;
	while (swapped) {
		swapped = false;
		j++;
		for (int i=0; i < (signed)vectorArray.size() - 1; i++){	
			if (vectorArray[i] > vectorArray[i+1]){
				temp1 = vectorArray[i];
				vectorArray[i] = vectorArray[i+1];
				vectorArray[i+1] = temp1;
				swapped = true;
			}		
		}
	}

	// print sorted vector
	cout << "Sorted list: \n";
	
	for (int i=0; i< (signed)vectorArray.size() ; i++){
	cout << vectorArray[i] << endl;
	}

return 0;
}