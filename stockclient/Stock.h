#ifndef __STOCK__
#define __STOCK__
#include <map>
#include <list>
#include <string>
static std::string HISTAG[]=
{
     "Open",
     "High",
     "Low",
     "Close",
     "Volume",
     "Adj_Close"
};

typedef struct StockPrice
{
     std::string Day;
     double Open;
     double High;
     double Low;
     double Close;
     double Volume;
     double Adj_Close;
}HPType;
typedef struct DayPrice
{
     std::string Day;
     std::string tm;
     double Open;
     double YClose;
     double High;
     double Low;
     double Close;
     double Volume;
     double VolMun;
     std::pair<double,long int> buy1;
     std::pair<double,long int> buy2;
     std::pair<double,long int> buy3;
     std::pair<double,long int> buy4;
     std::pair<double,long int> buy5;
     std::pair<double,long int> sold1;
     std::pair<double,long int> sold2;
     std::pair<double,long int> sold3;
     std::pair<double,long int> sold4;
     std::pair<double,long int> sold5;
}DPType;

class Stock
{
private:
     std::map<std::string,StockPrice> HisPrices;
     std::map<std::string,DayPrice> DayPrices;
     std::string stockName;
     std::string stockCode;
public:
     Stock()
	  :HisPrices(),
	   DayPrices(),
	   stockName(),
	   stockCode()
	  {}
     Stock(std::string name)
	  :HisPrices(),
	   DayPrices(),
	   stockName(name),
	   stockCode()
	  {}
     ~Stock(){}
     void SetName(std::string &name)
	  {
	       stockName=name;
	  }
     std::string &GetName()
	  {
	       return stockName;
	  }
     void SetCode(std::string &code)
	  {
	       stockCode=code;
	  }
     std::string &GetCode()
	  {
	       return stockCode;
	  }
     void AddDayPrice(DayPrice price);
     void AddHisPrice(StockPrice price);
     std::map<std::string,double> getHisValuePair(std::string colName);
     std::map<std::string,double> getDayValuePair(std::string colName);
     std::list<double> getHisValueList(std::string colName);
     std::list<double> getDayValueList(std::string colName);

};
#endif
