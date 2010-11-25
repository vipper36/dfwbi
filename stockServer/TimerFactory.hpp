#ifndef __LOKI_TIMERFACTORY_INC_
#define __LOKI_TIMERFACTORY_INC_
#include <string>
#include <map>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "BaseException.hpp"
#include "ActorCreator.hpp"
#include <Theron/Framework.h>
namespace Factory
{
    class TimerFactory
    {
    public:
        static TimerFactory* Instance()
            {
                if(m_instance==0)
                {
                    m_instance=new TimerFactory();
                }
                return m_instance;
            }
        static void Destroy()
            {
                delete m_instance;
            }
        void Run()
            {
                io.run();
            }
        boost::asio::deadline_timer* CreateTimer()
            {
                return new boost::asio::deadline_timer(io);
            }
    protected:
        ~TimerFactory()
            {
            }
    
        TimerFactory():io(20)
            {
            }
    private:
        boost::asio::io_service io;
        static TimerFactory* m_instance;
    };
    TimerFactory* TimerFactory::m_instance=NULL;
}
#endif
