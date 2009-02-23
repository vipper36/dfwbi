#include <cstdlib>
#include <sstream>
#include <string>
#include "Yahoo.h"

//query the history data from yahoo,the history data from startdat to now. startdate must be format like this "2008-12-22"
std::list<std::string> Yahoo::GetHisData(std::string &stockName,std::string &startdate)
{
     std::list<std::string> result;
     size_t idx1=startdate.find('-');
     size_t idx2=startdate.find('-',idx1+1);
     if(idx1==std::string::npos||idx2==std::string::npos)
	  return result;
     std::string month=startdate.substr(idx1+1,idx2-idx1-1);
     int imon=atoi(month.c_str()); 
     std::string url="http://ichart.yahoo.com/table.csv?s=";
     
     std::stringstream ssadd;
     ssadd<<stockName<<"&a="<<imon-1<<"&b="<<startdate.substr(idx2+1)<<startdate.substr(0,idx1);
     url=url+ssadd.str();
     if(!htc.connect(url))
	  return result;
     if(!htc.SendRequest())
	  return result;
     HttpResponse res=htc.getResponse();
     if(res.getBody().length()>0)
     {
       std::stringstream retStream(res.getBody());
	  std::string line;
	  while(!retStream.eof())
	  {
	       std::getline(retStream,line);
	       result.push_back(line);
	  }
     }
     return result;
}
std::map<std::string,std::string>  Yahoo::GetDayData(std::list<std::string> &nameList)
{
     std::map<std::string,std::string> result;     
     std::string url="http://download.finance.yahoo.com/d/quotes.csv?s=";
     std::stringstream ssadd;
     std::list<std::string>::iterator Itr=nameList.begin();
     if(Itr!=nameList.end())
       {
	 ssadd<<*Itr;
	 ++Itr;
	 while(Itr!=nameList.end())
	   {
	     ssadd<<"+"<<*Itr;
	     ++Itr;
	   }
       }
     url=url+ssadd.str()+"&f=sl1d1t1c1ohgv";
     if(!htc.connect(url))
	  return result;
     if(!htc.SendRequest())
	  return result;
     HttpResponse res=htc.getResponse();
     if(res.getBody().length()>0)
     {
       std::stringstream retStream(res.getBody());
	  std::string line;
	  while(!retStream.eof())
	  {
	       std::getline(retStream,line);
	       size_t idx1=line.find('"');
	       size_t idx2=line.find("\",");
	       if(idx1==std::string::npos||idx2==std::string::npos)
		    continue;
	       std::string stName=line.substr(idx1+1,idx2-idx1-1);
	       result.insert(make_pair(stName,line.substr(idx2+2)));
	  }
     }
     return result;
}
std::string Yahoo::GetDayData(std::string &name)
{
     std::string result;
     std::string url="http://download.finance.yahoo.com/d/quotes.csv?s=";
     url=url+name+"&f=sl1d1t1c1ohgv";
     if(!htc.connect(url))
	  return result;
     if(!htc.SendRequest())
	  return result;
     HttpResponse res=htc.getResponse();
     if(res.getBody().length()>0)
     {
       std::stringstream retStream(res.getBody());
	  std::string line;
	  while(!retStream.eof())
	  {
	       std::getline(retStream,line);
	       size_t idx=line.find("\",");
	       if(idx!=std::string::npos)
	       {
		    result=line.substr(idx+2);
		    break;
	       }
	  }
     }
     return result;
}
