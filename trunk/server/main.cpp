#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include "Server.h"
#include "ControlService.h"
int main(int argc,char* argv[])
{
     std::cout<<"System init........."<<std::endl;
     server::Server serv;
     if(argc>2)
     {
	  int i=1;
	  std::string args(argv[i]);
	  if(args=="-s")
	  {
	       i++;
	       std::string pasword(argv[i]);
	       i++;
	       int port=boost::lexical_cast<int>(argv[i]);
	       server::Service *sv=new server::ControlService(serv,pasword);
	       serv.AddService(sv,port );
	  }
     }
     std::cout<<"System start listen!"<<std::endl;
}
