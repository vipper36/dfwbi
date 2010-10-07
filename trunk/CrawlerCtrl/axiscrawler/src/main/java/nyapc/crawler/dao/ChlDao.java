package nyapc.crawler.dao;

import java.util.List;


public interface ChlDao {
	List getChls(int jobid,int num);
	int puttChl(ChlAtt chl);
	ChlAtt get(int id);
	boolean updateStat(int id,String stat);
	boolean updateStat(int id,String stat,String oldstat);
	int getFailCount(int chlId);
	boolean updateFailCount(int chlId);
	boolean resetFailCount(int chlId);
	boolean updateStatByJobId(int id,String stat);
	boolean updateStatByJobIdAndStatus(int id,String pre_status ,String stat);
	int GetId(String hash);
	int getJobId(int chlId);
}
