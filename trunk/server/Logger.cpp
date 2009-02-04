#include "Logger.h"
#include <iostream>
namespace common
{
     Logger * Logger::m_instance=NULL;
// Constructors/Destructors
//  
     Logger::Logger ( ) {
     }

     Logger::~Logger ( ) { }

//  
// Methods
//  
     void Logger::log(std::string log)
     {
	  std::cout<<log<<std::endl;
     }
     void Logger::log(int log)
     {
	  std::cout<<log<<std::endl;
     }

     Logger* Logger::Instance()
     {
	  if(m_instance==0)
	  {
	       m_instance=new Logger();
	  }
	  return m_instance;
     }
}
