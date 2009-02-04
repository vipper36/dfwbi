#include "RequestHandler.h"

// Constructors/Destructors
//  
namespace server
{
     RequestHandler::RequestHandler ( ) {
	  log=common::Logger::Instance();
     }
     RequestHandler::RequestHandler (Service *sv ) {
	  service=sv;
     }
     RequestHandler::~RequestHandler ( ) { }

//  
// Methods
//  
     void RequestHandler::operator()(std::istream& in, std::ostream& out)
     {
	  log->log("RequestHandler call service");
	  service->serve(in,out);
     }


}
