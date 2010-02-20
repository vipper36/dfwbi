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

