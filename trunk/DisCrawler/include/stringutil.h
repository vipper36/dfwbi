/* 
 * File:   stringutil.h
 * Author: ray
 *
 * Created on September 22, 2009, 1:55 PM
 */
#include <string>
#include <iostream>
#include <regex.h>
#include <sstream>
#include "property.h"
#include "nsStringAPI.h"

using namespace std;

#ifndef _STRINGUTIL_H
#define	_STRINGUTIL_H

string to_lower_case(string & str);
nsCString to_lower_case(nsCString & str);

void string_filter(string & s);
void string_filter2(string & s);
void string_filter(string & s, int s_pos, string & invalid_ch);
void string_filter(string & s, string & invalid_ch);
void string_replace(string & s, string pat, string r);
int get_integer(stringstream & ss);
string get_line(stringstream & ss);

#endif	/* _STRINGUTIL_H */

