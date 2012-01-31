#include "SNGenerator.h"
using namespace zmqWrapper
SNGenerator::m_instance=NULL;
SNGenerator* SNGenerator::Instance()
{
    if(m_instance==0)
    {
        m_instance=new SNGenerator();
    }
    return m_instance;
}
unsigned long SNGenerator::GetSN()
{
    unsigned long ret=m_sn++;
    if(m_sn>=m_longMax)
        m_sn=0;
    return ret;
}
