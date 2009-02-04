#include "Listener.h"
#include "Service.h"
#include "Server.h"
#include "RequestHandler.h"
#include "Connection.h"
namespace server {
     void Listener::setService ( Service *sv )   {
	  service = sv;
	  ServiceName=sv->getName();
     }


     Listener::Listener (Server &ser, int p, Service *sv)
	  :server(ser),
	   port(p),
	   service(sv),
	   mAcceptor(mIo_s)
     {
	  log=common::Logger::Instance();
	  ServiceName=service->getName();
	  threadcount=1;
	  boost::asio::ip::tcp::endpoint endpoint =boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port);
	  mAcceptor.open(endpoint.protocol());
	  mAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	  mAcceptor.bind(endpoint);
	  mAcceptor.listen();
	  RequestHandler_ptr reqh(new RequestHandler(service));
	  connection_ptr conn(new Connection(mIo_s, reqh));
	  log->log("start accept at:");
	  log->log(port);
	  mAcceptor.async_accept(conn->socket(),
				 boost::bind(&Listener::handle_accept, this,conn,
					     boost::asio::placeholders::error));
     }
     Listener::~Listener ( ) { }
     void Listener::setServer ( Server &ser )
     {
	  server = ser;
     }
     void Listener::pleaseStop ( )
     {
	  mIo_s.stop();
     }
     void Listener::run ( )
     {
	  log->log("start listening..");
	  for (int i = 0; i < threadcount; ++i) {
	       thr_grp.create_thread(boost::bind(&boost::asio::io_service::run, &mIo_s));
	  }
	  thr_grp.join_all();
     }
     void Listener::handle_accept(connection_ptr conn,const boost::system::error_code& e)
     {
	  if (!e)
	  {
	       log->log("handle accept...");
	       conn->start();
	       RequestHandler_ptr reqh(new RequestHandler(service));
	       connection_ptr conn(new Connection(mIo_s, reqh));
	       mAcceptor.async_accept(conn->socket(),
				      boost::bind(&Listener::handle_accept, this,conn,
						  boost::asio::placeholders::error));
	  }
     }
}


