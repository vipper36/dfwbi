#ifndef _ACTOR_CREATOR_
#define _ACTOR_CREATOR_
#include "dllapi.h"
#include "PluginBase.h"
typedef void* (*DLLFUN)(void* param);
class PluginParam
{
    std::string name;
    Theron::Framework *m_framework;
};
class ActorCreator<Param>
{
private:
    std::string dll_path;
    HINSTANCE funHandle;
public:
    ActorCreator()
        :dll_path(),
         funHandle(NULL)
    {
    }
    void setPath(const std::string &path)
    {
        if(dll_path.length()>0&&funHandle!=NULL)
        {
            myFreeLibrary(funHandle);
        }
        dll_path=path;
        funHandle=myLoadLibrary(const_cast<char*>(dll_path.c_str()));
        if (funHandle==NULL)
        {
            throw BaseException(UnKnownActor, "Unknown Actor" );
        }
    }
    ActorCreator(const std::string &path)
        :dll_path(path),
         funHandle(NULL)
    {
        funHandle=myLoadLibrary(const_cast<char*>(dll_path.c_str()));
        if (funHandle==NULL)
        {
            throw BaseException(UnKnownActor, "Unknown Actor" );
        }
    }
    Theron::ActorRef *operator()(const std::string &funName,Param &param)
    {

        DLLFUN fun=(DLLFUN)myGetProcAddress(funHandle,const_cast<char *>(funName.c_str()));
        if (fun==NULL)
        {
            throw BaseException(UnKnownActor, "Error Actor Type" );
        }
        Theron::ActorRef *ret=(Theron::ActorRef *)fun((void*)&param);
        if (ret==NULL)
        {
            throw BaseException(UnKnownActor, "Error Create Actor" );
        }
        return ret;
    }
    ~ActorCreator()
    {
        myFreeLibrary(funHandle);
    }
};
#endif
