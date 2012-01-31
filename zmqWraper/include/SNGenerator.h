#ifndef __MSG_SNGENERATOR_H__
#define __MSG_SNGENERATOR_H__
#include <limits>
namespace zmqWrapper
{
    class SNGenerator
    {
    private:
        unsigned long m_longMax;
        unsigned long m_sn;
    public:
        static SNGenerator* Instance();
        unsigned long GetSN();
    private:
        ~SNGenerator()
            {
            }
        SNGenerator()
            {
                m_sn=0;
                m_longMax=std::numeric_limits<unsigned long>::max();
            }
    private:
    
        static SNGenerator* m_instance;
    };
};


#endif
