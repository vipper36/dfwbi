package nyapc.crawler.dao;

public class ColAtt {
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
	
	
	public int getChlId() {
		return ChlId;
	}
	public void setChlId(int chlId) {
		ChlId = chlId;
	}
	public int getJobId() {
		return JobId;
	}
	public void setJobId(int jobId) {
		JobId = jobId;
	}

	private int JobId;
	private int Id;
	private String  Url;
	private String  Name;
	private int ChlId;
}
