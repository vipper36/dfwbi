/*
 * Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WAnchor>
#include "SearchInfo.hpp"
#include "RabbitAmqp.hpp"
using namespace Wt;

/*
 * A simple hello world application class which demonstrates how to react
 * to events, read input, and give feed-back.
 */
class HelloApplication : public WApplication
{
public:
    HelloApplication(const WEnvironment& env);

private:
    WLineEdit *nameEdit_;
    std::list<WWidget*> results;

    void greet();
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
HelloApplication::HelloApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Hello world");                               // application title

//  root()->addWidget(new WText("Your name, please ? "));  // show some text
  nameEdit_ = new WLineEdit(root());                     // allow text input
  nameEdit_->setFocus();                                 // give focus
  nameEdit_->setTextSize(100);
  WPushButton *b = new WPushButton("Search", root()); // create a button
  b->setMargin(5, Left);                                 // add 5 pixels margin

  root()->addWidget(new WBreak());                       // insert a line break

  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  b->clicked().connect(this, &HelloApplication::greet);

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
  nameEdit_->enterPressed().connect
    (boost::bind(&HelloApplication::greet, this));
}

void HelloApplication::greet()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
    if(results.size()>0)
    {
        for(std::list<WWidget*>::iterator it=results.begin();it!=results.end();++it)
        {
            root()->removeWidget(*it);
            delete *it;
        }
        results.clear();
    }
    search::QueryInfo qi;
    qi.query=std::string(nameEdit_->text().toUTF8());
    qi.vdb=std::string("news");
    std::stringstream ss;
    boost::archive::xml_oarchive oa(ss);
    oa << BOOST_SERIALIZATION_NVP(qi);
    
    AMQP::RabbitClient rc("192.168.16.41",5672);
    std::string res=rc.RpcCall(ss.str(),std::string("search.amqp"),std::string("query"));
    std::stringstream resSS(res);
    search::DocList docs;
    boost::archive::xml_iarchive ia(resSS);
    ia >> BOOST_SERIALIZATION_NVP(docs);
    std::cout<<"count:"<<docs.docList.size()<<std::endl;
    for(std::list<search::IndexInfo>::iterator it=docs.docList.begin();it!=docs.docList.end();++it)
    {
        std::map<std::string,std::string>::iterator fit=it->attMap.find("title");
        WAnchor *anchor=new WAnchor(root());
        results.push_back((WWidget*)anchor);
        anchor->setRef(it->uid);
        if(fit==it->attMap.end())
            anchor->setText(WString(it->uid,UTF8));
        else
            anchor->setText(WString(fit->second,UTF8));
        WBreak *abreak=new WBreak(root());
        results.push_back((WWidget*)abreak);
        WText *text=new WText(root());
        results.push_back((WWidget*)text);
        text->setText(WString(it->content,UTF8));
        WBreak *abreak2=new WBreak(root());
        results.push_back((WWidget*)abreak2);

    }
    std::cout<<"end!!!!!!"<<std::endl;
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new HelloApplication(env);
}

int main(int argc, char **argv)
{
  /*
   * Your main method may set up some shared resources, but should then
   * start the server application (FastCGI or httpd) that starts listening
   * for requests, and handles all of the application life cycles.
   *
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */
  return WRun(argc, argv, &createApplication);
}

