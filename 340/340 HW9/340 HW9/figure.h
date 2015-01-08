/**
	@File: figure.h
	@Author: Aleksandr Kibis
	@Date: 12/10/2013
*/
#ifndef _FIGURE_H
#define _FIGURE_H

#include <string>
#include <iostream>

using namespace std;

class Figure{
	public:
		Figure();
		virtual void draw();
		virtual void erase();
		void center();

	private:
};

#endif