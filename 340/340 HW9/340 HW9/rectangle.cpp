/**
	@File: rectangle.cpp
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/

#include "rectangle.h"



Rectangle::Rectangle():Figure()
{
	length = 2;
	width = 2;
	centerPoint = new int[2];
	centerPoint[0] = 1;
	centerPoint[1] = 1;
}

void Rectangle::draw()
{
	cout << "Drawing rectangle.\n";
}

void Rectangle::erase()
{
	cout << "Erasing rectangle.\n";
}