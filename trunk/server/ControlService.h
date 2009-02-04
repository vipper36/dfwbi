
#ifndef CONTROLSERVICE_H
#define CONTROLSERVICE_H
#include "Service.h"
#include "Server.h"
#include <string>

namespace server {


/**
 * class ControlService
 * 
 */

     class ControlService : public Service
     {
     public:
	  /**
	   * Empty Destructor
	   */
	  virtual ~ControlService ( );

	  // Public attributes
	  //  

	  Server &server;

	  /**
	   * Set the value of server
	   * @param new_var the new value of server
	   */
	  void setServer (Server &serv )   {
	       server = serv;
	  }

	  /**
	   * Get the value of server
	   * @return the value of server
	   */
	  Server &getServer ( )   {
	       return server;
	  }


	  /**
	   * @param  server
	   * @param  password
	   */
	  ControlService (Server &server, std::string &password );

	  void serve(std::istream &in,std::ostream &out);

	  std::string &getName();
     private:
	  std::string password;
	  std::string serName;
	  common::Logger *log;
	  bool authorized;
     public:

	  /**
	   * Set the value of password
	   * @param new_var the new value of password
	   */
	  void setPassword ( std::string pass )   {
	       password = pass;
	  }

	  /**
	   * Get the value of password
	   * @return the value of password
	   */
	  std::string getPassword ( )   {
	       return password;
	  }

     };
}; // end of package namespace

#endif // CONTROLSERVICE_H
