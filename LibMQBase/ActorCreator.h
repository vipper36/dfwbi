#ifndef _ACTOR_CREATOR_
#define _ACTOR_CREATOR_
#include "dllapi.h"
#include <Theron/Actor.h>
typedef void* (*DLLFUN)();
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
    Theron::Actor *operator()(const std::string &funName);
    ~ActorCreator()
    {
        myFreeLibrary(funHandle);
    }
};
#endif
