#include <fastcgi++/manager.hpp>
#include "CommandHandler.hpp"
void error_log(const char* msg)
{
   using namespace std;
   using namespace boost;
   static ofstream error;
   if(!error.is_open())
   {
      error.open("/tmp/errlog", ios_base::out | ios_base::app);
      error.imbue(locale(error.getloc(), new posix_time::time_facet()));
   }

   error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}

int main()
{
   try
   {
      Fastcgipp::Manager<CommandHandler> fcgi;
      fcgi.handler();
   }
   catch(std::exception& e)
   {
      error_log(e.what());
   }
}
