/**
@File: array.h
@Author: Aleksandr Kibis
@Date: 12/12/2013
*/

template<typename T>
class Array{

public:
	Array(int initialSize);
	~Array();
	T & operator[](int i);

private:
	T *data;
	int size;
};


template<typename T>
Array<T>::Array(int initialSize)
{
	size = initialSize;
	data = new T[size];
};

template<typename T>
T &Array<T>::operator[](int i)
{
	return data[i];
};

template<typename T>
Array<T>::~Array()
{
	delete [] data;
};







