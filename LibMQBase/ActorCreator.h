#ifndef _ACTOR_CREATOR_
#define _ACTOR_CREATOR_
#include "dllapi.h"
#include "PluginBase.h"

class ActorCreator
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
    void setPath(const std::string &path);
    ActorCreator(const std::string &path);
    PluginBase *operator()(const std::string &funName,PluginParam &param);
    ~ActorCreator()
    {
        myFreeLibrary(funHandle);
    }
};
#endif
