//
// posix_main.cpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>
#include "server.hpp"
#include "Logger.hpp"
#include <pthread.h>
#include <signal.h>
#include "config_file.hpp"
#include <boost/assign/list_of.hpp>
#include "config_file.hpp"


template<typename T1,typename T2,template<typename,typename> class Con=std::pair>
class printPair
{
public:
     void operator()(Con<T1,T2> con)
	  {
	       LOG_APP<<con.first<<"--"<<con.second;
	  }
};

namespace po = boost::program_options;
using namespace boost::assign;

int main(int argc, char* argv[])
{
     try
     {
	  std::string configFile;
	  std::string logFile("log.log");
	  po::options_description desc("Allowed options");
	  desc.add_options()
	       ("help,h", "usage message")
	       ("config,f", po::value(&configFile), "config file")
	       ("log,l", po::value(&logFile), "log file")
	       ;
	  po::variables_map vm;
	  po::store(parse_command_line(argc, argv, desc), vm);
	  if (argc<2||vm.count("help")||!vm.count("config")) {
	       std::cout << desc << "\n";
	       std::cout << "usage:httpd -f <config file> [-l <log file>]" << "\n";
	       return 0;
	  }
	  po::notify(vm);
	  std::cout<<"log file:"<<logFile<<std::endl;
	  init_logs(logFile);
	  LOG_APP<<"config file:"<<configFile;

	  Configer* conf=Configer::Instance();
	  conf->SetDefaultConfig(configFile);
	  std::list<std::string> sysconf=list_of("address")("port")("threads")("root");
	  std::map<std::string,std::string> remap=conf->GetConfig("sys",sysconf);
	  //Test config
	  printPair<std::string,std::string> prn;
	  std::for_each(remap.begin(),remap.end(), prn);
	  
	  
	  // Block all signals for background thread.
	  sigset_t new_mask;
	  sigfillset(&new_mask);
	  sigset_t old_mask;
	  pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

	  // Run server in background thread.
	  std::size_t num_threads = boost::lexical_cast<std::size_t>(remap["sys.threads"]);
	  http::server3::server s(remap["sys.address"].c_str(),remap["sys.port"].c_str(), remap["sys.root"].c_str(), num_threads);
	  boost::thread t(boost::bind(&http::server3::server::run, &s));

	  // Restore previous signals.
	  pthread_sigmask(SIG_SETMASK, &old_mask, 0);

	  // Wait for signal indicating time to shut down.
	  sigset_t wait_mask;
	  sigemptyset(&wait_mask);
	  sigaddset(&wait_mask, SIGINT);
	  sigaddset(&wait_mask, SIGQUIT);
	  sigaddset(&wait_mask, SIGTERM);
	  pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
	  int sig = 0;
	  sigwait(&wait_mask, &sig);

	  // Stop the server.
	  s.stop();
	  t.join();
     }
     catch (std::exception& e)
     {
	  LOG_ERR << "exception: " << e.what();
     }

     return 0;
}
