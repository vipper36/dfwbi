#include "stringutil.h"
#include <cctype>

using namespace std;

string to_lower_case(string & str)
{
    const char * data = str.c_str();
    int len = str.length();
    char lower_data[len+1];
    for(int i = 0; i < len; i++){
        lower_data[i] = tolower(*data++);
    }
    lower_data[len] = 0;
    return string(lower_data);
}

nsCString to_lower_case(nsCString & str)
{
    const char * data = str.get();
    int len = str.Length();
    char lower_data[len+1];
    for(int i = 0; i < len; i++){
        lower_data[i] = tolower(*data++);
    }
    lower_data[len] = 0;
    return nsCString(lower_data);
}

void string_filter(string & s) {
    //string_filter(s,0);
    string_filter2(s);
}

void string_filter(string & s, string & invalid_ch) {
    string_filter(s, 0, invalid_ch);
}

void string_filter(string & s, int s_pos, string & invalid_ch) {
    if (s_pos >= s.length()) return;
    char c = s.at(s_pos);
    size_t found = invalid_ch.find(c);
    if (found != string::npos) {
        s.replace(s_pos, 1, "");
        return string_filter(s, s_pos, invalid_ch);
    }
    return string_filter(s, ++s_pos, invalid_ch);
}

void string_filter2(string & s) {
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(#\\|\n\\| \\|　\\|\\s\\|\r\\|，\\|。\\|：\\|·\\|“\\|[,.:\"|]\\)\\+", flag);
    if (r != 0) {
        char ebuf[128];
        regerror(r, &reg, ebuf, sizeof (ebuf));
        cout << "regexp pattern error: " << ebuf << "\n";
    } else {
        size_t nmatch = 1;
        regmatch_t pm;
        int r = regexec(&reg, s.c_str(), nmatch, &pm, 0);
        if (!r) {
            int pos = 0;
            if (pm.rm_so != -1) {
                int len = pm.rm_eo - pm.rm_so;
                s.erase(pm.rm_so, len);
                string_filter2(s);
            }
        }
        /*
        else
        {
                char ebuf[128];
                regerror(r, &reg, ebuf, sizeof(ebuf));
                cout<<"regexp match error: "<<ebuf<<"\n";
        }
         */
    }
    regfree(&reg);
}

void string_replace(string & s, string pat, string replace) {
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, pat.c_str(), flag);
    if (r != 0) {
        char ebuf[128];
        regerror(r, &reg, ebuf, sizeof (ebuf));
        LOG << "string replace regexp pattern error: " << ebuf << "\n";
        return;
    } else {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        int r = regexec(&reg, s.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < 1; i++) {
                if (pm[i].rm_so != -1) {
                    int len = pm[i].rm_eo - pm[i].rm_so;
                    s.erase(pm[i].rm_so, len);
                    s.insert(pm[i].rm_so, replace);
                    string_replace(s, pat, replace);
                }
            }
        }
    }
    regfree(&reg);
}

int get_integer(stringstream & ss) {
    string line = get_line(ss);
    //cout << "line: "<<line<<"end"<<"\n";
    stringstream ss1;
    ss1 << line;
    int i = 0;
    ss1 >> i;
    return i;
}

string get_line(stringstream & ss) {
    string line;
    char c[2];
    c[1] = 0;
    while (ss.good()) {
        c[0] = ss.get();
        if (c[0] == '\n') break;
        line.append(c);
    }
    return line;
}