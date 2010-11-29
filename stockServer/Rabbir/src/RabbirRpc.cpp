#include <list>
#include <map>
#include "RabbirRpc.h"
#include "StockPrice.hpp"
#include "RabbitAmqp.hpp"
RcppExport SEXP RabbirRpc(SEXP host,SEXP port,SEXP exchange,SEXP key,SEXP type,SEXP marcket,SEXP code,SEXP start,SEXP end)
{
BEGIN_RCPP
    SEXP rl = R_NilValue;
    char *exceptionMesg = NULL;
    try
    {
        std::string hostStr=Rcpp::as<std::string>(host);
        std::string portStr=Rcpp::as<std::string>(port);
        std::string exStr=Rcpp::as<std::string>(exchange);
        std::string keyStr=Rcpp::as<std::string>(key);
        std::string typeStr=Rcpp::as<std::string>(type);
        std::string marcStr=Rcpp::as<std::string>(marcket);
        std::string codeStr=Rcpp::as<std::string>(code);
        std::string startStr=Rcpp::as<std::string>(start);
        std::string endStr=Rcpp::as<std::string>(end);
        stock::PriceReq req(typeStr,marcStr,codeStr,startStr,endStr);
        
        int portInt=atoi(portStr.c_str());
        std::stringstream ss;
        boost::archive::xml_oarchive oa(ss);
        oa << BOOST_SERIALIZATION_NVP(req);

        AMQP::RabbitClient rc(hostStr,portInt);
        std::string res=rc.RpcCall(ss.str(),exStr,keyStr);

        std::stringstream resSS(res);
        
        stock::StockPriceList pl;
        boost::archive::xml_iarchive ia(resSS);
        ia >> BOOST_SERIALIZATION_NVP(pl);
        
        std::vector<std::string> colName;
        std::list<std::string>::iterator tagStart;
        std::list<std::string>::iterator tagEnd;
        if(pl.type!=stock::REAL)
        {
            tagStart=stock::NTAGS.begin();
            tagEnd=stock::NTAGS.end();
            
        }
        else
        {
            tagStart=stock::TAGS.begin();
            tagEnd=stock::TAGS.end();
        }

        colName.assign(tagStart,tagEnd);
        colName.insert(colName.begin(),std::string("Date"));

        RcppFrame mat(colName);

        for(std::list<stock::StockPrice>::iterator it=pl.priceList.begin();it!=pl.priceList.end();++it)
        {
            std::vector<ColDatum> arow;
            ColDatum dateD;
            boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970,1,1));
            boost::posix_time::time_duration td= it->time-time_t_epoch;
            RcppDatetime dt(td.total_seconds());
            dateD.setDatetimeValue(dt);
            arow.push_back(dateD);
            for(std::list<std::string>::iterator jit=tagStart;jit!=tagEnd;++jit)
            {
                ColDatum dVal;
                dVal.setDoubleValue(it->priceMap[*jit]);
                arow.push_back(dVal);
            }
            mat.addRow(arow);
        }
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
