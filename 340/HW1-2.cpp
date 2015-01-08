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
	cout << "******************* HOMEWORK #1-2 ********************";

	ifstream inStream;
	string input;
	int temp = 0;
	int count = 0;
	int** matrix;

	cout << "Please enter square matrix size: ";
	cin >> input;

	inStream.open(input);
	while (inStream >> temp){
		count++;
	}

	int matrix[count][count];

	
	



}