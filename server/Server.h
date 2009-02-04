
#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <map>
#include "Listener.h"

namespace server {

     class Server
     {
     public:

	  /**
	   * Empty Constructor
	   */
	  Server ( );

	  /**
	   * Empty Destructor
	   */
	  virtual ~Server ( );

	  /**
	   * @param  maxConn
	   */
	  Server (int maxConn );
	  /**
	   * @param  service
	   * @param  port
	   */
	  bool AddService(Service *sv,int port );
	  /**
	   * @return undef
	   * @param  port
	   */
	  bool removeService(int port );

	  /**
	   */
	  void displayStatus ( );

	  
	  int getConnId();
	  listener_ptr GetListener(int port);
	  void setControlflag(bool flag);
	  bool getControlflag();
     private:
	  bool controlflag;
	  int conn_id;
	  std::map<int,listener_ptr> listeners;
	  common::Logger *log;
     };
}; // end of package namespace

#endif // SERVER_H
