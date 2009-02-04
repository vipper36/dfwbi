
#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Service.h"
#include "Logger.h"
namespace server {


     class RequestHandler:public boost::enable_shared_from_this<RequestHandler>
     {
     public:

	  /**
	   * Empty Constructor
	   */
	  RequestHandler();

	  RequestHandler(Service *sv);

	  /**
	   * Empty Destructor
	   */
	  virtual ~RequestHandler ( );

	  /**
	   */
	  void operator()(std::istream& in, std::ostream& out);

     private:
	  common::Logger *log;

	  Service *service;
	  /**
	   * Set the value of service
	   * @param new_var the new value of service
	   */
     public:
	  void setService ( Service *sv )   {
	       service = sv;
	  }

	  /**
	   * Get the value of service
	   * @return the value of service
	   */
	  Service *getService ( )   {
	       return service;
	  }
     }; // end of package namespace
     typedef boost::shared_ptr<RequestHandler> RequestHandler_ptr;
}
#endif // REQUESTHANDLER_H
