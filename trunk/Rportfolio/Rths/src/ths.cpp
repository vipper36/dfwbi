#include <list>
#include <boost/assign/list_of.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <map>
#include <stdlib.h>
#include "ths.h"
#include <sstream>
#include <fstream>
#include <iostream>
#pragma pack(2)

struct HEAD_DATA { 
  char version[6];
  unsigned int length; 
  unsigned short r_start; 
  unsigned short r_len; 
  unsigned short pad; 
};
struct K_DATA
{
  unsigned int date;
  unsigned int open; 
  unsigned int high; 
  unsigned int low; 
  unsigned int close; 
  unsigned int amount; 
  unsigned int money;
};
class KData
{
public:
  boost::posix_time::ptime date;
  double open; 
  double high; 
  double low; 
  double close; 
  double amount; 
  double money;
  void SetDate(unsigned int val)
  {
    int year=val/10000;
    int month=val/100 - year*100;
    int day=val-year*10000-month*100;
    date=boost::posix_time::ptime(boost::gregorian::date(year,month,day),boost::posix_time::minutes(0));
  }
  void SetMin(unsigned int val)
  {
    int min =val&0x3F;
    int hour=(val>>6)&0x1F;
    int day=(val>>11)&0x1F;
    int month=(val>>16)&0xF;
    int year=(val>>20)+1900;
    date=boost::posix_time::ptime(boost::gregorian::date(year,month,day),boost::posix_time::hours(hour)+boost::posix_time::minutes(min));
  }
  void SetOpen(unsigned int val)
  {
    open=double(val&0xFFFFFFF)/1000;
  }
  void SetHigh(unsigned int val)
  {
    high=double(val&0xFFFFFFF)/1000;
  }
  void SetLow(unsigned int val)
  {
    low=double(val&0xFFFFFFF)/1000;
  }
  void SetClose(unsigned int val)
  {
    close=double(val&0xFFFFFFF)/1000;
  }
  void SetAmount(unsigned int val)
  {
    amount=(val&0xFFFFFFF)*pow(10,val>>28);
  }
  void SetMoney(unsigned int val)
  {
    money=(val&0xFFFFFFF)*pow(10,val>>28);
  }
    
};
static std::string DIR=".";

std::list<KData> GetFileData(std::string file,std::string type)
{
  std::list<KData> dataList;
  HEAD_DATA head;
  std::ifstream is;
  memset((char*)&head,0,sizeof(HEAD_DATA));
  is.open (file.c_str(), std::ios::binary );
  if(is.good())
    {
      is.read ((char*)&head,sizeof(HEAD_DATA));
      is.seekg (head.r_start, std::ios::beg);
      for(int i=0;i<head.length;i++)
        {
	  std::auto_ptr<char> data(new char[head.r_len]);
	  K_DATA day;
	  memset((char*)&day,0,sizeof(K_DATA));
	  is.read (data.get(),head.r_len);
	  memcpy((char*)&day,data.get(),sizeof(K_DATA));

	  KData kdata;
	  if(type=="day")
	    kdata.SetDate(day.date);
	  else
	    kdata.SetMin(day.date);
	  kdata.SetOpen(day.open);
	  kdata.SetHigh(day.high);
	  kdata.SetLow(day.low);
	  kdata.SetClose(day.close);
	  kdata.SetAmount(day.amount);
	  kdata.SetMoney(day.money);
	  dataList.push_back(kdata);
        }
    }
  is.close();
  return dataList;
}
RcppExport void thsInit(SEXP dir)
{
  DIR=Rcpp::as<std::string>(dir);
}
RcppExport SEXP thsDay(SEXP code,SEXP marcket,SEXP start)
{
  Rcpp::DataFrame NDF;
  std::string path=DIR+"/"+Rcpp::as<std::string>(marcket)+"/day/"+Rcpp::as<std::string>(code)+".day";
  std::string startStr;
        
  std::string tmpStr=Rcpp::as<std::string>(start);
  boost::gregorian::date startDate;
  if(tmpStr.length()>0)
    {
      startDate=boost::gregorian::date(boost::gregorian::from_string(tmpStr));
    }

  std::list<KData> dataList=GetFileData(path,"day");
  std::vector<Rcpp::Date> dateV;
  std::vector<double> openV;
  std::vector<double> highV;
  std::vector<double> lowV;
  std::vector<double> closeV;
  std::vector<double> amountV;
  std::vector<double> moneyV;
  for(std::list<KData>::iterator it=dataList.begin();it!=dataList.end();++it)
    {
      if(it->date.date()>=startDate)
	{
	  Rcpp::Date dt(it->date.date().month(),it->date.date().day(),it->date.date().year());
	  dateV.push_back(dt);
                
	  openV.push_back(it->open);

	  highV.push_back(it->high);

	  lowV.push_back(it->low);

	  closeV.push_back(it->close);

	  amountV.push_back(it->amount);

	  moneyV.push_back(it->money);
	}
            
    }
  NDF= 
    Rcpp::DataFrame::create(Rcpp::Named("date")=dateV,
			    Rcpp::Named("open")=openV,
			    Rcpp::Named("high")=highV,
			    Rcpp::Named("low")=lowV,
			    Rcpp::Named("close")=closeV,
			    Rcpp::Named("amount")=amountV,
			    Rcpp::Named("money")=moneyV);

  return NDF;
}
Rcpp::DataFrame readMin(std::string day,std::string path)
{
    Rcpp::DataFrame NDF;

    std::string startStr;
        

  boost::gregorian::date startDate;
  if(day.length()>0)
    {
      startDate=boost::gregorian::date(boost::gregorian::from_string(day));
    }

  std::list<KData> dataList=GetFileData(path,"min");
  std::vector<Rcpp::Datetime> dateV;
  std::vector<double> openV;
  std::vector<double> highV;
  std::vector<double> lowV;
  std::vector<double> closeV;
  std::vector<double> amountV;
  std::vector<double> moneyV;
  for(std::list<KData>::iterator it=dataList.begin();it!=dataList.end();++it)
    {
      if(it->date.date()>=startDate)
	{
	  Rcpp::Datetime dt(to_iso_extended_string(it->date),"%Y-%m-%dT%H:%M:%OS");
	  dateV.push_back(dt);
                
	  openV.push_back(it->open);

	  highV.push_back(it->high);

	  lowV.push_back(it->low);

	  closeV.push_back(it->close);

	  amountV.push_back(it->amount);

	  moneyV.push_back(it->money);
	}
            
    }
  NDF= 
    Rcpp::DataFrame::create(Rcpp::Named("date")=dateV,
			    Rcpp::Named("open")=openV,
			    Rcpp::Named("high")=highV,
			    Rcpp::Named("low")=lowV,
			    Rcpp::Named("close")=closeV,
			    Rcpp::Named("amount")=amountV,
			    Rcpp::Named("money")=moneyV);

  return NDF;
}
Rcpp::DataFrame readMinofDay(std::string day,std::string path)
{
  Rcpp::DataFrame NDF;

  std::string startStr;
  boost::gregorian::date startDate;
  if(day.length()>0)
    {
      startDate=boost::gregorian::date(boost::gregorian::from_string(day));
    }

  std::list<KData> dataList=GetFileData(path,"min");
  std::vector<Rcpp::Datetime> dateV;
  std::vector<double> openV;
  std::vector<double> highV;
  std::vector<double> lowV;
  std::vector<double> closeV;
  std::vector<double> amountV;
  std::vector<double> moneyV;
  for(std::list<KData>::iterator it=dataList.begin();it!=dataList.end();++it)
    {
      if(it->date.date()==startDate)
	{
	  Rcpp::Datetime dt(to_iso_extended_string(it->date),"%Y-%m-%dT%H:%M:%OS");
	  dateV.push_back(dt);
                
	  openV.push_back(it->open);

	  highV.push_back(it->high);

	  lowV.push_back(it->low);

	  closeV.push_back(it->close);

	  amountV.push_back(it->amount);

	  moneyV.push_back(it->money);
	}
            
    }
  NDF= 
    Rcpp::DataFrame::create(Rcpp::Named("date")=dateV,
			    Rcpp::Named("open")=openV,
			    Rcpp::Named("high")=highV,
			    Rcpp::Named("low")=lowV,
			    Rcpp::Named("close")=closeV,
			    Rcpp::Named("amount")=amountV,
			    Rcpp::Named("money")=moneyV);

  return NDF;
}

RcppExport SEXP thsMin(SEXP code,SEXP marcket,SEXP start)
{
    std::string path=DIR+"/"+Rcpp::as<std::string>(marcket)+"/min/"+Rcpp::as<std::string>(code)+".min";
    std::string tmpStr=Rcpp::as<std::string>(start);
    return readMin(tmpStr,path);
}
RcppExport SEXP thsMinOfDay(SEXP code,SEXP marcket,SEXP day)
{
    std::string path=DIR+"/"+Rcpp::as<std::string>(marcket)+"/min/"+Rcpp::as<std::string>(code)+".min";
    std::string tmpStr=Rcpp::as<std::string>(day);
    return readMinofDay(tmpStr,path);
}
RcppExport SEXP thsMin5(SEXP code,SEXP marcket,SEXP start)
{
    std::string path=DIR+"/"+Rcpp::as<std::string>(marcket)+"/min5/"+Rcpp::as<std::string>(code)+".mn5";
    std::string tmpStr=Rcpp::as<std::string>(start);
    return readMin(tmpStr,path);
}
RcppExport SEXP thsMin5OfDay(SEXP code,SEXP marcket,SEXP day)
{
    std::string path=DIR+"/"+Rcpp::as<std::string>(marcket)+"/min5/"+Rcpp::as<std::string>(code)+".mn5";
    std::string tmpStr=Rcpp::as<std::string>(day);
    return readMinofDay(tmpStr,path);
}
