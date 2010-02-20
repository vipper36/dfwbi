#include <boost/algorithm/string.hpp>
#include <iostream>
#include <sstream>
#include "yahoo.h"

void *stock_create()
{
     yahoo_stock *ret=new yahoo_stock();
     return (void*)ret;
}
std::list<StockPrice> yahoo_stock::GetHisPrice(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type)
{
  return std::list<StockPrice> 
}
StockPrice yahoo_stock::GetCurPrice(std::string stockName)
{
}
std::string yahoo_stock::CalUrl(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type)
{
  std::string mcmd="http://203.209.255.240/test/kmin.py/wmData.znzDo?cmd=";
  std::string dcmd="http://203.209.255.253/test/kline.py/data.znzDo?cmd=";
  std::stringstream ss("");
  date fday = from.date();
  date tday = to.date();
  switch(type)
    {
    case DAY:
      ss<<dcmd;
      ss<<TransName(stockName);
      ss<<"|";
      for(greg_year ty=fday.year();ty<=tday.year();ty++)
	{
	  ss<<ty<<",";
	}
      ss<<"|";
      break;
    case M1:
    case M5:
    case M15:
    case M30:
    case M60:
      ss<<dcmd;
      ss<<type<<"|";
      ss<<TransName(stockName);
      break;
    default:
      break;
    }
  return ss.str();
}
std::string TransName(std::string stockName)
{
  std::stringstream ss;
  std::vector<std::string> resv;
  boost::algorithm::split( SplitVec, stockName, is_any_of(".") );
  if(resv[1]=="ss")
    {
      ss<<"SHHQ"<<resv[0];
    }else if(resv[1]=="sz")
    {
      ss<<"SZHQ"<<resv[0];
    }
  return ss.str();
}
