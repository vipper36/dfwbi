#include "analysis.h"
#include "BlockUtils.h"
#include <iostream>
#include "stringutil.h"

bool has_word_author(string & text) {
    size_t f = text.find("作者");
    if (f != string::npos)
        return true;
    f = text.find("记者");
    if (f != string::npos)
        return true;
    f = text.find("文/");
    if (f != string::npos)
        return true;
    f = text.find("文／");
    if (f != string::npos)
        return true;
    return false;
}

bool has_word_source(string & text) {
    size_t f = text.find("来源");
    if (f != string::npos)
        return true;
    f = text.find("转载");
    if (f != string::npos)
        return true;
    return false;
}

bool has_word_copyright(string & text) {
    bool b = false;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(\\([Cc]opyright\\)\\|\\(\\版权.*授权\\)\\|\\(\\ICP\\)\\)", flag);
    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            b = true;
        }
    }
    regfree(&reg);
    return b;
}

bool has_link_to_main_page(map<string, string> & attr) {
    map<string, string>::iterator it = attr.find("href");
    if (it != attr.end()) {
        string & href = it->second;
        if (href.at(href.size() - 1) == '/')
            return true;
    }
    return false;
}

bool has_word_site_or_paper(string & text) {
    bool b = false;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(\\(网\\|报\\|社\\)\\( \\|　\\|-\\)\\)\\|\\(\\(网\\|报\\|社\\)$\\)", flag);
    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            b = true;
        }
    }
    regfree(&reg);
    return b;
}

string extract_author(string text) {
    //    LOG << "text: " << text << endl;
    string author;
    int flag = 0;
    regex_t reg;
    //int r = regcomp(&reg, "\\(^\\|（\\|(\\| \\|　\\)\\(作者\\|记者\\|文\\)\\(／\\|/\\|:\\|：\\| \\|　\\)\\(\\s\\|　\\)*\\([^ ]\\{,30\\}\\?\\)\\(来源\\|[0-9]\\|转载\\|\\s\\|　\\| \\|$\\|[ ()}]\\|（\\|）\\)", flag);
    int r = regcomp(&reg, "\\(^\\|（\\|(\\| \\|　\\)\\(作者\\|记者\\|文\\)\\(／\\|/\\|:\\|：\\| \\|　\\)\\(\\s\\|　\\)*\\([^ ()（）]\\{,30\\}\\?\\)\\(来源\\|[0-9]\\|转载\\|\\s\\|　\\| \\|$\\|[ ()}]\\|（\\|）\\)", flag);
    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        string_replace(text, string("\n"), string("  "));
        //        LOG << "text: " << text << endl;
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < nmatch; i++) {
                                LOG << "group: " << i << endl;
                if (pm[i].rm_so != -1) {
                    if (i == 5) {
                        int n = pm[i].rm_eo - pm[i].rm_so;
                        char buf[n + 1];
                        strncpy(buf, text.c_str() + pm[i].rm_so, n);
                        buf[n] = 0;
                                                cout<<i<<" "<<buf<<endl;
                        author = string(buf);
                    }
                }
            }
        }
    }
    //    LOG << "release pattern\n";
    regfree(&reg);
    //    LOG << "release pattern\n";
    return author;
}

string extract_source(string text) {
    string source;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(^\\|（\\|(\\| \\|　\\)\\(来源\\|转载\\)\\(:\\|：\\| \\|　\\)\\(\\s\\|　\\)*\\([^ ()（）]\\{,100\\}\\?\\)\\(文／\\|文/\\|文章\\|[0-9]\\|作者\\|记者\\|\\s\\|　\\|[ {}()]\\|（\\|）\\|$\\)", flag);
    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        string_replace(text, string("\n"), string("  "));
        //        LOG<<"text:"<<text<<endl;
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < nmatch; i++) {
                if (pm[i].rm_so != -1) {
                    if (i == 5) {
                        int n = pm[i].rm_eo - pm[i].rm_so;
                        char buf[n + 1];
                        strncpy(buf, text.c_str() + pm[i].rm_so, n);
                        buf[n] = 0;
                        source = string(buf);
                    }
                }
            }
        }
    }

    //    LOG<<"buffer"<<(long)reg.buffer<<endl;
    //    LOG<<"fastmap"<<(long)reg.fastmap<<endl;
    regfree(&reg);
    return source;
}

string find_author(string & text) {
    string author("");
    int len = text.length();
    if (len > 1024) {
        string start, end;
        size_t found = text.rfind("。", 512);
        if (found != string::npos) {
            start = text.substr(0, found);
//            cout<<"[find author] start text: "<< start <<endl;
            author = extract_author(start);
        }
        if (author.compare("") != 0)
            return author;

        found = text.find("。", len - 512);
        if (found != string::npos) {
            end = text.substr(found);
//            cout<<"[find author] end text: "<< end <<endl;
            author = extract_author(end);
        }
        if (author.compare("") != 0)
            return author;
    } else {
        author = extract_author(text);
    }
    return author;
}

string find_source(string & text) {
    string source("");
    int len = text.length();
    if (len > 1024) {
        string start, end;
        size_t found = text.rfind("。", 512);
        if (found != string::npos) {
            start = text.substr(0, found);
            source = extract_source(start);
        }
        if (source.compare("") != 0)
            return source;

        found = text.find("。", len - 512);
        if (found != string::npos) {
            end = text.substr(found);
            source = extract_source(end);
        }
        if (source.compare("") != 0)
            return source;
    } else {
        source = extract_source(text);
    }
    return source;
}

float all_words_relate_date(string text) {
    float ret = 0.0;
    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "\\(.*\\)\\(年\\)\\(.*\\)\\(月\\)\\([^星期]*\\)\\(日\\)\\([^星期]*\\)\\(星期\\)\\?\\(.*\\)", flag);
    string date_pat("^\\([0-9]\\|０\\|１\\|２\\|３\\|４\\|５\\|６\\|７\\|８\\|９\\|一\\|二\\|三\\|四\\|五\\|六\\|日\\|年\\|月\\|星期\\)\\+$");

    int date_words_length = 0;

    if (r == 0) {
        size_t nmatch = 10;
        regmatch_t pm[nmatch];
        string_replace(text, string("\\(\n\\| \\|　\\)\\+"), string(""));
        //        cout << "text:" << text << endl;
        int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
        if (!r) {
            for (int i = 0; i < nmatch; i++) {
                if (pm[i].rm_so != -1) {
                    if (i > 0 && i < 10) {
                        int n = pm[i].rm_eo - pm[i].rm_so;
                        char buf[n + 1];
                        strncpy(buf, text.c_str() + pm[i].rm_so, n);
                        buf[n] = 0;
                        string s(buf);
                        bool is_date_word = match(s, date_pat);
                        if (is_date_word) {
                            date_words_length += n;
                        }
                        //                        cout << i << ":" << s << " " << is_date_word <<"\n";
                    }
                }
            }
        }
    }

    ret = date_words_length / (float) (text.size());

    regfree(&reg);
    return ret;
}

bool match(string & text, string & pat) {
    bool ret = false;

    if (text.size() > 0) {
        int flag = 0;
        regex_t reg;
        int r = regcomp(&reg, pat.c_str(), flag);
        if (r == 0) {
            size_t nmatch = 10;
            regmatch_t pm[nmatch];

            int r = regexec(&reg, text.c_str(), nmatch, pm, 0);
            if (!r) {
                ret = true;
            }
        }

        regfree(&reg);
    }
    return ret;
}
