package nyapc.crawler.dao;

import java.util.List;


public interface ColDao {
	List getCols(int jid,int num);
	int puttCol(ColAtt col);
	ColAtt get(int id);
	boolean updateStat(int id,String stat);
	int getFailCount(int chlId);
	boolean resetFailCount(int colId);
	boolean updateFailCount(int chlId);	
	boolean updateStatByJobId(int id,String stat);
	boolean updateStatByJobIdAndStatus(int id,String pre_status ,String stat);
	String getAlias(int id);
	boolean SetAlias(int id,String alias);
	boolean updateName(int id,String name);
	int GetId(String hash);
	int getJobId(int colid);
	int getChlId(int colid);
	boolean needUpdate(int colId);
	boolean updateFinStat(int id,String stat);
}
