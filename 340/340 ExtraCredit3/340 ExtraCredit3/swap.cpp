/**
@File: swap.cpp
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

#include "swap.h"

template<typename T>
void swap(const T & first, const T & second)
{
	T temp = first;
	first = second;
	second = temp;
}