#ifndef _STATUS_H_
#define _STATUS_H_
#include <string>
#include <list>
#include "stock_inter.hpp"
#include "HttpClient.h"
#include "HttpResponse.h"
#include "Logger.hpp"
#include "yahooParser.hpp"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#ifdef __cplusplus 
extern "C"
{
#endif
     void *stock_create();
#ifdef __cplusplus      
}
#endif
class yahoo_stock:public stock_inter
{
public:
     yahoo_stock()
	  {
	    init_logs();
	  }
     ~yahoo_stock()
	  {}
     virtual std::list<StockPrice> &GetHisPrice(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type);
     virtual StockPrice GetCurPrice(std::string stockName);
private:
     std::string CalUrl(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type);
     std::string TransName(std::string stockName);
     void parseDayResult(std::string result);
     void parseMinResult(std::string result,data_type type);
     void PutDayData(yahoo::DayData dd,data_type type);
     void PutDayPrice(yahoo::DayPrice dp);
     void PutYearData(yahoo::YearData yd);
     void PrintPrice(StockPrice sp);
     void InsertMap(StockPrice sp,std::map<boost::posix_time::ptime,StockPrice> &smap);
     std::list<StockPrice> _priceList;
     HttpClient _client;
};
#endif
