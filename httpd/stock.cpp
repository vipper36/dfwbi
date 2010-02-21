#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "Logger.hpp"
#include "config_file.hpp"
#include "stock_inter.hpp"
#include "list_inter.hpp"
#include <boost/assign/list_of.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"


namespace po = boost::program_options;
using namespace boost::assign;
using namespace Base;
int main(int argc, char* argv[])
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;
  try
    {
      std::string configFile("stock.conf");
      std::string cmd("yahoo");
      std::string slist("file");
      po::options_description desc("Allowed options");
      desc.add_options()
	("help,h", "usage message")
	("config,f", po::value(&configFile), "config file")
	("cmd,c", po::value(&cmd), "command")
	("list,l", po::value(&slist), "list")
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
      list_inter *lp=conf->CreateObject<list_inter>(slist);
      lp->open("ss.csv","ss");
      std::map<std::string,std::string> &sslist=lp->GetList();
      stockList.insert(sslist.begin(),sslist.end());
      lp->open("sz.csv","sz");
      
      std::map<std::string,std::string> &szlist=lp->GetList();
      stockList.insert(szlist.begin(),szlist.end());

      stock_inter *tp=conf->CreateObject<stock_inter>(cmd);
      if(tp!=NULL)
	{
	  ptime from(date(2010,1,1),hours(0));
	  ptime now = second_clock::local_time();
	  for(std::map<std::string,std::string>::iterator it=stockList.begin();it!=stockList.end();++it)
	    {
	      tp->GetHisPrice(it->first,from, now,stock_inter::DAY);
	    }
	}
    }
  catch (std::exception& e)
    {
      std::cout<< "exception: " << e.what()<<std::endl;
    }

  return 0;
}
