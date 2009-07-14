#include "date.h"
#include <iostream>
#include <sstream>
#include <time.h>

list< pair<string,int> > get_date_format(string & format)
{
    string date_format("YMDHmS");
    list< pair<string,int> > m;

    const char * c = format.c_str();

    string sep;
    while(*c != '\0')
    {
        size_t f = date_format.find(*c);
        if(f != string::npos)
        {
            if(sep.compare("")!=0)
            {
                //cout<<sep<<" "<<sep.length()<<endl;
                m.push_back(pair<string,int>(sep,sep.length()));
                sep.clear();
            }
            int i = 1;
            while(*c == *(c+1))
            {
                c++;
                i++;
            }
            char ch = *c;
            if(*(c+1) == '+')
            {
                c++;
                i = 2;
            }
            string s;
            s.push_back(ch);
            //cout<<s<<" "<<i<<endl;
            m.push_back(pair<string,int>(s,i));
        }
        else
        {
            sep.push_back(*c);
        }
        c++;
    }
    return m;
}

string scan_date(char * date, string format, int len)
{
    //cout << "date:"<<date<<endl;
    //cout << "format:"<<format<<endl;
    //cout << "len:"<<len<<endl;
    int d = 0;
    char buf[len+1];
    for(int n = 0; n<len+1;n++)
        buf[n] = 0;
    string date_format("YMDHmS");
    if(date_format.find(format) != string::npos)
    {
	int i = 0;
        for(; i<len; i++)
	{
            if(date[i]>='0' && date[i]<='9') break;
	}
        for(; i<len; i++)
        {
	    if(date[i]<'0' || date[i]>'9') break;
            buf[i] = date[i];
        }
    }
    else
    {
        for(int i = 0; i<len; i++)
        {
            if(date[i]>='0' && date[i]<='9') break;
            buf[i] = date[i];
        }
	string s(buf);
        return s;
    }

    /*
    sscanf(buf,"%d",&d);
    stringstream ss;
    ss << d<<endl;
    string dig;
    ss >> dig;
    */

    return string(buf);
}

string get_date(string & date, string & format)
{
    string d;
    struct tm t;
    t.tm_year=-1;
    t.tm_mon=-1;
    t.tm_mday=-1;
    t.tm_hour=0;
    t.tm_min=0;
    t.tm_sec=0;
    char * dbuf = (char *)date.c_str();
    list< pair<string,int> > lst = get_date_format(format);
    if(lst.size() < 1) return d;

    list< pair<string,int> >::iterator it = lst.begin();
    while(dbuf != '\0')
    {
        if(*dbuf>='0' && *dbuf <='9')
            break;
        dbuf++;
    }
   
    for(;it!=lst.end();it++)
    {
        pair<string,int> & p = *it;
        string f = p.first;
        //int len = p.second;
        int len = date.size();
        string a = scan_date(dbuf,f,len);
//	cout<<a<<endl;
        if(f.compare("Y")==0)
        {
            t.tm_year = atoi(a.c_str()) - 1900;
        }
        else if(f.compare("M")==0)
        {
            t.tm_mon = atoi(a.c_str()) - 1;
            if(t.tm_mon < 0) return string();
        }
        else if(f.compare("D")==0)
        {
            t.tm_mday = atoi(a.c_str());
            if(t.tm_mday < 1) return string();
        }
        else if(f.compare("H")==0)
        {
            t.tm_hour = atoi(a.c_str());
        }
        else if(f.compare("m")==0)
        {
            t.tm_min = atoi(a.c_str());
        }
        else if(f.compare("S")==0)
        {
            t.tm_sec = atoi(a.c_str());
        }
        if(a.length()>6){
            if(t.tm_mon == -1 || t.tm_mday == -1)
                return string();
        }

        dbuf = dbuf + a.length();
    }

    char buf[80];
    strftime(buf,80,"%Y-%m-%d %T",&t);
    d = string(buf);
    return d;
}
/*
int main()
{
    string format("YYYY 年 M+ 月 D+ 日HH:mm:SS");
    string date("2009年06月10日10:01\n");
    string d = get_date(date,format);
    cout << date<<endl;
    cout << d<<endl;

    date=string("2009-06-11 08:34:35　来源: (北京)");
    format=string("YYYY-MM-DD HH:mm:SS");
    d = get_date(date,format);
    cout << date<<endl;
    cout << d<<endl;
    return 0;
}
*/
