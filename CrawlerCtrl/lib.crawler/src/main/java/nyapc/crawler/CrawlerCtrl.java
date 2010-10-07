package nyapc.crawler;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;
import nyapc.crawler.dao.JobAtt;
import nyapc.crawler.dao.LonginInfo;
import nyapc.crawler.dao.Task;

@WebService
@SOAPBinding(style = Style.RPC)
public class CrawlerCtrl {
	public Task getTask(int cid,int num){return null;}//clientid
	public Task getTaskByJobId(int cid,int jid,String type,int num){return null;}//clientid,jobid



	public boolean putResult(String res,int cid){return false;}
	public int getStat(int cid){return -3;}
	public int addJob(String name,String url,String type,String category,String dredb,String comment){return -3;}
	public boolean delJob(int id){return false;}

	public int [] getJobID(){return null;}
	public JobAtt getJob(int id){return null;}
	public JobAtt[] getJobs(){return null;}
	public JobAtt[] getJobsWrapStatInvalid(){return null;}
	public boolean updateJob(int id){return false;}
	public boolean updateJobUrl(int id,String url){return false;}
	public boolean hasTask(int cid){return false;}


	//operate cookie
	public int addCookie(int jobid,String logUrl,String logName,String logPass,String cookie,String cookType){return -3;}
	public boolean updateCookie(int jobid,String cookie){return false;}
	public String getCookie(int jobid){return null;}
	public LonginInfo getLogInfo(int jobid){return null;}
	public int [] getLogJobID(){return null;}

        ///////wrapper
        public int getVersion(int id){return -3;}
	public String getWrapper(int id){return null;}
	public String getWrapGen(int id){return null;}
	public boolean updateWrapper(String wrap,int id,int taskid){return false;}
	public boolean updateWrapperCheckOk(String wrap, int wrapId){return false;}
	public boolean updateWrapGen(String wrapgen,int id){return false;}//保留接口，暂时保留
	public Task getWrapTask(int cid,int num){return null;}

	public int[] getWrapId(int jid){return null;}
	public String getWraptype(int id){return null;}
	public Task getWrapInvalidTask(int cid,int num){return null;}
	public Task getWrapInvalidTaskByJobId(int cid,int jid,String type,int num){return null;}//clientid,jobid
	public boolean addWrapper(int jobId,String type,String wrapper,String vargen,String comment){return false;}
	public boolean deleteWrapStudy(int id){return false;}
	public String getStudyWrapper(int id){return null;}

}
