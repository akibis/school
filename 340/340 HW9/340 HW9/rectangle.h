/**
	@File: rectangle.h
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "figure.h"

class Rectangle: public Figure
{
	public:
		Rectangle();
		void draw();
		void erase();
	private:
		int length;
		int width;
		int* centerPoint;
};

#endif