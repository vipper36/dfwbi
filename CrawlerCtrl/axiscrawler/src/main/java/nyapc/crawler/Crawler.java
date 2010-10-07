package nyapc.crawler;

import nyapc.crawler.dao.Task;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

import nyapc.crawler.dao.TaskDao;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class Crawler implements Runnable {
	private static Log log = LogFactory.getLog(CrawlerCtrlImpl.class.getName());
	private static BlockingQueue<Task> taskq = new LinkedBlockingDeque<Task>();
	private static BlockingQueue<Task> wraptaskq = new LinkedBlockingDeque<Task>();
	
	public TaskDao getTaskdao() {
		return taskdao;
	}
	public void setTaskdao(TaskDao taskdao) {
		this.taskdao = taskdao;
	}
	private TaskDao taskdao;
	public Crawler()
	{
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		
		while (!Thread.interrupted()){
			    try {
			    	if(taskq.size()<=500){
				    	for(int i=0;i<300;i++){
				    		Task task = getTaskQueue(10);
				    		if(task !=null){
				    			taskq.add(task);
				    		}else
				    		{
				    			break;
				    		}
				    	}
				    	
			    	}else{
			    		//null
			    	}	  
			    	
			    	if(wraptaskq.size()<=20){
				    	for(int i=0;i<10;i++){
				    		Task task = getWrapTaskQueue(10);
				    		if(task !=null){
				    			wraptaskq.add(task);
				    		}else
				    		{
				    			break;
				    		}	    		
				    	}
			    	}else{
			    		//null
			    	}	    	
			    	
			    	
			     //log.debug("生产：dd"  );
			     Thread.sleep(1000*30);
			     //TimeUnit.MILLISECONDS.sleep(1000*30);
			    } catch (Exception e) {
			        log.debug(e.toString());
			    }
		}

	}
	public Task getTaskQueue(int num) {
		// TODO Auto-generated method stub
		Task ret=null;
		//channel
		if(ret == null){ 
			int jid = taskdao.getJobId("1","0");
			log.debug("chl job id:"+jid);
			if(jid>0){
				ret = taskdao.getTaskQueueChannel(jid,"1",num,"0","-2");
			}
		}
		//column
		if(ret == null){ 
			int jid = taskdao.getJobId("2","0");
			log.debug("col job id:"+jid);
			if(jid>0){
				ret = taskdao.getTaskQueueColumn(jid,"2",num,"0","-2");
			}
		}
		//url
		if(ret == null){ 
			int jid = taskdao.getJobId("3","0");
			log.debug("url job id:"+jid);
			if(jid>0){
				ret = taskdao.getTaskQueueUrl(jid,"3",num,"0","-2");
			}
		}

		return ret;
	}
	public Task getWrapTaskQueue(int num) {
		// TODO Auto-generated method stub
		Task ret=null;
		//channel
		if(ret == null){ 
			int jid = taskdao.getJobId("1","9");
			if(jid>0){
				ret = taskdao.getTaskQueueChannel(jid,"1",num,"9","-3");
			}
		}
		//column
		if(ret == null){ 
			int jid = taskdao.getJobId("2","9");
			if(jid>0){
				ret = taskdao.getTaskQueueColumn(jid,"2",num,"9","-3");
			}
		}
		//url
		if(ret == null){ 
			int jid = taskdao.getJobId("3","9");
			if(jid>0){
				ret = taskdao.getTaskQueueUrl(jid,"3",num,"9","-3");
			}
		}

		return ret;
	}	
	public Task takeTask(int cid) {

		Task rtn = null;
		try {
			if(taskq.size()>0){
				rtn = taskq.take();
				log.debug("taskq.size()>0");
				rtn = taskdao.takeTaskQueue(rtn,cid,"1");
			}
		} catch (InterruptedException e) {

			log.debug(e.toString());
		}
		return rtn;
	}
	public Task takeWrapTask(int cid) {
		Task rtn = null;
		try {
			if(wraptaskq.size()>0){
				rtn = wraptaskq.take();
				rtn = taskdao.takeTaskQueue(rtn,cid,"10");
			}
		} catch (InterruptedException e) {

			log.debug(e.toString());
		}
		return rtn;
	}

}
