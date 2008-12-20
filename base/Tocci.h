#ifndef _OCCIDATABASE_H_
#define _OCCIDATABASE_H_
#include <occi.h>
#include <string>
#include <iostream>

using namespace oracle::occi;
using namespace std;

class TOcciDatabase
{
public:
     static TOcciDatabase* getInstance(string usr, string passwd, string db);
     int getConnectCount(){ return _Instance->count; };
     Connection* getConnect(string tag);
     ~TOcciDatabase();
protected:
     TOcciDatabase(){};
     TOcciDatabase(string usr, string passwd, string db);

private:
     static TOcciDatabase* _Instance;
     static int count;
     Environment *env;
     StatelessConnectionPool  *connPool;
};


class TOcciQuery
{
private:
     Connection *conn;
     Statement *stmt;
     bool isAutoCommit;
     TOcciQuery(){};
public :
     TOcciQuery(Connection *connect){  conn = connect; };
     void beginTrans();
     void commit();
     void roolback();
     boolean getAutoCommit();
     ResultSet* executeQuery(string sql) ;
     void executeUpdate(string sql) ;
     void close() { if(stmt != NULL) conn->terminateStatement (stmt); };
     void close(ResultSet* rs);
};

#endif /*_OCCIDATABASE_H_*/
