#ifndef __CREATOR_H__
#define __CREATOR_H__
#include "CaxTradMessage.h"
#include "WCOEPMessage.h"
#include "WCOTIXMessage.h"
#include "SendAction.h"
#include "RecvAction.h"
#include "SaveDBAction.h"
#include "ReadDBAction.h"
#include "XMLConfiger.h"
class Registor
{
private:
    static CaxMessage *CreateTradMsg();
    static CaxMessage *CreateWCOEMsg();
    static CaxMessage *CreateWCOTMsg();
    static CaxAction *CreateSendAction();
    static CaxAction *CreateRecvAction();
    static CaxAction *CreateSaveDBAction();
    static CaxAction *CreateReadDBAction();
    static Registor *m_instance;
    static std::string m_subname;
protected:
    Registor();
    ~Registor();
public:
    bool SetSub(std::string &name);
    static Registor* Instance();
    void RegistMSG();
    void RegistAct();
};
#endif
