/**
	@File: figure.cpp
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/

#include "figure.h"

using std::cout;

Figure::Figure()
{

}

void Figure::draw()
{
	cout << "Drawing a figure.\n";
	
}

void Figure::erase()
{
	cout << "Erasing a figure.\n";
}

void Figure::center()
{
	cout << "Centering a figure.\n";
	erase();
	draw();
}
