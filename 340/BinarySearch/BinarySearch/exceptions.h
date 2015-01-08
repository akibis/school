#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <exception>
#include <iostream>

using namespace std;

class My_Bad_Alloc_Exception: public bad_alloc {

public:
	virtual const char* what() const throw() {
		return "BadAllocException: ";
	}

};

#endif