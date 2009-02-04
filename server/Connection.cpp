#include <boost/bind.hpp>
#include "Connection.h"
#include <iostream>
#include <sstream>
// Constructors/Destructors
//  
namespace server
{

     Connection::Connection(boost::asio::io_service& io_service,
			    RequestHandler_ptr handler)
	  :mStrand(io_service),
	   mSocket(io_service),
	   reqHandler(handler)
     {
	   log=common::Logger::Instance();
     }

     boost::asio::ip::tcp::socket& Connection::socket()
     {
	  return mSocket;
     }
     void Connection::start()
     {
	  log->log("start connection...");
	  boost::asio::streambuf TmpBuffer;
	  std::ostream os(&TmpBuffer);
	  os<<"hello conneted!"<<std::endl;
	  
	  boost::asio::async_write(mSocket,TmpBuffer,
				   mStrand.wrap(boost::bind(&Connection::handle_write, shared_from_this(),
							    boost::asio::placeholders::error)));
	  mSocket.async_read_some(mBuffer.prepare(8192),
				  mStrand.wrap(boost::bind(&Connection::handle_read, shared_from_this(),
							   boost::asio::placeholders::error,
							   boost::asio::placeholders::bytes_transferred)));
     }
     void Connection::handle_read(const boost::system::error_code& e,
				  std::size_t bytes_transferred)
     {
	  log->log("handle read...");
	  if(!e) {
	       boost::asio::streambuf TmpBuffer;
	       mBuffer.commit(bytes_transferred);
	       std::istream is(&mBuffer);
	       std::ostream os(&TmpBuffer);
	       (*reqHandler)(is,os);
	       boost::asio::async_write(mSocket,TmpBuffer,
				   mStrand.wrap(boost::bind(&Connection::handle_write, shared_from_this(),
							    boost::asio::placeholders::error)));
	       mSocket.async_read_some(mBuffer.prepare(8192),
				       mStrand.wrap(boost::bind(&Connection::handle_read, shared_from_this(),
								boost::asio::placeholders::error,
								boost::asio::placeholders::bytes_transferred)));
	  }
	  else
	  {
	       shutdown();
	  }
     }

     void Connection::handle_write(const boost::system::error_code& e)
     {
	  if(!e) {
	       log->log("Write finish!");
//	       boost::system::error_code ignored_ec;
//	       mSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_ec);
	  }
	  else
	  {
	       shutdown();
	  }
     }
     void Connection::shutdown() {
	  mSocket.close();
     }
}
//  
// Methods
//  
