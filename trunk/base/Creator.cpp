#include "Creator.h"
#include "Factory.h"
Registor *Registor::m_instance=NULL;
std::string Registor::m_subname;
Registor *Registor::Instance()
{
    if(m_instance==0)
    {
        m_instance=new Registor;
    }
    return m_instance;
}
Registor::Registor()
{
    m_subname=std::string("main");
}
bool Registor::SetSub(std::string &name)
{
    m_subname=name;
    return true;
}

Registor::~Registor()
{
}
CaxMessage *Registor::CreateTradMsg()
{
    return new CaxTradMessage();
}

CaxMessage *Registor::CreateWCOEMsg()
{
    return new WCOEPMessage();
}
CaxMessage *Registor::CreateWCOTMsg()
{
    return new WCOTIXMessage();
}

CaxAction *Registor::CreateSendAction()
{
    return new SendAction(m_subname);
}

CaxAction *Registor::CreateRecvAction()
{
    return new RecvAction(m_subname);
}
CaxAction *Registor::CreateSaveDBAction()
{
    XMLConfiger *configer=XMLConfiger::Instance();
    SaveDBAction *tmp=new SaveDBAction();
    std::string tmpAttName("SaveFlag");
    std::string strFlag=configer->GetMsgTypeAtt(m_subname,tmpAttName);
    int flag=atoi(strFlag.c_str());
    tmp->SetFlag(flag);
    tmpAttName=std::string("NewIdFlag");
    strFlag=configer->GetMsgTypeAtt(m_subname,tmpAttName);
    char idFlag=atoi(strFlag.c_str());
    tmp->SetNewIdFlag(idFlag);
    return tmp;
}

CaxAction *Registor::CreateReadDBAction()
{
    XMLConfiger *configer=XMLConfiger::Instance();
    ReadDBAction *tmp=new ReadDBAction();
    std::string tmpAttName("ReadFlag");
    std::string strFlag=configer->GetMsgTypeAtt(m_subname,tmpAttName);
    int flag=atoi(strFlag.c_str());
    tmp->SetFlag(flag);
    tmpAttName=std::string("IDFlag");
    strFlag=configer->GetMsgTypeAtt(m_subname,tmpAttName);
    char idFlag=strFlag.c_str()[0];
    tmp->SetIDFlag(idFlag);
    return tmp;
}
void Registor::RegistMSG()
{
    Factory<CaxMessage,std::string> *msgFactory=Factory<CaxMessage,std::string>::Instance();
    msgFactory->Register(std::string("CaxTrad"),&(Registor::CreateTradMsg));
    msgFactory->Register(std::string("WCOE"),&(Registor::CreateWCOEMsg));
    msgFactory->Register(std::string("WCOT"),&(Registor::CreateWCOTMsg));
}

void Registor::RegistAct()
{
    Factory<CaxAction,std::string> *actFactory=Factory<CaxAction,std::string>::Instance();
    actFactory->Register(std::string("Sender"),&(Registor::CreateSendAction));
    actFactory->Register(std::string("Reciever"),&(Registor::CreateRecvAction));
    actFactory->Register(std::string("SaveDB"),&(Registor::CreateSaveDBAction));
    actFactory->Register(std::string("ReadDB"),&(Registor::CreateReadDBAction));
}



