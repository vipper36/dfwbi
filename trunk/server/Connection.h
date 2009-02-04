
#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "RequestHandler.h"

namespace server {
     class Connection
	  : public boost::enable_shared_from_this<Connection>,
	  private boost::noncopyable
	  {
	  public:
	       explicit Connection(boost::asio::io_service& io_service,
				   RequestHandler_ptr handler);

	       boost::asio::ip::tcp::socket& socket();
	       /**
		  /**
		  * Empty Constructor
		  */

	       void start();
	       /**
		* Set the value of reqHandler
		* @param new_var the new value of reqHandler
		*/
	       void setReqHandler ( RequestHandler_ptr req )   {
		    reqHandler = req;
	       }

	       /**
		* Get the value of reqHandler
		* @return the value of reqHandler
		*/
	       RequestHandler_ptr getReqHandler ( )   {
		    return reqHandler;
	       }

	  private:
	       
	       void handle_read(const boost::system::error_code& e,
				std::size_t bytes_transferred);
	       void shutdown();
	       void handle_write(const boost::system::error_code& e);

	       common::Logger *log;

	       RequestHandler_ptr reqHandler;

	       boost::asio::io_service::strand mStrand;

	       
	       boost::asio::ip::tcp::socket mSocket;


	       boost::asio::streambuf mBuffer;

	  };
     typedef boost::shared_ptr<Connection> connection_ptr;
}; // end of package namespace

#endif // CONNECTION_H
