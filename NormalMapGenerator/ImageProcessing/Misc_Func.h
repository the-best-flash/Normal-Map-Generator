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

/** \file Misc_Func.h
* Contains Various functions
*/

#include <QString>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include "My_Math.h"
using namespace std;

#ifndef __MISC_FUNC__H__
#define __MISC_FUNC__H__

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#endif

#ifndef _SCL_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <string>
#include <cctype>

using namespace std;

#define PI       3.14159265358979323846

#ifndef NULL
	#define NULL 0
#endif

 string QstrTostr(QString str);
 int  strrpos( char str[], char ch );
 void  strclr( char * str, int len);
 void  limit_num(float & num, float limit);
 int  find_drive(int type, const char * str);
 void  tolower( char str[] );
 float *  add_new_float();
 float *  set_up_array(float * arr, int cur_num, int count, float default_val);
 int *  set_up_array(int * arr, int cur_num, int count, int default_val);
 bool *  set_up_array(bool * arr, int cur_num, int count, bool default_val);
 bool *  fill_array( int & cur_num, int count, bool val);
 int *  fill_array( int & cur_num, int count, int val);
 float *  fill_array( int & cur_num, int count, float val);
 bool *  add_val(bool * arr, int & cur_num, bool val);
 float *  add_val(float * arr, int & cur_num, float val);
 int *  add_val(int * arr, int & cur_num, int val);
 string*  add_string( string * list, int & size, string item);
 string  toupper( char* str );
 float overlay(float a, float b);
 float screen(float a, float b);

#endif
