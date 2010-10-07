package nyapc.crawler;


import java.io.IOException;
import java.io.StringReader;


import java.util.List;

import javax.jws.WebService;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.rpc.ServiceException;

import nyapc.crawler.dao.AgentDao;


import nyapc.crawler.dao.*;


import nyapc.crawler.dao.JobDao;

import nyapc.crawler.dao.TaskDao;
import nyapc.crawler.dao.UrlAtt;
import nyapc.crawler.dao.UrlDao;
import nyapc.crawler.dao.WrapAtt;
import nyapc.crawler.dao.WrapperDao;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import org.springframework.remoting.jaxrpc.ServletEndpointSupport;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;


public class CrawlerCtrlImpl extends ServletEndpointSupport implements nyapc.crawler.CrawlerCtrl {

    private static Log log = LogFactory.getLog(CrawlerCtrl.class.getName());
    private ApplicationContext ctx = null;
    private ChlDao chldao = null;
    private ColDao coldao = null;
    private UrlDao urldao = null;
    private WrapperDao wrapdao = null;
    private JobDao jobdao = null;
    private ResultHandler handler = null;
    private AgentDao agentdao = null;
    private CrawlerDao crawlerdao = null;
    private TaskDao taskdao = null;
    private CookieDao cookieDao = null;
    private Crawler crawtask = null;
    protected void onInit() throws ServiceException {
        ctx = (ApplicationContext) getApplicationContext();
        chldao = (ChlDao) ctx.getBean("ChlDao");
        coldao = (ColDao) ctx.getBean("ColDao");
        urldao = (UrlDao) ctx.getBean("UrlDao");
        wrapdao = (WrapperDao) ctx.getBean("WrapDao");
        jobdao = (JobDao) ctx.getBean("JobDao");
        handler = (ResultHandler) ctx.getBean("ResultHandler");
        agentdao = (AgentDao) ctx.getBean("AgentDao");
        crawlerdao = (CrawlerDao) ctx.getBean("CrawlerDao");
        taskdao = (TaskDao) ctx.getBean("TaskDao");
        cookieDao = (CookieDao) ctx.getBean("CookieDao");
        crawtask = (Crawler) ctx.getBean("Crawler");

        cookieDao = (CookieDao) ctx.getBean("CookieDao");
        log.debug("######### static block");

        if (taskdao != null) {
            log.debug("#########ss  into ");
            taskdao.restartTomcat();
        } else {
            log.debug("######### null");
        }

        Thread pt = new Thread(crawtask);
        pt.start();
    }

	@Override
	public Task getWrapTask(int cid,int num) {
		Task ret=null;
		boolean sysError=false;
		//task，先从task表冲取status=10的
		if(ret == null){ 
			int jid = taskdao.getJobIdFromTask(cid,"10");//from task_list
			if(jid>0){
				ret = taskdao.getTask(cid,jid,"10");
			}
			else
			{
				if(jid==-2)
					sysError=true;
			}
			log.debug("1111111111111");
		}
		if(!sysError)
		{
			if(ret == null){
				ret = crawtask.takeWrapTask(cid);
			}
		}
		return ret;
	}

	@Override
	public Task getWrapInvalidTask(int cid,int num) {
		Task ret=null;

		//task，先从task表冲取status=11的
		if(ret == null){ 
			int jid = taskdao.getJobIdFromTask(cid,"11");//from task_list
			if(jid>0){
				ret = taskdao.getTask(cid,jid,"11");
			}
			log.debug("1111111111111");
		}




		//channel
		if(ret == null){ 
			int jid = taskdao.getJobIdByWrapInvalid("1");
			if(jid>0){
				ret = taskdao.getTaskChannel(cid,jid,"1",num,"10","11");
			}
			log.debug("2222222");
		}


		//column
		if(ret == null){ 
			//最近的10条50％为9，才retun task，否则为null
			int jid = taskdao.getJobIdByWrapInvalid("2");
			if(jid>0){
				ret = taskdao.getTaskColumn(cid,jid,"2",num,"10","11");
			}
			log.debug("333333333");
		}

		//url
		if(ret == null){ 
			//最近的20条50％为9，才retun task，否则为null
			int jid = taskdao.getJobIdByWrapInvalid("3");
			if(jid>0){
				ret = taskdao.getTaskUrl(cid,jid,"3",num,"10","11");
			}
			log.debug("4444");
		}

		//置成1，表示正在进行中
		wrapdao.updateStatByWrapId(ret.getWrap_id(),"1");		

		return ret;
	}


	@Override
	public String getWrapper(int id) {
		WrapAtt tmp=wrapdao.getWrap(id);
		return tmp.getWrapper();
	}

	@Override
	public boolean updateWrapper(String wrap, int id,int taskid) {
		
		WrapAtt  wrapAtt= wrapdao.getWrap(id);
		
		log.debug("wrap length:"+wrap.length()+" wrapper id:"+id+" wrapper type:"+wrapAtt.getType());
		wrapdao.insertWrapStudyByWrapId(wrapAtt.getId());
		if(wrap.length()>0)
		{
			log.debug("111111111");
			wrapdao.updateWrapFromWrapStudy(wrap, wrapAtt.getId());
		}
		

		//wraptask完成，从9错误——0（未做状态）
		//目前，学习成功和失败，都修改３＋１的状态到０，回头有可能优化
		if(wrapAtt!=null){
			if("1".equals(wrapAtt.getType())){
				//应该只把状态为9,10的给置成0
				log.debug("update chl stat");
				chldao.updateStatByJobIdAndStatus(wrapAtt.getJobid(),"9", "0");
				chldao.updateStatByJobIdAndStatus(wrapAtt.getJobid(),"10", "0");
			}else if("2".equals(wrapAtt.getType())){
				//应该只把状态为9,10的给置成0
				log.debug("update col stat");
				coldao.updateStatByJobIdAndStatus(wrapAtt.getJobid(),"9", "0");
				coldao.updateStatByJobIdAndStatus(wrapAtt.getJobid(),"10", "0");
			}else if("3".equals(wrapAtt.getType())){
				//应该只把状态为9,10的给置成0
				log.debug("update url stat");
				urldao.updateStatByJobIdAndStatus(wrapAtt.getJobid(),"9", "0");
				urldao.updateStatByJobIdAndStatus(wrapAtt.getJobid(),"10", "0");
			}
			taskdao.updateStatByTaskId(taskid, "2");//完成
			//把wrap_stat是-1的,插入wrapper_study表中
			
			//wrapdao.updateStatByWrapId(wrapAtt.getId(),"-1");				
		}
		return true;
	}

	@Override
	public boolean updateWrapperCheckOk(String wrap, int wrapId) {
		boolean rtn = false;		
		if(wrap.length()>0)
		{
			//boolean flag1 = wrapdao.updateWrap(wrap, wrapId);
			//置成0，wrap重新可用
			//wrapdao.updateStatByWrapId(wrapId,"0");	
			wrapdao.updateWrapFromWrapStudy(wrap, wrapId);
			wrapdao.updateWrapListByStudy(wrap,wrapId);
			rtn = true;
		}
		return rtn;
	}

	@Override
	public int getStat(int cid) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override	
	public boolean putResult(String res, int cid) {
		// TODO Auto-generated method stub
		try { 

			res = res.trim();


			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance(); 
			DocumentBuilder builder = factory.newDocumentBuilder();
			StringReader reader = new StringReader( res );
			InputSource inputSource = new InputSource( reader );
			inputSource.setEncoding("utf-8");
			Document document = builder.parse(inputSource);
			Element docEle=document.getDocumentElement();

			int  taskId = Util.str2int(docEle.getAttribute("id"));
			String type= docEle.getAttribute("type");
			log.debug("type:"+type);
			log.debug("taskId:"+taskId);
			if(taskId>0){
				if(type.equals("1")){
					handler.handleChl(docEle, taskId);
				}else if(type.equals("2")){
					handler.handleCol(docEle, taskId);

				}else if(type.equals("3")){
					handler.handleUrl(docEle, taskId);
				}
			}//end taskId>0
		} catch (ParserConfigurationException e) { 
			log.debug(e.getMessage()); 
		} catch (SAXException e) {

			log.debug(e.toString());
		} catch (IOException e) {

			log.debug(e.toString());
		}
		return true;
	}

	@Override
	public int getVersion(int id) {
		WrapAtt wrap=wrapdao.getWrap(id);
		return wrap.getVersion();
	}

	@Override
	public int addJob(String name, String url, String type,String category,String dredb, String comment) {
		JobAtt job=new JobAtt();
		log.debug("start add job");
		job.setName(name);
		job.setSeed(url);
		job.setSeedType(type);
		job.setComment(comment);
		job.setCategory(category);
		job.setDredb(dredb);
		return jobdao.AddJob(job);
	}

	@Override
	public boolean updateJob(int id) {
		//9－》不变
		//2->0 即，从完成转成0
		log.debug("start update job");
		boolean rtn = jobdao.updateJob(id);

		return rtn;
	}


	@Override
	public JobAtt getJob(int id) {
		return jobdao.getJob(id);
	}

	@Override
	public int[] getJobID() {
		List<JobAtt> joblist=jobdao.getAllJob();
		int [] ret=new int[joblist.size()];
		int i=0;
		for(JobAtt job:joblist)
		{
			ret[i]=job.getId();
			i++;
		}

		return ret;
	}

	@Override
	public JobAtt[] getJobs() {
		List<JobAtt> joblist=jobdao.getAllJob();
		JobAtt[]  ret=new JobAtt[joblist.size()];
		ret=joblist.toArray(new JobAtt[0]);
		return ret;
	}

	@Override
	public JobAtt[] getJobsWrapStatInvalid() {
		List<JobAtt> joblist=jobdao.getAllJobWrapStudy();
		JobAtt[]  ret=new JobAtt[joblist.size()];
		ret=joblist.toArray(new JobAtt[0]);
		return ret;
	}

	@Override
	public boolean addWrapper(int jobId, String type, String Wrapper,String vargen,String comment) {
		log.debug(Wrapper+vargen+comment);

		WrapAtt wrap=new WrapAtt();
		wrap.setJobid(jobId);
		wrap.setType(type);
		wrap.setWrapper(Wrapper);
		wrap.setComment(comment);
		wrap.setVersion(1);
		wrap.setVargen(vargen);
		return wrapdao.putWrap(wrap)>0;
	}

	@Override
	public String getWrapGen(int id) {
		WrapAtt tmp=wrapdao.getWrap(id);
		return tmp.getVargen();
	}

	@Override
	public boolean updateWrapGen(String wrapgen, int id) {
		return wrapdao.updateWrapGen(wrapgen, id);
	}




	@Override
	public boolean hasTask(int cid) {
		// TODO Auto-generated method stub
		boolean ret = false;
		if(getTask(cid,1)!=null){
			ret = true;
		}
		return ret;
	}
	@Override
	public Task getTask(int cid,int num) {
		// TODO Auto-generated method stub
		Task ret=null;
		//task，先从task表冲取status=1的
		boolean sysError=false;
		if(ret == null){ 
			int jid = taskdao.getJobIdFromTask(cid,"1");//from task_list
			log.debug("jid:"+jid+" cid:"+cid);
			if(jid>0){
				ret = taskdao.getTask(cid,jid,"1");
			}else
			{
				if(jid==-2)
					sysError=true;
			}
		}


		if(!sysError)
		{
			if(ret == null){
				ret = crawtask.takeTask(cid);
			}
		}

		return ret;
	}

	@Override
	public Task getTaskByJobId(int cid, int jid,String type,int num) {
		//供抓取学习使用
		Task ret=new Task();
		ret.setTaskId(1);
		if("1".equals(type)){
			//channel
			List<ChlAtt> chls=chldao.getChls(jid,num); //取得chls
			List wraps = wrapdao.getWrapsByJob(jid, "1");
			log.debug("size:"+wraps.size());
			if(wraps!=null && wraps.size()>0){
				WrapAtt wa=(WrapAtt)wraps.get(0);
				
				log.debug("chl wrap:"+wraps.size()+":"+wa.getId());
				StringBuffer  tmp=new StringBuffer ();
				for(ChlAtt ch:chls)
				{
					tmp.append(Util.strNotNull(ch.getUrl()));
					tmp.append("[#]");
					tmp.append(ch.getId());
					tmp.append("[##]");	
				}
				ret.setWrap_id(wa.getId());
				ret.setJob_id(jid);
				ret.setWrap_version(wa.getVersion());
				ret.setType(wa.getType());
				ret.setUrls(tmp.toString());
			}
		}else if("2".equals(type)){
			//column
			List<ColAtt> cols=coldao.getCols(jid,num);
			List wraps = wrapdao.getWrapsByJob(jid, "2");

			if(wraps!=null && wraps.size()>0){
				WrapAtt wa=(WrapAtt)wraps.get(0);
				log.debug("cols wrap:"+wraps.size()+":"+wa.getId());
				StringBuffer  tmp=new StringBuffer ();
				for(ColAtt col:cols)
				{
					tmp.append(Util.strNotNull(col.getUrl()));
					tmp.append("[#]");
					tmp.append(col.getId());
					tmp.append("[##]");	
				}
				ret.setWrap_id(wa.getId());
				ret.setJob_id(jid);
				ret.setWrap_version(wa.getVersion());
				ret.setType(wa.getType());
				ret.setUrls(tmp.toString());
			}
		}else if("3".equals(type)){
			//url
			List<UrlAtt> urlList=urldao.getUrls(jid,num);
			List wraps=wrapdao.getWrapsByJob(jid, "3");
			if(wraps!=null && wraps.size()>0){
				WrapAtt wa=(WrapAtt)wraps.get(0);
				log.debug("cols wrap:"+wraps.size()+":"+wa.getId());
				StringBuffer  tmp=new StringBuffer ();
				for(UrlAtt url:urlList)
				{
					tmp.append(Util.strNotNull(url.getUrl()));
					tmp.append("[#]");
					tmp.append(url.getId());
					tmp.append("[##]");	
				}
				ret.setWrap_id(wa.getId());
				ret.setJob_id(jid);
				ret.setWrap_version(wa.getVersion());
				ret.setType(wa.getType());
				ret.setUrls(tmp.toString());
			}
		}
		return ret;
	}

	@Override
	public boolean delJob(int id) {
		// TODO Auto-generated method stub
		return jobdao.del(id)==1;
	}

	@Override
	public boolean updateJobUrl(int id,String url) {
		// TODO Auto-generated method stub
		return jobdao.updateJobUrl(id,url)==1;

	}

	@Override
	public Task getWrapInvalidTaskByJobId(int cid, int jid, String type, int num) {
		// TODO Auto-generated method stub
		Task ret=null;
		/*
		 * 供测试使用
		 */

		

		if("1".equals(type)){
			//channel
				if(jid>0){
					ret = taskdao.getTaskChannelWrapInvalid(cid,jid,"1",num);
				}
				log.debug("2222222");
		}else if("2".equals(type)){
			//column
				if(jid>0){
					ret = taskdao.getTaskColumnWrapInvalid(cid,jid,"2",num);
				}
				log.debug("333333333");
		}else if("3".equals(type)){
			//url
				if(jid>0){
					ret = taskdao.getTaskUrlWrapInvalid(cid,jid,"3",num);
				}
				log.debug("4444");
		}

		return ret;

	}



	
	@Override
	public int[] getWrapId(int jid) {
		List<Integer> intList=wrapdao.getWrapId(jid);
		int [] ret=new int[intList.size()];
		int i=0;
		for(int id:intList)
		{
			ret[i]=id;
			i++;
		}
		return ret;
	}

	@Override
	public String getWraptype(int id) {
		return wrapdao.getWrapType(id);
	}

	@Override
	public int addCookie(int jobid, String logUrl, String logName,
			String logPass, String cookie,String cookType) {
		CookieAtt att=new CookieAtt();
		att.setCookieStr(cookie);
		att.setJobId(jobid);
		att.setLogName(logName);
		att.setLogPass(logPass);
		att.setLogUrl(logUrl);
		att.setCookieType(cookType);
		return cookieDao.AddCookie(att);
	}

	@Override
	public String getCookie(int jobid) {
		// TODO Auto-generated method stub
		CookieAtt att=cookieDao.getCookieByJobId(jobid);
		return att.getCookieStr();
	}

	@Override
	public boolean updateCookie(int jobid, String cookie) {
		cookieDao.SetCookieStr(jobid, cookie);
		return true;
	}

	@Override
	public LonginInfo getLogInfo(int jobid) {
		// TODO Auto-generated method stub
		CookieAtt att=cookieDao.getCookieByJobId(jobid);
		LonginInfo info=new LonginInfo();
		info.setLogName(att.getLogName());
		info.setLogPass(att.getLogPass());
		info.setLogUrl(att.getLogUrl());
		return info;
	}

	@Override
	public int[] getLogJobID() {
		List<Integer> joblist=cookieDao.getAllJobId();
		int [] ret=new int[joblist.size()];
		int i=0;
		for(Integer job:joblist)
		{
			ret[i]=job;
			i++;
		}
		return ret;
	}
	@Override
	public boolean deleteWrapStudy(int id)
	{
        wrapdao.deleteWrapStudy(id);
		return true;
	}

	@Override
	public String getStudyWrapper(int id) {
		WrapAtt tmp=wrapdao.getStudyWrap(id);
		return tmp.getWrapper();
	}

}
