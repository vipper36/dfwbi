#include <stdio.h>
#include "BaseException.h"
#include "ActorCreator.h"
void ActorCreator::setPath(const std::string &path)
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
ActorCreator::ActorCreator(const std::string &path)
    :dll_path(path),
     funHandle(NULL)
{
    funHandle=myLoadLibrary(const_cast<char*>(dll_path.c_str()));
    if (funHandle==NULL)
    {
        throw BaseException(UnKnownActor, "Unknown Actor" );
    }
}
Theron::Actor *ActorCreator::operator()(const std::string &funName)
{

    DLLFUN fun=(DLLFUN)myGetProcAddress(funHandle,const_cast<char *>(funName.c_str()));
    if (fun==NULL)
    {
        throw BaseException(UnKnownActor, "Error Actor Type" );
    }
    Theron::Actor *ret=(Theron::Actor *)fun();
    if (ret==NULL)
    {
        throw BaseException(UnKnownActor, "Error Create Actor" );
    }
    return ret;
}
