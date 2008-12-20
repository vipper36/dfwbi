#include "Tocci.h"
int TOcciDatabase::count = 0;
TOcciDatabase* TOcciDatabase::_Instance = 0;

TOcciDatabase::TOcciDatabase(string usr, string passwd, string db)
{
     try
     {
	  env = Environment::createEnvironment (Environment::DEFAULT);
	  connPool = env->createStatelessConnectionPool (usr, passwd, db,3,20,3);

     }
     catch(SQLException ex) 
     {
	  cout<<"Exception thrown for getConnect"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
};
Connection* TOcciDatabase::getConnect(string tag)
{
     count++;
     return _Instance->connPool->getConnection(tag); 
};
TOcciDatabase::~TOcciDatabase()
{
     try
     {
	  env->terminateStatelessConnectionPool (connPool);
	  Environment::terminateEnvironment (env);
     }
     catch(SQLException ex) 
     {
	  cout<<"Exception thrown for getConnect"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
};

TOcciDatabase* TOcciDatabase::getInstance(string usr, string passwd, string db)
{
     if(_Instance == 0)
     {
	  _Instance = new TOcciDatabase(usr,passwd,db);
     }

     return _Instance;
};

void TOcciQuery::close(ResultSet* rs) 
{
     if(rs != NULL) 
	  stmt->closeResultSet (rs);

     if(stmt != NULL) 
	  conn->terminateStatement (stmt);
};

void TOcciQuery::beginTrans() 
{
     try 
     {
	  isAutoCommit = stmt->getAutoCommit();
	  stmt->setAutoCommit(false);
     }
     catch(SQLException ex) 
     {
	  cout<<"Exception thrown for beginTrans"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
};

void TOcciQuery::commit() 
{
     try
     {
	  conn->commit();
	  stmt->setAutoCommit(isAutoCommit);
     }
     catch(SQLException ex) 
     {
	  cout<<"Exception thrown for commit"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
};

void TOcciQuery::roolback() 
{
     try 
     {
	  conn->rollback();
	  stmt->setAutoCommit(isAutoCommit);
     }
     catch(SQLException ex) 
     {
	  cout<<"Exception thrown for roolback"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
};

boolean TOcciQuery::getAutoCommit() 
{
     boolean result = false;
     try 
     {
	  result = stmt->getAutoCommit();
     }
     catch(SQLException ex) 
     {
	  cout<<"Exception thrown for getAutoCommit"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
     return result;
};

ResultSet* TOcciQuery::executeQuery(string sql) 
{
     ResultSet*rs = NULL;
     try 
     {
	  stmt = conn->createStatement();
	  rs = stmt->executeQuery(sql);
     }
     catch (SQLException ex) 
     {
	  cout<<"Exception thrown for executeQuery"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
     return rs;
};

void TOcciQuery::executeUpdate(string sql) 
{
     try 
     {
	  stmt = conn->createStatement();
	  stmt->executeUpdate(sql);
     }
     catch (SQLException ex) 
     {
	  cout<<"Exception thrown for executeUpdate"<<endl;
	  cout<<"Error number: "<<  ex.getErrorCode() << endl;
	  cout<<ex.getMessage() << endl;
	  throw ex;
     }
};


