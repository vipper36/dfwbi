#include <iostream>
#include <fstream>
#include <string>
#include <boost/program_options.hpp>
#include "Logger.hpp"
#include "config_file.hpp"
#include "stock_inter.hpp"
#include "list_inter.hpp"
#include <boost/assign/list_of.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/rolling_mean.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <list>
#include <algorithm>
#include "da.h"
#include "LSFitting.h"

namespace po = boost::program_options;
using namespace boost::assign;
using namespace boost::accumulators;
using namespace boost::numeric::ublas;
using namespace Base;
static double lastval=0;
void OutStock(std::ostream &ost,StockPrice sp)
{
     double curval=log(sp.PriceValues["money"]/sp.PriceValues["volum"]);
     double deltaval=100*(curval-lastval);
		
     if(lastval!=0)
     {
	  ost << sp.time<<","<<sp.PriceValues["open"]<<","<<sp.PriceValues["close"]<<","<<sp.PriceValues["high"]<<","<<sp.PriceValues["low"]<<","<<deltaval<<","<<sp.PriceValues["volum"]<<","<<sp.PriceValues["money"]<<std::endl;
     }
     lastval=curval;
}
class GetMatrix
{

private:
     int m_order;
     int m_curRow;
     std::list<double> curList;
     double m_last;
public:
     typedef void result_type;
     GetMatrix(int order)
	  :m_curRow(0),
	   m_last(0),
	   m_order(order)
	  {
	       
	  }
     result_type operator ()(StockPrice sp,matrix<double> &x,vector<double> &y)
	  {
	       double curval=log(sp.PriceValues["money"]/sp.PriceValues["volum"]);
	       double deltaval=100*(curval-m_last);
	       if(m_last==0)
	       {
		    m_last=curval;
		    return;
	       }else
	       {
		    m_last=curval;
	       }
	       if(deltaval<10.1)
	       {

		    if(curList.size()<m_order)
		    {
			 curList.push_back(deltaval);
		    }else
		    {
			 x.resize(m_curRow+1,m_order);
			 y.resize(m_curRow+1);
			 
			 y(m_curRow)=deltaval;
			 int col=0;
			 for(std::list<double>::iterator it=curList.begin();it!=curList.end();++it)
			 {
			      x(m_curRow,col)=*it;
			      col++;
			 }	
			 
			 curList.push_back(deltaval);
			 curList.pop_front();
			 m_curRow++;
			 
		    }
	       }
	  }
};
template<typename ACC>
void AddtoAcc(ACC &acc,StockPrice sp )
{
     acc(sp.PriceValues["money"]/sp.PriceValues["volum"]);
}

void AddtoCont(std::list<double> &target,StockPrice sp)
{
     target.push_back(sp.PriceValues["money"]/sp.PriceValues["volum"]);
}
int main(int argc, char* argv[])
{
     using namespace boost::posix_time;
     using namespace boost::gregorian;
     try
     {
	  std::string aStock;
	  std::string configFile("stock.conf");
	  std::string cmd("yahoo");
	  std::string slist("file");
	  po::options_description desc("Allowed options");
	  desc.add_options()
	       ("help,h", "usage message")
	       ("config,f", po::value(&configFile), "config file")
	       ("cmd,c", po::value(&cmd), "command")
	       ("list,l", po::value(&slist), "list")
	       ("stock,s", po::value(&aStock), "list")
	       ;
	  po::variables_map vm;
	  po::store(po::parse_command_line(argc, argv, desc), vm);
	  po::notify(vm);
	  if (vm.count("help")) {
	       std::cout << desc << "\n";
	       std::cout << "usage:httpd -f [config file] [-l list] [-c command]" << "\n";
	       return 0;
	  }
	  std::cout<<"config file:"<<configFile<<std::endl;
	  Configer* conf=Configer::Instance();
	  conf->LoadIni(configFile);
	  init_logs();
	  std::map<std::string,std::string> stockList;
	  if(aStock.length()>0)
	  {
	       stockList.insert(std::make_pair(aStock,aStock));
	      
	  }else
	  {
	       list_inter *lp=conf->CreateObject<list_inter>(slist);
	       lp->open("ss.csv","ss");
	       std::map<std::string,std::string> &sslist=lp->GetList();
	       stockList.insert(sslist.begin(),sslist.end());
	       lp->open("sz.csv","sz");
	      
	       std::map<std::string,std::string> &szlist=lp->GetList();
	       stockList.insert(szlist.begin(),szlist.end());
	  }

	  stock_inter *tp=conf->CreateObject<stock_inter>(cmd);
	  if(tp!=NULL)
	  {
	       //ptime from(date(2010,1,1),hours(0));
	       ptime now = second_clock::local_time();
	       ptime from=now-years(1);
	       for(std::map<std::string,std::string>::iterator it=stockList.begin();it!=stockList.end();++it)
	       {
		    std::list<StockPrice> &spList=tp->GetHisPrice(it->first,from, now,stock_inter::DAY);
		    
		    accumulator_set<double, stats<tag::mean, tag::variance > > acc;
		    std::for_each(spList.begin(),spList.end(),boost::bind(AddtoAcc<accumulator_set<double, stats<tag::mean, tag::variance > > >,boost::ref(acc),_1));

		    std::ofstream tof(it->first.c_str());
		    std::for_each(spList.begin(),spList.end(),boost::bind(OutStock,boost::ref(tof),_1));
		    std::cout<<mean(acc)<<":"<<variance(acc)<<std::endl;
		    
		    GetMatrix getMatrix(3);
		    matrix<double> x;
		    vector<double> y;

		    std::for_each(spList.begin(),spList.end(),boost::bind(getMatrix,_1,boost::ref(x),boost::ref(y)));

		    std::cout<<"x="<<std::endl;
		    std::cout<<x<<std::endl;
		    std::cout<<"y="<<std::endl;
		    std::cout<<y<<std::endl;

		    // accumulator_set<double, stats<tag::rolling_mean> > acc2(tag::rolling_window::window_size = 5);
		    
// 		    std::list<double> rmean;
// 		    std::list<double> aprice;
// 		    SMA<std::list<double> > psma;

// 		    std::for_each(spList.begin(),spList.end(),boost::bind(AddtoCont,boost::ref(aprice),_1));
		    
// 		    psma(rmean,aprice,5);
// 		    for(std::list<double>::iterator it=rmean.begin();it!=rmean.end();++it)
// 		    {
// 			 std::cout<<*it<<std::endl;
// 		    }
// 		    std::cout<<"------------------------------------------------------"<<std::endl;
// 		    EMA<std::list<double> > pema;
// 		    std::list<double> rema;
// 		    pema(rema,aprice,0.3);
// 		    for(std::list<double>::iterator it=rema.begin();it!=rema.end();++it)
// 		    {
// 			 std::cout<<*it<<std::endl;
// 		    }
// 		    std::cout<<"------------------------------------------------------"<<std::endl;
// 		    WMA<std::list<double> > pwma;
// 		    std::list<double> rwma;
// 		    pwma(rwma,aprice,5);

// 		    for(std::list<double>::iterator it=rwma.begin();it!=rwma.end();++it)
// 		    {
// 			 std::cout<<*it<<std::endl;
// 		    }
	       }
	  }
     }
     catch (std::exception& e)
     {
	  std::cout<< "exception: " << e.what()<<std::endl;
     }

     return 0;
}
