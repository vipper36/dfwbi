#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <map>
#include <list>
#include <string>
using namespace std;

#ifndef __DATE_FORMAT_H__
#define __DATE_FORMAT_H__

list< pair<string,int> > get_date_format(string & format);

string scan_date(char* date, string format,int len);

string get_date(string & date,string & date_format);
string get_date(string & date, string & format, string & output_format);

#endif
