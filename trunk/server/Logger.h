
#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace common {
/*
 *The Logger is a implement of singleton pattan
 */ 
class Logger
{
public:
          
     /**
      * Empty Destructor
      */
  
     ~Logger();
     void log(std::string log);
     void log(int log);
     static Logger* Instance();
private:
  Logger();
  static Logger *m_instance;
};
}; // end of package namespace

#endif // LOGGER_H
