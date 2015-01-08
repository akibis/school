/**
	@File: triangle.h
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/
#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include "figure.h"

class Triangle: public Figure
{
	public:
		Triangle();
		void Triangle::draw();
		void Triangle::erase();

	private:
		int sideOne;
		int sideTwo;
		int sideThree;
};

#endif