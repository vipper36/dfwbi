#include "Server.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>


// Constructors/Destructors
//  
namespace server
{
     Server::Server ( ) {
	  controlflag=false;
	  log=common::Logger::Instance();
     }

     Server::~Server ( ) { }
     void Server::setControlflag(bool flag)
     {
	  controlflag=flag;
     }
     bool Server::getControlflag()
     {
	  return controlflag;
     }
//  
// Methods
//  
     bool Server::AddService(Service *sv,int port )
     {
	  std::string serviceName=sv->getName();
	  std::map<int,listener_ptr>::iterator listItr=listeners.find(port);
	  if(listItr!=listeners.end())
	       return false;
	  listener_ptr lisPtr(new Listener(*this, port,sv));
	  listeners.insert(std::make_pair(port,lisPtr));
	  boost::shared_ptr<boost::thread> thread(new boost::thread(
						       boost::bind(&Listener::run, lisPtr)));
	  thread->join();
	  return true;
     }

     bool Server::removeService (int port )
     {
	  std::map<int,listener_ptr>::iterator lisPtrItr=listeners.find(port);
	  if(lisPtrItr==listeners.end())
	       return false;
	  listener_ptr lisPtr=lisPtrItr->second;
	  listeners.erase(lisPtrItr);
	  lisPtr->pleaseStop();
	  return true;
     }

     void Server::displayStatus ( )
     {
     }
     listener_ptr Server::GetListener(int port)
     {
	  std::map<int,listener_ptr>::iterator lisPtrItr=listeners.find(port);
	  if(lisPtrItr==listeners.end())
	       throw std::exception();
	  return lisPtrItr->second;
     }


}
