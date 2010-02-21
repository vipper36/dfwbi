#include <boost/algorithm/string.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <iostream>
#include <sstream>
#include "yahoo.h"

void *stock_create()
{
  yahoo_stock *ret=new yahoo_stock();
  return (void*)ret;
}
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
void yahoo_stock::PutDayPrice(yahoo::DayPrice dp)
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;
  StockPrice sp;
  int year=dp.date/10000;
  int mon=(dp.date-year*10000)/100;
  int day=dp.date-year*10000-mon*100;
  sp.time=ptime(date(year,mon,day),hours(0));
  sp.PriceValues.insert(std::make_pair("open",dp.open));
  sp.PriceValues.insert(std::make_pair("high",dp.high));
  sp.PriceValues.insert(std::make_pair("low",dp.low));
  sp.PriceValues.insert(std::make_pair("close",dp.close));
  sp.PriceValues.insert(std::make_pair("volum",dp.volum));
  sp.PriceValues.insert(std::make_pair("money",dp.money));
  _priceList.push_back(sp);
  
}
void yahoo_stock::PutYearData(yahoo::YearData yd)
{
  std::for_each(yd.price_list.begin(),yd.price_list.end(),boost::bind(&yahoo_stock::PutDayPrice,this,_1));
}
void yahoo_stock::PutDayData(yahoo::DayData dd,data_type type)
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;
  int year=dd.date/10000;
  int mon=(dd.date-year*10000)/100;
  int day=dd.date-year*10000-mon*100;
  ptime curtime(date(year,mon,day),hours(9)+minutes(30));
  for(std::list<yahoo::MinPrice>::iterator it=dd.price_list.begin();it!=dd.price_list.end();++it)
    {
      StockPrice sp;
      curtime=curtime+minutes(int(type));
      sp.time=curtime;
      sp.PriceValues.insert(std::make_pair("open",it->open));
      sp.PriceValues.insert(std::make_pair("high",it->high));
      sp.PriceValues.insert(std::make_pair("low",it->low));
      sp.PriceValues.insert(std::make_pair("close",it->close));
      sp.PriceValues.insert(std::make_pair("volum",it->volum));
      sp.PriceValues.insert(std::make_pair("money",it->money));
      _priceList.push_back(sp);
    }
  
}

std::list<StockPrice> &yahoo_stock::GetHisPrice(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type)
{
  _priceList.clear();
  if(from<to)
    {
      std::string url=CalUrl(stockName,from,to,type);
      if(url.length()>0)
	{
	  LOG_APP << "url:"<<url;
	  if(!_client.connect(url))
	    return _priceList;
	  if(!_client.SendRequest())
	    return _priceList;
	  HttpResponse &res=_client.getResponse();
	  if(!res.getBody().eof())
	    {
	      std::stringstream &retStream=res.getBody();
	      if(type==DAY)
		parseDayResult(retStream.str());
	      else
		parseMinResult(retStream.str(),type);
	    }
	  if(!_priceList.empty())
	    {
	      std::map<boost::posix_time::ptime,StockPrice> spMap;
	      std::for_each(_priceList.begin(),_priceList.end(),boost::bind(&yahoo_stock::InsertMap,this,_1,ref(spMap)));
	      _priceList.clear();
	      for(std::map<boost::posix_time::ptime,StockPrice>::iterator it=spMap.begin();it!=spMap.end();it++)
		{
		  if(it->first<from)
		    {
		      continue;
		    }
		  else if(it->first<to)
		    {
		      _priceList.push_back(it->second);
		    }
		  else
		    break;
		}
	      LOG_APP << "size:"<<_priceList.size();
	      //std::for_each(_priceList.begin(),_priceList.end(),boost::bind(&yahoo_stock::PrintPrice,this,_1));
	    }
	}
    }
  return _priceList;
}
void yahoo_stock::PrintPrice(StockPrice sp)
{
  LOG_APP << sp.time<<","<<sp.PriceValues["open"]<<","<<sp.PriceValues["close"]<<","<<sp.PriceValues["high"]<<","<<sp.PriceValues["low"];
}
void yahoo_stock::InsertMap(StockPrice sp,std::map<boost::posix_time::ptime,StockPrice> &smap)
{
  smap.insert(std::make_pair(sp.time,sp));
}
void yahoo_stock::parseDayResult(std::string result)
{
  using qi::phrase_parse;
  using ascii::space;
  using phoenix::push_back;
  using phoenix::ref;
  
  //  LOG_APP << "content:"<<result;
  
  std::list<yahoo::YearData> ylist;
  yahoo::yhy_parser<std::string::const_iterator> yhy_;
  std::string::const_iterator iter = result.begin();
  std::string::const_iterator end = result.end();
  LOG_APP << "size:"<<ylist.size();
  bool r=phrase_parse(iter,end,
		      (
		       '['>>yhy_[push_back(ref(ylist), qi::_1)]%','>>"]0"
		       )
		      ,
		      space);
  LOG_APP << "return:"<<r;
  LOG_APP << "size:"<<ylist.size();
  std::for_each(ylist.begin(),ylist.end(),boost::bind(&yahoo_stock::PutYearData,this,_1));
  LOG_APP << "size:"<<_priceList.size();
}

void yahoo_stock::parseMinResult(std::string result,data_type type)
{
  using qi::phrase_parse;
  using ascii::space;
  using phoenix::push_back;
  using phoenix::ref;
  //  LOG_APP << "return:"<<result;

  std::list<yahoo::DayData> dlist;
  yahoo::yhd_parser<std::string::const_iterator> yhd_;
  std::string::const_iterator iter = result.begin();
  std::string::const_iterator end = result.end();
  bool r=phrase_parse(iter,end,
                      (
                       '['>>yhd_[push_back(ref(dlist), qi::_1)]%','>>"]0"
                       )
                      ,
                      space);
  LOG_APP << "return:"<<r;
  LOG_APP << "size:"<<dlist.size();

  std::for_each(dlist.begin(),dlist.end(),boost::bind(&yahoo_stock::PutDayData,this,_1,type));
  LOG_APP << "size:"<<_priceList.size();
}
StockPrice yahoo_stock::GetCurPrice(std::string stockName)
{
  return StockPrice();
}

std::string yahoo_stock::CalUrl(std::string stockName,boost::posix_time::ptime &from, boost::posix_time::ptime& to,data_type type)
{
  std::string mcmd="http://203.209.255.240/test/kmin.py/wmData.znzDo?cmd=";
  std::string dcmd="http://203.209.255.253/test/kline.py/data.znzDo?cmd=";
  std::stringstream ss("");
  boost::gregorian::date fday = from.date();
  boost::gregorian::date tday = to.date();
  std::string sn=TransName(stockName);
  switch(type)
    {
    case DAY:
      if(sn.length()>0)
	{
	  ss<<dcmd;
	  ss<<sn;
	  ss<<"|";
	  for(boost::gregorian::greg_year ty=fday.year();ty<=tday.year();ty=ty+1)
	    {
	      ss<<ty<<",";
	    }
	  ss<<"|";
	}
      break;
    case M1:
    case M5:
    case M15:
    case M30:
    case M60:
      if(sn.length()>0)
	{
	  ss<<mcmd;
	  ss<<type<<"|";
	  ss<<sn;
	  ss<<"|";
	}
      break;
    default:
      break;
    }
  return ss.str();
}

std::string yahoo_stock::TransName(std::string stockName)
{
  std::stringstream ss;
  std::vector<std::string> resv;
  boost::algorithm::split( resv, stockName, boost::algorithm::is_any_of(".") );
  if(resv[1]=="ss")
    {
      ss<<"SHHQ"<<resv[0];
    }else if(resv[1]=="sz")
    {
      ss<<"SHHQ"<<resv[0];
    }
  return ss.str();
}
