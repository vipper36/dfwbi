package nyapc.crawler.dao;
import java.util.List;

public interface WrapperDao {
	WrapAtt getWrap(int id);
	int putWrap(WrapAtt wrap);
	boolean updateWrap(String wrap, int id);
	boolean updateWrapGen(String wrapgen, int id);
	List getWrapsByJob(int jobid,String type);
	List listByStat(String stat);
	boolean updateStatByWrapId(int id,String stat);
	List getWrapId(int jid);
	String getWrapType(int id);
	WrapAtt getStudyWrap(int id);
	//把wrapper_list表中学习出错的记录,插入wrapper_study表中
	boolean insertWrapStudyByWrapId(int id);
	//通过界面修改wrapper_study表中的wrapper
	boolean updateWrapFromWrapStudy(String wrap,int id);
	//把正确的wrapper的记录从wrapper_study表中,导入wrapper_list中
	boolean updateWrapListByStudy(String wrap,int id);
	//删除一条wrapper_study
	boolean deleteWrapStudy(int id);
}
