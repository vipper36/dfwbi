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



namespace po = boost::program_options;
using namespace boost::assign;
using namespace boost::accumulators;
using namespace Base;
void OutStock(std::ostream &ost,StockPrice sp)
{
     ost << sp.time<<","<<sp.PriceValues["open"]<<","<<sp.PriceValues["close"]<<","<<sp.PriceValues["high"]<<","<<sp.PriceValues["low"]<<","<<sp.PriceValues["money"]/sp.PriceValues["volum"]<<","<<sp.PriceValues["volum"]<<","<<sp.PriceValues["money"]<<std::endl;
}
template<typename ACC>
void AddtoAcc(ACC &acc,StockPrice sp )
{
     acc(sp.PriceValues["money"]/sp.PriceValues["volum"]);
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
	       }
	       
	  }
     }
     catch (std::exception& e)
     {
	  std::cout<< "exception: " << e.what()<<std::endl;
     }

     return 0;
}
