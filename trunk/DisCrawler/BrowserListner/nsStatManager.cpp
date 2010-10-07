#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsStatManager.h"
#include "nsIWebNavigation.h"
#include "nsIWebBrowser.h"
#include "nsISoapInter.h"
#include "nsISoapTask.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsStatManager, nsIStatManager)



nsStatManager::nsStatManager()
{
  /* member initializers and constructor code */
}

nsStatManager::~nsStatManager()
{
  /* destructor code */
}

/* void SetBrowser (in nsIWebBrowser browser, in long id); */
NS_IMETHODIMP nsStatManager::SetBrowser(nsIWebBrowser *browser, PRInt32 id)
{
     LOG<<"browser:"<<browser<<" id:"<<id<<"\n";
     std::map<int,nsIWebBrowser *>::iterator fit=bMap.find(id);
     if(fit!=bMap.end())
     {
	  fit->second=browser;
	  sMap[fit->first]=NOT_START;
     }
     else
     {
	  bMap.insert(std::make_pair(id,browser));
	  sMap.insert(std::make_pair(id,0));
     }
     return NS_OK;
}

/* void ChangeStat (in long id, in unsigned short stat); */
NS_IMETHODIMP nsStatManager::ChangeStat(PRInt32 id, PRUint16 stat)
{
     LOG<<"change stat:id="<<id<<" stat="<<stat<<"\n";
     std::map<PRInt32,PRUint16>::iterator fit=sMap.find(id);
     if(fit!=sMap.end())
     {
	  fit->second=stat;
     }
     if(IsReady())
     {
	  StopBrowers();
	  Excute();
	  exit(0);
     }
     return NS_OK;
}
/* void SetTask (in nsISoapTask task); */
NS_IMETHODIMP nsStatManager::SetTask(nsISoapTask *task)
{
  m_task=task;
    return NS_OK;
}

/* void SetInter (in nsISoapInter inter); */
NS_IMETHODIMP nsStatManager::SetInter(nsISoapInter *inter)
{
  m_inter=inter;
    return NS_OK;
}
/* void SetCid (in long id); */
NS_IMETHODIMP nsStatManager::SetCid(PRInt32 id)
{
	cid=id;
    return NS_OK;
}

void nsStatManager::StopBrowers()
{
     for(std::map<int,nsIWebBrowser *>::iterator it=bMap.begin();it!=bMap.end();++it)
     {
	   nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(it->second);
	   nav->Stop(nsIWebNavigation::STOP_ALL);
     }
}
bool nsStatManager::IsReady()
{
     int readycount=0;
     int finCount=0;
     for(std::map<PRInt32,PRUint16>::iterator it=sMap.begin();it!=sMap.end();++it)
     {
	  if(it->second>RUNNING)
	  {
	       if(it->second==FIN_DOC||it->second==FINISH)
		    finCount++;
	       readycount++;
	  }
     }
     LOG<<"count:"<<readycount<<" map size:"<<sMap.size()<<"\n";
     if(double(readycount)/sMap.size()>0.8||double(finCount)/sMap.size()>0.7)
     {
	  return true;
     }else
     {
	  return false;
     }
}
