#include <boost/test/included/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/parameterized_test.hpp>
#include <boost/functional.hpp>
#include <boost/static_assert.hpp>
#include <boost/mem_fn.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include <boost/assign/list_of.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "Logger.hpp"
#include "Factory.hpp"
#include "config_file.hpp"
#include "command_inter.hpp"
#include "handle_command.hpp"

using namespace boost;
using namespace boost::unit_test;
using namespace boost::assign;
using namespace std;
namespace po = boost::program_options;
template<typename T1,typename T2,template<typename,typename> class Con=std::pair>
class printPair
{
public:
     void operator()(Con<T1,T2> con)
	  {
	       LOG_APP<<con.first<<"--"<<con.second;
	  }
};
void testfun()
{
     try
     {
	  Factory<command_inter> *fact=Factory<command_inter>::Instance();
	  std::string proName="commands/status.so";
	  fact-> Register(proName);
	  std::string funName;
	  LOG_APP<<proName;
	  funName="status_create";
	  LOG_APP<<funName;
	  command_inter *tp=fact->CreateObject(proName,funName);
	  LOG_APP<<tp->handle(proName,funName);
	  
	  Configer* conf=Configer::Instance();
	  std::string filename="httpd.conf";
	  conf->LoadIni(filename);
	  http::server3::handle_command hc;
	  std::string cmd("status");
	  std::string param("rr");
	  std::string cont("");
	  std::string ret;
	  hc.SigCommand(cmd,param,cont,ret);
	  
	  LOG_APP<<ret;

	  std::stringstream ss;
	  ss  << "CurrentX=1234"<<std::endl
	      <<"CurrentY=456"<<std::endl;
	  po::options_description desc;
	  desc.add_options()
		("CurrentX", "");
	  po::variables_map vm;       
	  po::store(po::parse_config_file(ss, desc, true), vm);
	  po::notify(vm);
	  LOG_APP<<"CurrentX count:"<<vm.count("CurrentX");
	  LOG_APP<<"CurrentY count:"<<vm.count("CurrentY");
	  LOG_APP<<vm["CurrentX"].as<std::string>();
	  
	  std::ifstream ss1("idmapd.conf");

	  
	  po::options_description desc1;
	  desc1.add_options()
		("General.Domain", "");
	  po::variables_map vm1;       
	  po::store(po::parse_config_file(ss1, desc1, true), vm1);
	  po::notify(vm1);
	  LOG_APP<<"Domain count:"<<vm1.count("General.Domain");
	  LOG_APP<<vm1["General.Domain"].as<std::string>();
	  
	  

     }
     catch(BaseException e)
     {
	  std::cout<<e.what()<<std::endl;
     }
}
test_suite*
init_unit_test_suite( int argc, char* argv[] )
{
     init_logs("log.log");     
     test_suite* ts1 = BOOST_TEST_SUITE( "test_suite1" );
     ts1->add( BOOST_TEST_CASE( &testfun ) );
     framework::master_test_suite().add( ts1 );
     return 0;
}
