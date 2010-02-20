#ifndef _STATUS_H_
#define _STATUS_H_
#include "stock_inter.hpp"
#include "HttpClient.h"
#include "HttpResponse.h"
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
	  }
     ~yahoo_stock()
	  {}
     virtual std::list<StockPrice> &GetHisPrice(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type);
     virtual StockPrice GetCurPrice(std::string stockName);
private:
     std::string CalUrl(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type);
     std::string TransName(std::string stockName);
     std::list<StockPrice> _priceList;
     HttpClient _client;
};
#endif
