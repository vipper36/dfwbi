package nyapc.crawler.dao;

import java.util.List;



public interface JobDao {
	boolean updateJob(int jid);
	JobAtt getJob(int jid);
	List getAllJob();
	List getAllJobWrapInvalid();
	List getAllJobWrapStudy();
	int AddJob(JobAtt jod);
	int del(int id);
	int updateJobUrl(int jid,String url);
	boolean needUpdate(int jobId);
}
