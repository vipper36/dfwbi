#include "Logger.hpp"
#include <boost/logging/format.hpp>
#include <boost/logging/writer/ts_write.hpp>
#include <boost/logging/format/formatter/high_precision_time.hpp>
#include <boost/logging/format/formatter/named_spacer.hpp>
#include "config_file.hpp"
using namespace boost::logging;
using namespace Base;
// Step 6: Define the filters and loggers you'll use
BOOST_DEFINE_LOG(g_l, log_type)
BOOST_DEFINE_LOG_FILTER(g_l_filter, level::holder)

void init_logs() {
  Configer *conf=Configer::Instance();
  std::string logfile=conf->GetConfig("config.logfile");
  if(logfile.length()>0)
    init_logs(logfile);
  else
    init_logs("log.log");
}
void init_logs(std::string filename) {
     // Add formatters and destinations
     // That is, how the message is to be formatted...
     g_l()->writer().add_formatter( formatter::named_spacer("[%index%] %time% (T%thread%) ")
				    .add("index",formatter::idx() )
				    .add( "thread",formatter::thread_id() )
				    .add( "time",formatter::high_precision_time("$mm:$ss:$micro") ));
     g_l()->writer().add_formatter( formatter::append_newline() );

     //        ... and where should it be written to
     g_l()->writer().add_destination( destination::cout() );
     g_l()->writer().add_destination( destination::dbg_window() );
     g_l()->writer().add_destination( destination::file(filename.c_str()) );
     g_l()->turn_cache_off();
}
