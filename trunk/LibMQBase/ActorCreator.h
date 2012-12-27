#ifndef _ACTOR_CREATOR_
#define _ACTOR_CREATOR_
#include "dllapi.h"
#include <string>
#include "BaseException.h"
#include "ContextManager.h"
typedef void* (*DLLFUN)(void* param);
class PluginParam
{
    public:
    std::string name;
    int count;
    Theron::Framework *framework;
    Theron::Address listenInterAdd;
};
template<typename Param>
class ActorCreator
{
public:
    ActorCreator()
    {
    }
    Theron::ActorRef *operator()(const std::string &path,const std::string &createName,const std::string &regName,Param &param)
    {
        ContextManager *cm=ContextManager::Instance();
        HINSTANCE funHandle=cm->getFunHandler(path);
        DLLFUN fun=(DLLFUN)myGetProcAddress(funHandle,const_cast<char *>(createName.c_str()));
        if (fun==NULL)
        {
            throw BaseException(UnKnownActor, "Error Actor Type" );
        }
        DLLFUN regfun=(DLLFUN)myGetProcAddress(funHandle,const_cast<char *>(regName.c_str()));
        if (regfun==NULL)
        {
            throw BaseException(UnKnownActor, "Error Actor Type" );
        }
        regfun((void*)cm);
        Theron::ActorRef *ret=(Theron::ActorRef *)fun((void*)&param);
        if (ret==NULL)
        {
            throw BaseException(UnKnownActor, "Error Create Actor" );
        }
        return ret;
    }
    ~ActorCreator()
    {

    }
};
#endif
