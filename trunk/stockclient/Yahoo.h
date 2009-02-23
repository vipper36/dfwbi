#ifndef __YAHOO__
#define __YAHOO__
#include <string>
#include <list>
#include <map>
#include "HttpClient.h"
#include "HttpResponse.h"

class Yahoo
{
  public:
     Yahoo(){};
     ~Yahoo(){};
     std::list<std::string> GetHisData(std::string &stockName,std::string &startdate);
     std::map<std::string,std::string>  GetDayData(std::list<std::string> &nameList);
     std::string GetDayData(std::string &name);
  public:
     HttpClient htc;
};
#endif
