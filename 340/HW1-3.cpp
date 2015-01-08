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

//void dropSpecialChars(vector<string>& text);

int main() {
	cout << "************* Homework Question #3 **************\n"
		 << endl
		 << endl;

	vector <string> text;
	string word;
	ifstream inStream;
	inStream.open("C:/Users/rusky/Desktop/par.txt");

	while (inStream >> word){
		text.push_back(word);
	}

	cout << "\nBefore\n\n" << text[12] << endl;
	for (int i=0; i < (signed)text.size(); i++){
		cout << text[i];
	}
	//dropSpecialChars(& text);


	// Remove special characters
	for (unsigned int i=0; i < text.size(); i++){
		for (unsigned int j=0; j < text[i].size(); j++){
			if ((int)text[i][j] < 65 || (int)text[i][j] > 90){
				text[i][j] = NULL;
			}
		}
	}

	cout << "After\n\n" << text[12] << endl;
	for (int i=0; i < (signed)text.size(); i++){
		cout << text[i] << endl;
	}
	return 0;
}
//void dropSpecialChars(vector<string>& text){
//	for (unsigned int i=0; i < text.size(); i++){
//		for (unsigned int j=0; j < text[i].size(); j++){
//			if ((int)text[i][j] < 65 || (int)text[i][j] > 90){
//				text[i][j] = NULL;
//			}
//		}
//	}
//}