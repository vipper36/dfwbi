#include "StockDataAdaptor.h"
#include <boost/algorithm/string.hpp> 
#include <cstdlib>
#include <list>
bool StockDataAdaptor::FillHisdata(Stock *st,std::string &fromDate)
{
      Yahoo yh;
      std::list<std::string> sl=yh.GetHisData(st->GetName(),fromDate);
      std::list<std::string>::iterator Itr=sl.begin();
      for(;Itr!=sl.end();++Itr)
      {
	   StockPrice sp;
	   std::list<std::string> results;    
	   boost::split(results, *Itr, boost::is_any_of(","));
	   std::list<std::string>::const_iterator p = results.begin( );
	   if(p==results.end())
		continue;

	   sp.Day=*p;
	   ++p;
	   if(p==results.end())
		continue;
	   
	   sp.Open=strtod(p->c_str(),NULL);
	   ++p;
	   if(p==results.end())
		continue;   
	   
	   sp.High=strtod(p->c_str(),NULL);
	   ++p;
	   if(p==results.end())
		continue;

	   sp.Low=strtod(p->c_str(),NULL);
	   ++p;
	   if(p==results.end())
		continue;

	   sp.Close=strtod(p->c_str(),NULL);
	   ++p;
	   if(p==results.end())
		continue;

	   sp.Volume=strtod(p->c_str(),NULL);
	   ++p;
	   if(p==results.end())
		continue;

	   sp.Adj_Close=strtod(p->c_str(),NULL);
	   st->AddHisPrice(sp);
      }
      return true;
}
bool StockDataAdaptor::FillCurentData(Stock *st)
{
     DayPrice dp;
     std::string pr=yh.GetDayData(st->GetName());

     std::list<std::string> results;    
     boost::split(results, pr, boost::is_any_of(","));
     std::list<std::string>::const_iterator p = results.begin( );
     if(p==results.end())
	  return false;
     
     dp.Close=strtod(p->c_str(),NULL);
     ++p;
     if(p==results.end())
	  return false;
     std::string date=*p;
     dp.Day=date.substr(1,date.length()-2);
     ++p;
     if(p==results.end())
	  return false;
     std::string time=*p;
     dp.tm=time.substr(1,time.length()-2);
     ++p;
     if(p==results.end())
	  return false;
     ++p;
     if(p==results.end())
	  return false;
     
     dp.Open=strtod(p->c_str(),NULL);
     ++p;
     if(p==results.end())
	  return false;   
     
     dp.High=strtod(p->c_str(),NULL);
     ++p;
     if(p==results.end())
	  return false;

     dp.Low=strtod(p->c_str(),NULL);
     ++p;
     if(p==results.end())
	  return false;

     dp.Volume=strtod(p->c_str(),NULL);
     st->AddDayPrice(dp);
     return true;
}
