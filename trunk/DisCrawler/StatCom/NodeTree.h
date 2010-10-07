#ifndef __NODE_TREE_
#define __NODE_TREE_
#include <list>
#include <iostream>
#include <math.h>
#include "nsIXpathUtil.h"
#include "nsIDOMNode.h"
#include "nsIDomAttUtil.h"
class NodeTree
{
private:
     std::list<NodeTree> subs;
     nsIDOMNode *node;
     double area;
public:
     NodeTree(nsIDOMNode* anode,double a)
	  {
	       node=anode;
	       area=a;
	  }
     NodeTree():node(nsnull),area(0)
	  {
	  }
     NodeTree(const NodeTree &tree):
	  node(tree.GetNode()),area(tree.GetArea())
	  {
	       subs.insert(subs.begin(),tree.GetSubs().begin(),tree.GetSubs().end());
	  }
     bool AddSub(NodeTree anode)
	  {
	       nsIDOMNode* tmp=anode.GetNode();
	       
	       bool added=false;
	       std::list<NodeTree>::iterator last=subs.begin();
	       for(std::list<NodeTree>::iterator it=subs.begin();it!=subs.end();++it)
	       {
		    nsIDOMNode* tmpsub=it->GetNode();
		    if(IsAncest(tmp,tmpsub))
		    {
			 anode.AddSub(*it);
			 if(it==subs.begin())
			 {
			      subs.erase(it);
			      it=subs.begin();
			      last=subs.begin();
			 }else
			  {
			      subs.erase(it);
			      it=last;
			  }
			 
		    }else if(IsAncest(tmpsub,tmp))
		    {
			 it->AddSub(anode);
			 added=true;
			 break;
		    }else
		    {
			 last=it; 
		    }
		    
	       }
	       if(!added)
		    subs.push_back(anode);
	  }
     const std::list<NodeTree> &GetSubs() const
	  {
	       return subs;
	  }
     void SetArea(double a)
	  {
	       area=a;
	  }
     double GetArea() const
	  {
	       return area;
	  }
     void SetNode(nsIDOMNode* anode)
	  {
	       node=anode;
	  }
     nsIDOMNode* GetNode() const
	  {
	       return node;
	  }
     
     void GetAll(std::list<nsIDOMNode*> &tar)
	  {
	       if(node!=nsnull)
		    tar.push_back(node);
	       for(std::list<NodeTree>::iterator it=subs.begin();it!=subs.end();++it)
		    it->GetAll(tar);
	  }
     void PrintTree(nsIXpathUtil *xpathUtil)
	  {
	       nsCString xpath;
		    
	       if(node!=nsnull)
		    xpathUtil->GetXpath(node, 1,xpath);
	       std::cout<<GetArea()<<"----"<<node<<"----"<<xpath.get()<<"\n";
	       int i=0;
	       for(std::list<NodeTree>::iterator it=subs.begin();it!=subs.end();++it)
	       {
		    std::cout<<i<<"--\t";
		    it->PrintTree(xpathUtil);    
		    i++;
	       }
	       
	  }
     void PrintTree()
	  {
	       std::cout<<GetArea()<<"----"<<node<<"\n";
	       int i=0;
	       for(std::list<NodeTree>::iterator it=subs.begin();it!=subs.end();++it)
	       {
		    std::cout<<i<<"--\t";
		    it->PrintTree();    
		    i++;
	       }
	       
	  }
     bool IsAncest(nsIDOMNode *anc,nsIDOMNode *node)
	  {
	       nsIDOMNode* pNode=node;
	       while(pNode!=nsnull&&pNode!=anc)
	       {
		    pNode->GetParentNode(&pNode);
	       }
	       if(pNode==anc)
		    return true;
	       else
		    return false;
	  }
     void ArrangeTree()
	  {
	       std::list<NodeTree>::iterator last=subs.begin();
	       for(std::list<NodeTree>::iterator it=subs.begin();it!=subs.end();)
	       {
		    it->ArrangeTree();
		    std::cout<<"area:"<<it->GetArea()<<"\n";
		    std::cout<<"area:"<<exp(-it->GetArea()*5)<<"\n";

		    double subSum=0;
		    std::list<NodeTree> tmpsubs=it->GetSubs();
		    std::cout<<"sub count:"<<tmpsubs.size()<<"\n";
		    for(std::list<NodeTree>::iterator sit=tmpsubs.begin();sit!=tmpsubs.end();++sit)
		    {
			 subSum+=exp(-sit->GetArea()*10);
		    }
		    std::cout<<"subSum:"<<subSum<<"\n";
		    
		    if(subSum/exp(-it->GetArea()*5)>0.95)
		    {
			 std::cout<<"deal sub\n";
			 for(std::list<NodeTree>::iterator sit=tmpsubs.begin();sit!=tmpsubs.end();++sit)
			 {
			      std::cout<<"push sub\n";
			      subs.push_back(*sit);
			 }
			 if(it==subs.begin())
			 {
			      std::cout<<"erase  begin\n";
			      subs.erase(it);
			      it=subs.begin();
			      last=subs.begin();
			 }
			 else
			 {
			      std::cout<<"erase normal\n";
			      subs.erase(it);
			      it=last;
			      ++it;
			 }
			 PrintTree();
			 
			 
		    }
		    else
		    {
			 last=it;
			 ++it;
		    }
		    
	       }
	  }
};

#endif
