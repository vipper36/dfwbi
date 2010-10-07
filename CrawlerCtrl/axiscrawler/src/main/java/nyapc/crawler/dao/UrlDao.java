package nyapc.crawler.dao;

import java.util.List;


public interface UrlDao {
	List getUrls(int jid,int num);
	int puttUrl(UrlAtt url);
	boolean updateStat(int id,String stat);
	int getFailCount(int urlId);
	boolean resetFailCount(int urlId);	
	boolean updateFailCount(int urlId);	
	boolean updateStatByJobId(int id,String stat);
	boolean updateStatByJobIdAndStatus(int id,String pre_status ,String stat);
	boolean AddCol(int id,int colid);
	int GetId(String hash);
	int getJobId(int urlId);
	UrlAtt getUrl(int urlId);
	List<Integer> getColIds(int urlId);
	void deleteall();
}
