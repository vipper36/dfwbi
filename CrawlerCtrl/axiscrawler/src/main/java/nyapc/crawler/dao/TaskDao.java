package nyapc.crawler.dao;

import java.util.HashMap;
import java.util.List;


public interface TaskDao {
    int save(TaskAtt taskAtt);
	int del(int id);
	TaskAtt get(int id);
    List list();
    Task getTask(int cid, int jid,String type,String from_status);
    Task getTask(int cid, int jid,String from_status);
    
    Task getTaskChannel(int cid, int jid,String type,int num,String from_status,String to_status);
    Task getTaskColumn(int cid, int jid,String type,int num,String from_status,String to_status);
    Task getTaskUrl(int cid, int jid,String type,int num,String from_status,String to_status);
    
    
    Task getTaskQueueChannel(int jid,String type,int num,String from_status,String to_status);
    Task getTaskQueueColumn(int jid,String type,int num,String from_status,String to_status);
    Task getTaskQueueUrl(int jid,String type,int num,String from_status,String to_status);
    
    Task takeTaskQueue(Task task,int cid,String to_status);
    
    
    Task getTaskChannelWrapInvalid(int cid, int jid,String type,int num);//供wrap测试使用
    Task getTaskColumnWrapInvalid(int cid, int jid,String type,int num);//供wrap测试使用
    Task getTaskUrlWrapInvalid(int cid, int jid,String type,int num);//供wrap测试使用

    
    int getJobIdFromTask(int cid,String status);
    int getJobId(String type,String status);
    
    int getJobIdByWrapInvalid(String type);
    boolean updateStatByTaskId(int id,String stat);
    boolean updateStatByJobId(int id,String type,String stat);
    boolean updateRelationStatByTaskId(int id,String stat);
    
    void restartTomcat();
}
