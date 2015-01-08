/* 
 * File:   main.cpp
 * Author: Aleksandr Kibis
 *
 * Created on December 2, 2013, 4:40 PM
 */

#include <iostream>
#include "linkedList.h"
#include "listExceptions.h"

using namespace std;

int main() 
{

    List aList;
    List bList;
    
    try{
		// load aList
        aList.insert(50);
        aList.insert(30);
		aList.insert(20);

        
		// load bList
        bList.insert (7);
        
        
        cout <<"aList:\n" << aList << endl;
        
        
    }catch (ListException& e1)
    {
        cerr << e1.what();
    }catch (ListIndexOutOfRangeException& e2)
    {
        cerr << e2.what();
    }
       
	cout << "Remove 50\n";
	aList.remove(50);
	cout << "aList: " << aList << endl;

	const int x = 30;
	cout << "Test retrieve function, grab 30\n";
	if(aList.retrieve(30) == true)
		cout << "True\n";

	cout << "Check find function: find 20" << endl;

	
    
 
}

