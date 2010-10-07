package nyapc.crawler.dao;


public class UrlAtt {
	public int getId() {
		return Id;
	}
	public void setId(int id) {
		Id = id;
	}
	public String getUrl() {
		return Url;
	}
	public void setUrl(String url) {
		Url = url;
	}
	public String getName() {
		return Name;
	}
	public void setName(String name) {
		Name = name;
	}
	public int getJobId() {
		return jobId;
	}
	public void setJobId(int jobId) {
		this.jobId = jobId;
	}
	private int Id;
	private String  Url;
	private String  Name;
	
	private int jobId;
}
