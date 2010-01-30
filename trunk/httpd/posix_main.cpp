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



namespace po = boost::program_options;
using namespace boost::assign;
using namespace Base;
int main(int argc, char* argv[])
{
     try
     {
       std::string configFile("httpd.conf");
	  po::options_description desc("Allowed options");
	  desc.add_options()
	       ("help,h", "usage message")
	       ("config,f", po::value(&configFile), "config file")
	       ;
	  po::variables_map vm;
	  po::store(po::parse_command_line(argc, argv, desc), vm);
	  po::notify(vm);
	  if (vm.count("help")) {
	       std::cout << desc << "\n";
	       std::cout << "usage:httpd -f [config file] [-l <log file>]" << "\n";
	       return 0;
	  }
	  std::cout<<"config file:"<<configFile<<std::endl;
	  Configer* conf=Configer::Instance();
	  conf->LoadIni(configFile);
	std::cout<<conf->GetConfig("sys.threads")<<std::endl;
	std::cout<<conf->GetConfig("sys.threads1")<<std::endl;
	  init_logs();


	  
	  
	  // Block all signals for background thread.
	  sigset_t new_mask;
	  sigfillset(&new_mask);
	  sigset_t old_mask;
	  pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);

	  // Run server in background thread.
	  std::size_t num_threads = boost::lexical_cast<std::size_t>(conf->GetConfig("sys.threads"));
	  http::server3::server s(conf->GetConfig("sys.address").c_str(),conf->GetConfig("sys.port").c_str(), conf->GetConfig("sys.root").c_str(), num_threads);
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
	 std::cout<< "exception: " << e.what()<<std::endl;
     }

     return 0;
}
