#include "StockDataAdaptor.h"
#include <boost/algorithm/string.hpp> 
#include <boost/spirit.hpp>
#include <cstdlib>
#include <list>
using namespace boost;
using namespace boost::spirit;
bool StockDataAdaptor::FillHisdata(Stock *st,std::string &fromDate)
{
      Yahoo yh;
      std::list<std::string> sl=yh.GetHisData(st->GetName(),fromDate);
      std::list<std::string>::iterator Itr=sl.begin();
      for(;Itr!=sl.end();++Itr)
      {
	   StockPrice sp;
	   parse_info<const char*> ret=parse(Itr->c_str(), (+(~ch_p(',')))[assign_a(sp.Day)] >> ch_p(',') >> (real_p[assign_a(sp.Open)]) >> ch_p(',') >> (real_p[assign_a(sp.High)]) >> ch_p(',') >> (real_p[assign_a(sp.Low)]) >> ch_p(',') >> (real_p[assign_a(sp.Close)]) >> ch_p(',') >> (real_p[assign_a(sp.Volume)]) >> ch_p(',') >> (real_p[assign_a(sp.Adj_Close)]), cntrl_p);
	   bool parCor=ret.full;
	   if(!parCor)
		std::cout<<"parse error!"<<std::endl;
	   else
		st->AddHisPrice(sp);
      }
      return true;
}
bool StockDataAdaptor::FillCurentData(Stock *st)
{
     DayPrice sp;
     std::string pr=yh.GetDayData(st->GetName());
     parse_info<const char*> ret=parse(pr.c_str(), real_p[assign_a(sp.Close)]>> ch_p(',') >> (+(~ch_p(',')))[assign_a(sp.Day)] >> ch_p(',') >> (+(~ch_p(',')))[assign_a(sp.tm)] >>ch_p(',')>> (+alpha_p) >> ch_p(',') >> real_p[assign_a(sp.Open)] >> ch_p(',') >> real_p[assign_a(sp.High)] >> ch_p(',') >> real_p[assign_a(sp.Low)] >> ch_p(',') >> real_p[assign_a(sp.Volume)], cntrl_p);
     sp.Day=sp.Day.substr(1,sp.Day.length()-2);
     sp.tm=sp.tm.substr(1,sp.tm.length()-2);
     st->AddDayPrice(sp);
     return ret.full;
}
