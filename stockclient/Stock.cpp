#include "Stock.h"
void Stock::AddHisPrice(StockPrice price)
{
     HisPrices.insert(std::make_pair(price.Day,price));
}
void Stock::AddDayPrice(DayPrice price)
{
     std::string dt=price.Day+"|"+price.tm;
     DayPrices.insert(std::make_pair(dt,price));
}
std::map<std::string,double> Stock::getHisValuePair(std::string colName)
{
     std::map<std::string,double> retmap;
     std::map<std::string,StockPrice>::iterator Itr;
     for(Itr=HisPrices.begin();Itr!=HisPrices.end();++Itr)
     {
	  if(colName==HISTAG[0])
	       retmap.insert(make_pair(Itr->first,Itr->second.Open));
	  else if(colName==HISTAG[1])
	       retmap.insert(make_pair(Itr->first,Itr->second.High));
	  else if(colName==HISTAG[2])
	       retmap.insert(make_pair(Itr->first,Itr->second.Low));
	  else if(colName==HISTAG[3])
	       retmap.insert(make_pair(Itr->first,Itr->second.Close));
	  else if(colName==HISTAG[4])
	       retmap.insert(make_pair(Itr->first,Itr->second.Volume));
	  else if(colName==HISTAG[5])
	       retmap.insert(make_pair(Itr->first,Itr->second.Adj_Close));
     }
     return retmap;
		    
}
std::map<std::string,double> Stock::getDayValuePair(std::string colName)
{
     std::map<std::string,double> retmap;
     std::map<std::string,DayPrice>::iterator Itr;
     for(Itr=DayPrices.begin();Itr!=DayPrices.end();++Itr)
     {
	  if(colName==HISTAG[0])
	       retmap.insert(make_pair(Itr->first,Itr->second.Open));
	  else if(colName==HISTAG[1])
	       retmap.insert(make_pair(Itr->first,Itr->second.High));
	  else if(colName==HISTAG[2])
	       retmap.insert(make_pair(Itr->first,Itr->second.Low));
	  else if(colName==HISTAG[3])
	       retmap.insert(make_pair(Itr->first,Itr->second.Close));
	  else if(colName==HISTAG[4])
	       retmap.insert(make_pair(Itr->first,Itr->second.Volume));
     }
     return retmap;
}
std::list<double> Stock::getHisValueList(std::string colName)
{
     std::list<double> retlist;
     std::map<std::string,StockPrice>::iterator Itr;
     for(Itr=HisPrices.begin();Itr!=HisPrices.end();++Itr)
     {
	  if(colName==HISTAG[0])
	       retlist.push_back(Itr->second.Open);
	  else if(colName==HISTAG[1])
	       retlist.push_back(Itr->second.High);
	  else if(colName==HISTAG[2])
	       retlist.push_back(Itr->second.Low);
	  else if(colName==HISTAG[3])
	       retlist.push_back(Itr->second.Close);
	  else if(colName==HISTAG[4])
	       retlist.push_back(Itr->second.Volume);
	  else if(colName==HISTAG[5])
	       retlist.push_back(Itr->second.Adj_Close);
     }
     return retlist;
}
std::list<double> Stock::getDayValueList(std::string colName)
{
     std::list<double> retlist;
     std::map<std::string,DayPrice>::iterator Itr;
     for(Itr=DayPrices.begin();Itr!=DayPrices.end();++Itr)
     {
	  if(colName==HISTAG[0])
	       retlist.push_back(Itr->second.Open);
	  else if(colName==HISTAG[1])
	       retlist.push_back(Itr->second.High);
	  else if(colName==HISTAG[2])
	       retlist.push_back(Itr->second.Low);
	  else if(colName==HISTAG[3])
	       retlist.push_back(Itr->second.Close);
	  else if(colName==HISTAG[4])
	       retlist.push_back(Itr->second.Volume);
     }
     return retlist;
}
