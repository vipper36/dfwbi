#ifndef __STOCK_ADAPTOR__
#define __STOCK_ADAPTOR__
#include "Stock.h"
#include "Yahoo.h"
#include <string>
class StockDataAdaptor
{
private:
     Yahoo yh;
public:
     StockDataAdaptor()
	  :yh()
	  {};
     ~StockDataAdaptor(){};
     bool FillHisdata(Stock *st,std::string &fromdate);
     bool FillCurentData(Stock *st);
};
#endif
