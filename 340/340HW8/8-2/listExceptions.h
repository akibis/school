/*
  Name: listExceptions.h
  Desc: declare two exception classes that are specific to List
  Copyright: 
  Author: Aleksandr Kibis
  Date: 19/09/11 18:37
  Modified: November 20, 2013
  Description: 
*/
#ifndef _LIST_EXCEPTIONS_H
#define _LIST_EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class ListIndexOutOfRangeException : public out_of_range
{
public:
  
  /**/
  ListIndexOutOfRangeException(const string & message = "")
      : out_of_range(message.c_str())
  { }  // end constructor
  /**/
  //virtual const char* what() const throw()
  //{return "list: out of range";}
}; // end ListIndexOutOfRangeException


class ListException : public logic_error
{
public:
  
  /**/    
  ListException(const string & message = "")
      : logic_error(message.c_str())
  { }  // end constructor
  /**/
  // virtual const char* what() const throw()
  //{return "list: logic error";}  //list is full
}; // end ListException

#endif
