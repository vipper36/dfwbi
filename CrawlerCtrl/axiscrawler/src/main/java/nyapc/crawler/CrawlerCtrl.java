/**
 * CrawlerCtrl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.4 Apr 22, 2006 (06:55:48 PDT) WSDL2Java emitter.
 */

package nyapc.crawler;

public interface CrawlerCtrl extends java.rmi.Remote {
    public int getVersion(int id) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.Task getTask(int cid, int num) throws java.rmi.RemoteException;
    public java.lang.String getWrapper(int id) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.Task getTaskByJobId(int cid, int jid, java.lang.String type, int num) throws java.rmi.RemoteException;
    public boolean putResult(java.lang.String res, int cid) throws java.rmi.RemoteException;
    public int getStat(int cid) throws java.rmi.RemoteException;
    public int addJob(java.lang.String name, java.lang.String url, java.lang.String type, java.lang.String category, java.lang.String dredb, java.lang.String comment) throws java.rmi.RemoteException;
    public boolean delJob(int id) throws java.rmi.RemoteException;
    public int[] getJobID() throws java.rmi.RemoteException;
    public nyapc.crawler.dao.JobAtt getJob(int id) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.JobAtt[] getJobs() throws java.rmi.RemoteException;
    public nyapc.crawler.dao.JobAtt[] getJobsWrapStatInvalid() throws java.rmi.RemoteException;
    public boolean updateJob(int id) throws java.rmi.RemoteException;
    public boolean updateJobUrl(int id, java.lang.String url) throws java.rmi.RemoteException;
    public boolean hasTask(int cid) throws java.rmi.RemoteException;
    public int addCookie(int jobid, java.lang.String logUrl, java.lang.String logName, java.lang.String logPass, java.lang.String cookie, java.lang.String cookType) throws java.rmi.RemoteException;
    public boolean updateCookie(int jobid, java.lang.String cookie) throws java.rmi.RemoteException;
    public java.lang.String getCookie(int jobid) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.LonginInfo getLogInfo(int jobid) throws java.rmi.RemoteException;
    public int[] getLogJobID() throws java.rmi.RemoteException;
    public java.lang.String getWrapGen(int id) throws java.rmi.RemoteException;
    public boolean updateWrapper(java.lang.String wrap, int id, int taskid) throws java.rmi.RemoteException;
    public boolean updateWrapperCheckOk(java.lang.String wrap, int wrapId) throws java.rmi.RemoteException;
    public boolean updateWrapGen(java.lang.String wrapgen, int id) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.Task getWrapTask(int cid, int num) throws java.rmi.RemoteException;
    public int[] getWrapId(int jid) throws java.rmi.RemoteException;
    public java.lang.String getWraptype(int id) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.Task getWrapInvalidTask(int cid, int num) throws java.rmi.RemoteException;
    public nyapc.crawler.dao.Task getWrapInvalidTaskByJobId(int cid, int jid, java.lang.String type, int num) throws java.rmi.RemoteException;
    public boolean addWrapper(int jobId, java.lang.String type, java.lang.String wrapper, java.lang.String vargen, java.lang.String comment) throws java.rmi.RemoteException;
    public boolean deleteWrapStudy(int id) throws java.rmi.RemoteException;
    public java.lang.String getStudyWrapper(int id) throws java.rmi.RemoteException;
}
