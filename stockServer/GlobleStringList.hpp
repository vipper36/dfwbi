#ifndef __GLOBLE_STRING_LIST_INC_
#define __GLOBLE_STRING_LIST_INC_
#include <string>
#include <list>
#include "BaseException.hpp"
namespace Factory
{
    class GlobleSL
    {
    public:
        static GlobleSL* Instance()
            {
                if(m_instance==0)
                {
                    m_instance=new GlobleSL();
                }
                return m_instance;
            }
        static void Destroy()
            {
                delete m_instance;
            }
        std::list<std::string>::iterator AddString(std::string s)
            {
                _list.push_back(s);
                return back(std::list<std::string>::iterator);
            }
        void DelString(std::list<std::string>::iterator it)
            {
                _list.erase(it);
            }
    protected:
        ~GlobleSL()
            {
            }
    
        GlobleSL():
            {
            }
    private:
        std::list<std::string> _list;
        static GlobleSL* m_instance;
    };
    GlobleSL* GlobleSL::m_instance=NULL;
}
#endif
