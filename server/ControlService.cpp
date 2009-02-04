#include "ControlService.h"
#include <list>
#include <boost/algorithm/string.hpp>

// Constructors/Destructors
//  
namespace server {

     ControlService::~ControlService ( ) { }
     ControlService::ControlService (Server &ser, std::string &pass )
	  :server(ser),
	   password(pass)
     {
	  authorized=false;
	  serName="ControlService";
	  log=common::Logger::Instance();
     }
//  
// Methods
//
     void ControlService::serve(std::istream &in,std::ostream &out)
     {
	  log->log("service start responce!");
	  /*if(server.getControlflag())
	    {
	    out<<"only surport one control"<<std::endl;
	    return;
	    }
	    else
	    {
	    server.setControlflag(true);
	    }*/
	  out<<"Remote console"<<std::endl;
	  char line[8192];
	  in.getline(line,8192);
	  printf("%s\n",line);
	  std::string sLine(line);
	  log->log(sLine);
	  try
	  {
	       std::list<std::string> results; 
	       boost::split(results, sLine, boost::is_any_of(" "));
	       std::list<std::string>::const_iterator p = results.begin();
	       if (*p=="password") {
		    std::string pwd = *(++p);
		    if (pwd==password) {
			 out<<"OK"<<std::endl;
			 authorized = true;
		    } else 
			 out<<"Retry password"<<std::endl;
	       } else if (*p=="add") {
		    if(!authorized) out<<"Please login!"<<std::endl;
		    else {
			 std::string servicename=*(++p);
			 int Port=boost::lexical_cast<int>(*(++p));
			 out<<"Server:"<<servicename<<" at:"<<Port<<" alraedy load!"<<std::endl;
		    }
	       } else if (*p=="remove") {
		    if(!authorized) out<<"Please login!"<<std::endl;
		    else {
			 int port =boost::lexical_cast<int>(*(++p));
			 out<<"Server at:"<<port<<" alraedy remove!"<<std::endl;
		    }
	       } else if(*p=="status") {
		    if(!authorized) out<<"Please login!"<<std::endl;
		    else  out<<"Server status"<<std::endl;;
	       } else if(*p=="help") {
		    if(!authorized) out<<"Please login!"<<std::endl;
		    else  out<<"help"<<std::endl;;
	       }
	       else out<<"unknown command\n"<<std::endl;
	  } 
	  catch(std::exception e) {
	       out<<"Backend system exception!"<<std::endl;
	  }
	  
     
     }

     std::string &ControlService::getName()
     {
	  return serName;
     }


}
