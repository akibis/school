/**
	@File: triangle.cpp
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/

#include "triangle.h"

Triangle::Triangle():Figure()
{
	sideOne = 1;
	sideTwo = 1;
	sideThree = 1;
}

void Triangle::draw()
{
	cout << "Drawing triangle.\n";
}

void Triangle::erase()
{
	cout << "Erasing triangle.\n";
}