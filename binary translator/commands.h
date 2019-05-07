#include "enums.h"

#define db(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 1);\
	this -> output_cur += 1;}

#define dw(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 2);\
	this -> output_cur += 2;}

#define dd(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 4);\
	this -> output_cur += 4;}

#define dq(value)\
	{size_t temp = value;\
	memcpy (this -> output_cur, &temp, 8);\
	this -> output_cur += 8;}

#define GETCOM this->get_com()
