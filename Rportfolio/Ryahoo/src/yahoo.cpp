#include <list>
#include <boost/assign/list_of.hpp>
#include "boost/date_time/posix_time/posix_time.hpp" 
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <map>
#include <stdlib.h>
#include "yahoo.h"
#include "yahooParser.hpp"
#include <sstream>
#include <iostream>
#include <curl/curl.h>
static size_t  yahoo_write(void *ptr, size_t size, size_t nmemb, std::stringstream *stream)
{
    stream->write((char*)ptr,size*nmemb);
    return size*nmemb;
}
std::list<yahoo::YearData> parseDayResult(std::string result)
{
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::standard::space;
    using boost::phoenix::push_back;
    using boost::phoenix::ref;
  
          
    std::list<yahoo::YearData> ylist;
    yahoo::yhy_parser<std::string::const_iterator> yhy_;
    std::string::const_iterator iter = result.begin();
    std::string::const_iterator end = result.end();
    bool r=phrase_parse(iter,end,
                        (
                            '['>>yhy_[push_back(ref(ylist), boost::spirit::qi::_1)]%','>>"]0"
                            )
                        ,
                        space);
    return ylist;
}
std::list<yahoo::YearData> getData(std::string url)
{
    CURL *curl = curl_easy_init();
    std::stringstream ss;
    std::list<yahoo::YearData> yl;
    if(curl!=NULL) {
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,&ss);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, yahoo_write);
        
        CURLcode res = curl_easy_perform(curl);
        if(!ss.eof())
        {
            yl=parseDayResult(ss.str());
        }
    }
    if(curl!=NULL)
        curl_easy_cleanup(curl);
    return yl;
}
RcppExport SEXP yahooData(SEXP code,SEXP start)
{
BEGIN_RCPP
    SEXP rl = R_NilValue;
    char *exceptionMesg = NULL;
    try
    {
        std::string url="http://data03.znz.finance.bj1.aliyk.com/test/kline.py/data.znzDo?cmd=";
        std::string codeStr=Rcpp::as<std::string>(code);
        std::string startStr;
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        boost::gregorian::greg_year ty=now.date().year();
        
        std::string tmpStr=Rcpp::as<std::string>(start);
        if(tmpStr.length()>0)
        {
            std::stringstream ss;
            boost::gregorian::date d(boost::gregorian::from_string(tmpStr));
        
            for(boost::gregorian::greg_year year=d.year();year<=ty;year=year+1)
            {
                ss<<year<<",";
            }
            ss<<"|";
            startStr=ss.str();
        }else
        {
            std::stringstream ss;
            ss<<ty;
            ss<<"|";
            startStr=ss.str();
        }
        url+=codeStr+"|"+startStr;
//        std::cout<<url<<std::endl;
        std::list<yahoo::YearData> yd=getData(url);

        std::vector<std::string> colName=boost::assign::list_of("date")("open")("high")("low")("close")("volum")("money");


        RcppFrame mat(colName);

        for(std::list<yahoo::YearData>::iterator yit=yd.begin();yit!=yd.end();++yit)
        {
            for(std::list<yahoo::DayPrice>::iterator dit=yit->price_list.begin();dit!=yit->price_list.end();++dit)
            {

                int year=dit->date/10000;
                int mon=(dit->date-year*10000)/100;
                int day=dit->date-year*10000-mon*100;

                std::vector<ColDatum> arow;
                ColDatum dateD;
                RcppDate dt(mon,day,year);
                dateD.setDateValue(dt);
                arow.push_back(dateD);
                
                ColDatum open;
                open.setDoubleValue(dit->open);
                arow.push_back(open);

                ColDatum high;
                high.setDoubleValue(dit->high);
                arow.push_back(high);

                ColDatum low;
                low.setDoubleValue(dit->low);
                arow.push_back(low);

                ColDatum close;
                close.setDoubleValue(dit->close);
                arow.push_back(close);

                ColDatum volum;
                volum.setDoubleValue(dit->volum);
                arow.push_back(volum);

                ColDatum money;
                money.setDoubleValue(dit->money);
                arow.push_back(money);

                mat.addRow(arow);
                
            }
            
        }
        std::cout<<"rows:"<<mat.rows()<<std::endl;
        if(mat.rows()>0)
        {
            RcppResultSet rs;
            
            rs.add("result",  mat);
            
            // Get the list to be returned to R.
            rl = rs.getReturnList();
        }

    } catch(std::exception& ex) {
        exceptionMesg = copyMessageToR(ex.what());
    } catch(...) {
        exceptionMesg = copyMessageToR("unknown reason");
    }

    if(exceptionMesg != NULL)
        Rf_error(exceptionMesg);
    return rl;
END_RCPP    
}
