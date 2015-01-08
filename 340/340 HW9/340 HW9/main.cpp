/**
	@File: main.cpp
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/

#include <iostream>
#include "figure.h"
#include "rectangle.h"
#include "triangle.h"

using std::cout;

int main()
{
Triangle tri;
tri.draw(); 

cout << "\nDerived class Triangle object calling" << " center().\n";
tri.center();

Rectangle rect;
rect.draw();
cout << "\nDerived class Rectangle object calling" << " center().\n";
rect.center();
return 0;
}