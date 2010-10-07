#include <map>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <regex.h>
#include <cstdlib>
#include <cstring>

using namespace std;

#ifndef __ANALYSIS_H__
#define __ANALYSIS_H__

bool has_word_author(string & text);
bool has_word_source(string & text);
bool has_word_copyright(string & text);
bool has_link_to_main_page(map<string,string> & attr);
bool has_word_site_or_paper(string & text);

string extract_author(string text);
string extract_source(string text);

string find_author(string & text);
string find_source(string & text);

float all_words_relate_date(string text);
bool match(string & text, string & pat);
#endif
