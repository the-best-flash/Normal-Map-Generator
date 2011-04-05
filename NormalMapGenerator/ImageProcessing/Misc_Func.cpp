/***************************************************************************
    Normal Map Generator Copyright © 2010 Colton Manville
    (Contact: the_best_flash@hotmail.com)

    This file is part of Normal Map Generator.

    Normal Map Generator is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Normal Map Generator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Normal Map Generator.

    If not, see <http://www.gnu.org/licenses/gpl.txt>.
***************************************************************************/

/** \file Misc_Func.cpp
* Contains Various functions
*/

#define __BUILD_ME__
#include "Misc_Func.h"

string QstrTostr(QString str)
{
    char* c_str = new char[str.count() + 1];
    int i;
    string s;

    for( i = 0; i < str.count(); i++)
    {
        c_str[i] = str[i].toAscii();
    }

    c_str[i] = '\0';

    s = c_str;
    delete [] c_str;

    return s;
}

/*! Limits the specified number to a number between 0 and 'limit'. (Ex. 12.1 limited to 10.0 becomes 2.1)
	 \note This does not return a value. The value that is passed in is modified.
	 \param[in] &num Number to be limited and modified.
	 \param[in] limit The value to limit the number to */
void limit_num(float & num, float limit)
{
	if( num > limit )
	{
		while( num > limit )
			num -= limit;
	} else if ( num < 0 )
	{
		while( num < 0 )
			num += limit;
	}
}

/*! Clears the specified c-syle string
	 \param[in] str[] The string to clear
	 \param[in] len The length of the c-sytle string */
void strclr( char str[], int len)
{
	for( int i = 0; i < len; i++)
		str[i] = '\0';
}

/*! Returns the position of the character in the c-sytle string
	 \param[in] str[] The string to search
	 \param[in] ch The character to search for*/
int strrpos( char str[], char ch )
{
	int pos = -1;
	int i;

	for( i = 0; i < (int)strlen(str); i++)
		if( str[i] == ch )
			pos = i;

	return pos;
}

int find_drive(int type, const char * string)
{
	int i = 0;
	int count = 0;

	char * str = new char[(int)strlen(string) + 1];

	strcpy(str, string);

	str[(int)strlen(string)] = '\0';

	tolower( str );

	while( str[i] != '\0' )
	{
		if( str[i] == 'e' && type == 1)
		{
			i++;
			while( str[i] != '\0' )
			{
				if( str[i] != ' ' && str[i] != '\"' )
				{
					delete [] str;
					return i;
				}

				i++;
			}
		}
		else if( str[i] == 'r' && type == 2)
		{
			i++;
			while( str[i] != '\0' )
			{
				if( str[i] != ' ' && str[i] != '\"' )
				{
					delete [] str;
					return i;
				}

				i++;
			}
		}
		else if( str[i] == 'e' && type == 3)
		{
			count++;
			if( count == 2 )
			{
				i++;
				while( str[i] != '\0' )
				{
					if( str[i] != ' ' && str[i] != '\"' )
					{
						delete [] str;
						return i;
					}

					i++;
				}
			}
		}
		i++;
	}

	delete [] str;
	return -1;
}

/*! Converts a string to lowercase
	 \param[in] str[] The string to convert */
void tolower( char str[] )
{
	int i = 0;

	while( str[i] != '\0' )
	{
                str[i] = tolower(str[i]);

		i++;
	}
}

float * set_up_array(float * arr, int cur_num, int count, float defalut_val)
{
	float * temp_float = NULL;
	int j;

	temp_float = new float[count];
	for( j = 0; j < cur_num; j++)
		temp_float[j] = arr[j];
	delete [] arr;
	arr = new float[count];
	for( j = 0; j < cur_num; j++)
		arr[j] = temp_float[j];
	for( j = cur_num - 1; j < count; j++)
		arr[j] = defalut_val;

	delete [] temp_float;
	temp_float = NULL;

	return arr;
}

int * set_up_array(int * arr, int cur_num, int count, int default_val)
{
	int * temp_int = NULL;
	int j;

	temp_int = new int[count];
	for( j = 0; j < cur_num; j++)
		temp_int[j] = arr[j];
	delete [] arr;
	arr = new int[count];
	for( j = 0; j < cur_num; j++)
		arr[j] = temp_int[j];
	for( j = cur_num - 1; j < count; j++)
		arr[j] = default_val;

	delete [] temp_int;
	temp_int = NULL;

	return arr;
}

bool * set_up_array(bool * arr, int cur_num, int count, bool default_val)
{
	bool* temp_bool = NULL;
	int j;

	temp_bool = new bool[count];
	for( j = 0; j < cur_num; j++)
		temp_bool[j] = arr[j];
	delete [] arr;
	arr = new bool[count];
	for( j = 0; j < cur_num; j++)
		arr[j] = temp_bool[j];
	for( j = cur_num - 1; j < count; j++)
		arr[j] = default_val;

	delete [] temp_bool;
	temp_bool = NULL;

	return arr;
}

bool * fill_array( int & cur_num, int count, bool val)
{
	int j;
	bool * arr;

	arr = new bool[count];
	for( j = 0; j < count; j++)
		arr[j] = val;
	cur_num = count;

	return arr;
}

int * fill_array( int & cur_num, int count, int val)
{	
	int j, *arr;

	arr = new int[count];
	for( j = 0; j < count; j++)
		arr[j] = val;
	cur_num = count;

	return arr;
}

float * fill_array( int & cur_num, int count, float val)
{
	int j;
	float * arr;

	arr = new float[count];
	for( j = 0; j < count; j++)
		arr[j] = val;
	cur_num = count;

	return arr;
}

bool * add_val(bool * arr, int & cur_num, bool val)
{
	int j;
	bool * temp_bool = NULL;

	if( cur_num > 0)
	{
		temp_bool = new bool[cur_num + 1];
		for( j = 0; j < cur_num; j++)
			temp_bool[j] = arr[j];
		delete [] arr;
		arr = new bool[cur_num + 1];
		for( j = 0; j < cur_num + 1; j++)
			arr[j] = temp_bool[j];

		delete [] temp_bool;
		temp_bool = NULL;
	}
	else
	{
		arr = new bool[1];
	}

	arr[cur_num] = val;
	cur_num++;

	return arr;
}

float * add_val(float * arr, int & cur_num, float val)
{
	int j;
	float * temp_float = NULL;

	if( cur_num > 0)
	{
		temp_float = new float[cur_num + 1];
		for( j = 0; j < cur_num; j++)
			temp_float[j] = arr[j];
		delete [] arr;
		arr = new float[cur_num + 1];
		for( j = 0; j < cur_num + 1; j++)
			arr[j] = temp_float[j];

		delete [] temp_float;
		temp_float = NULL;
	}
	else
	{
		arr = new float[1];
	}
	
	arr[cur_num] = val;
	cur_num++;

	return arr;
}

int * add_val(int * arr, int & cur_num, int val)
{
	int j, *temp_int;

	if( cur_num > 0)
	{
		temp_int = new int[cur_num + 1];
		for( j = 0; j < cur_num; j++)
			temp_int[j] = arr[j];
		delete [] arr;
		arr = new int[cur_num + 1];
		for( j = 0; j < cur_num + 1; j++)
			arr[j] = temp_int[j];

		delete [] temp_int;
		temp_int = NULL;
	}
	else
	{
		arr = new int[1];
	}

	arr[cur_num] = val;
	cur_num++;

	return arr;
}

string* add_string( string * list, int & size, string item)
{
	string * temp = NULL;
	int i;

	if( size > 0 )
	{
		temp = new string[size + 1];
		for( i = 0; i < size; i++)
			temp[i] = list[i];
		list = new string[size + 1];
		for( i = 0; i < size; i++)
			list[i] = temp[i];
		list[size] = item;
		size++;
	}
	else
	{
		list = new string[1];
		list[0] = item;
		size = 1;
	}

	delete [] temp;

	return list;
}

string toupper( char* str )
{
	int i;

	string temp;

	for( i = 0; i < (int)strlen(str); i++ )
		str[i] = toupper(str[i]);

	temp = str;

	return temp;
}

//Equations From
//Grokking the GIMP
//By Carey Bunks
//http://gimp-savvy.com/BOOK/index.html?node55.html
float overlay(float a, float b)
{
        return (a * screen(a, b) + (1.0f - a) * (a * b));
}

//Equations From
//Grokking the GIMP
//By Carey Bunks
//http://gimp-savvy.com/BOOK/index.html?node55.html
float screen( float a, float b )
{
        //return 1.0f - (1.0f - b) * (1.0f - a);
        return a + b - (b * a);
}
