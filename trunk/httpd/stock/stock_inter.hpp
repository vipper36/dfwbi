#ifndef __STOCK_INTER_H__
#define __STOCK_INTER_H__
#include "boost/date_time/posix_time/posix_time.hpp"
#include <string>
#include <map>
#include <list>
struct StockPrice
{
  boost::posix_time::ptime time;
  std::map<std::string,double> PriceValues;
};

class stock_inter
{
public:
enum data_type
  {
    DAY=0,
    M1=1,
    M5=5,
    M15=15,
    M30=30,
    M60=60
  };
public:
  virtual ~stock_inter(){};
  virtual std::list<StockPrice> &GetHisPrice(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type)=0;
  virtual StockPrice GetCurPrice(std::string stockName)=0;
};
#endif
