
#ifndef LISTENER_H
#define LISTENER_H
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <deque>
#include "Logger.h"
#include "Connection.h"
typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
typedef std::deque<io_service_ptr> ios_deque;
namespace server {
class Service;
class Server;
/**
 * class Listener
 * 
 */

     class Listener: public boost::enable_shared_from_this<Listener>,
	  private boost::noncopyable
     {
     public:
	  ~Listener ();
	  explicit Listener (Server &ser, int p, Service *sv);
	  /**
	   */
	  void pleaseStop ( );
	  /**
	   */
	  void run ( );
	  void handle_accept(connection_ptr conn,const boost::system::error_code& e);
     private:
	  boost::thread_group thr_grp;
	  boost::asio::io_service mIo_s;
	  boost::asio::ip::tcp::acceptor mAcceptor;
	  int threadcount;
	  int port;
	  std::string ServiceName;
	  common::Logger *log;
	  Service *service;
	  Server &server;
     public:
	  /**
	   * Set the value of threadcount
	   * @param count the new value of threadcount
	   */
	  void setThreadcount ( int count )   {
	       threadcount = count;
	  }

	  /**
	   * Get the value of threadcount
	   * @return the value o threadcount
	   */
	  int getThreadcount ( )   {
	       return threadcount;
	  }
	  /**
	   * Set the value of port
	   * @param new_var the new value of port
	   */
	  void setPort ( int p )   {
	       port = p;
	  }

	  /**
	   * Get the value of port
	   * @return the value of port
	   */
	  int getPort ( )   {
	       return port;
	  }

	  /**
	   * Set the value of ServiceName
	   * @param new_var the new value of ServiceName
	   */
	  void setService ( Service *sv );

	  /**
	   * Get the value of ServiceName
	   * @return the value of ServiceName
	   */
	  Service* getService ( )   {
	       return service;
	  }

	  /**
	   * Set the value of server
	   * @param new_var the new value of server
	   */
	  void setServer ( Server &ser );

	  /**
	   * Get the value of server
	   * @return the value of server
	   */
	  Server &getServer ( )   {
	       return server;
	  }
     };
     typedef boost::shared_ptr<Listener> listener_ptr;
}; // end of package namespace

#endif // LISTENER_H
