package nyapc.crawler.dao;


public class Task  {
	
	public int getWrap_id() {
		return wrap_id;
	}
	public void setWrap_id(int wrapId) {
		wrap_id = wrapId;
	}
	public String getUrls() {
		return urls;
	}
	public void setUrls(String urls) {
		this.urls = urls;
	}
	public int getJob_id() {
		return job_id;
	}
	public void setJob_id(int jobId) {
		job_id = jobId;
	}

	public String getType() {
		return type;
	}
	public void setType(String type) {
		this.type = type;
	}
	public int getWrap_version() {
		return wrap_version;
	}
	public void setWrap_version(int wrapVersion) {
		wrap_version = wrapVersion;
	}
	private int job_id;
	private String type;
	private int wrap_id;
	private int wrap_version;
	private String urls;
	private int taskId;
	private String ids;
	public int getTaskId() {
		return taskId;
	}
	public void setTaskId(int taskId) {
		this.taskId = taskId;
	}
	public String getIds() {
		return ids;
	}
	
	public void setIds(String ids) {
		this.ids = ids;
	}
}
