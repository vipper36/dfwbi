package nyapc.crawler;

import nyapc.crawler.dao.JobAtt;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import nyapc.crawler.dao.AeSimpleSHA1;
import nyapc.crawler.dao.ChlDao;
import nyapc.crawler.dao.ColAtt;
import nyapc.crawler.dao.ColDao;
import nyapc.crawler.dao.IdxDao;
import nyapc.crawler.dao.JobDao;
import nyapc.crawler.dao.TaskDao;
import nyapc.crawler.dao.UrlAtt;
import nyapc.crawler.dao.UrlDao;
import nyapc.crawler.dao.IdxAtt;
public class ResultHandler {
	public ChlDao getChldao() {
		return chldao;
	}
	public void setChldao(ChlDao chldao) {
		this.chldao = chldao;
	}
	public ColDao getColdao() {
		return coldao;
	}
	public void setColdao(ColDao coldao) {
		this.coldao = coldao;
	}
	public UrlDao getUrldao() {
		return urldao;
	}
	public void setUrldao(UrlDao urldao) {
		this.urldao = urldao;
	}
	public JobDao getJobdao() {
		return jobdao;
	}
	public void setJobdao(JobDao jobdao) {
		this.jobdao = jobdao;
	}
	public IdxDao getIdxdao() {
		return idxdao;
	}
	public void setIdxdao(IdxDao idxdao) {
		this.idxdao = idxdao;
	}
	public TaskDao getTaskdao() {
		return taskdao;
	}
	public void setTaskdao(TaskDao taskdao) {
		this.taskdao = taskdao;
	}
	public void handleChl(Element docEle,int taskId)
	{
		try {
			//频道  
			NodeList resultlist=docEle.getElementsByTagName("Result");
			if(resultlist.getLength()>0){
				Map<Integer,Integer> uidMap=new HashMap<Integer,Integer>();
				//有数据
				for(int iresult=0;iresult<resultlist.getLength();iresult++)
				{
					Element colresult=(Element) resultlist.item(iresult);
					String url=colresult.getAttribute("url");
					String code=colresult.getAttribute("code");
					String parurl=Util.GetUrlDir(url);
					String siteurl=Util.GetUrlSite(url);
					String cmdurl=Util.GetUrlCmd(url);
					int chl_id=Integer.parseInt(colresult.getAttribute("uid"));
					int job_id=chldao.getJobId(chl_id);
					String error=colresult.getAttribute("error");
					if(error!=null&&error.length()>0)
					{
						//Document load error
						if(error.equals("5"))
						{
							chldao.updateStat(chl_id, "9");
						}else
						{
							chldao.updateFailCount(chl_id);
							if(chldao.getFailCount(chl_id)>3){
								//错误超过3次，才更新成2
								chldao.resetFailCount(chl_id);
								chldao.updateStat(chl_id, "2");
							}else{
								chldao.updateStat(chl_id, "0");
							}
						}
					}else
					{
						int colCount=0;
						NodeList nl=colresult.getElementsByTagName("Columns");
						if(nl.getLength()>0)
						{ 
							Element cols=(Element) nl.item(0);

							NodeList collist=cols.getElementsByTagName("Column");
							if(collist.getLength()>0)
							{
								//set 2
								for(int i=0;i<collist.getLength();i++)
								{
									Element col=(Element) collist.item(i);
									String colName= Util.strNotNull(col.getAttribute("name"));
									String colUrl= Util.strNotNull(col.getAttribute("url"));
									//filter the url:delet '#',"javascript",
									colUrl = Util.BuildUrl(colUrl, parurl, siteurl,cmdurl,code);
									
									colCount++;
									if(colUrl.length()==0)
										continue;
									ColAtt cola=new ColAtt();
									cola.setChlId(chl_id);
									cola.setJobId(job_id);
									cola.setName(colName);//应该可以为null,数据库已经处理
									cola.setUrl(Util.strNotNull(colUrl));//不能为null

									String hash=AeSimpleSHA1.SHA1(cola.getUrl());
									int colid=coldao.GetId(hash);
//									log.debug("col id:"+colid+" url:"+cola.getUrl()+" hash:"+hash);
									
									if(colid<=0 && !"".equals(cola.getUrl())){
										log.debug("insert column");
										colid=coldao.puttCol(cola);
										if(col.getAttribute("name").equals(col.getAttribute("url")))
										{
											coldao.updateStatByJobId(job_id,"2");
										}
									}
									else{
										//栏目已经存在，更新状态为col_stat=0 
										if(!col.getAttribute("name").equals(col.getAttribute("url"))
												&&jobdao.needUpdate(job_id))
										{
											log.debug("update col stat!");
											coldao.updateFinStat(colid, "0");
										}
									}

									NodeList sublist=col.getElementsByTagName("SubItem");
									for(int j=0;j<sublist.getLength();j++)
									{
										Element subitem=(Element) sublist.item(j);
										String urlUrl= Util.strNotNull(subitem.getAttribute("url"));
										//filter the url:delet '#',"javascript",
										urlUrl = Util.BuildUrl(urlUrl, parurl, siteurl,cmdurl,code);
										if(urlUrl.length()==0)
											continue;


										String urlName=subitem.getTextContent();
										UrlAtt ua=new UrlAtt();
										ua.setJobId(job_id);
										ua.setName(urlName);
										ua.setUrl(Util.strNotNull(urlUrl));
										if(colid>0)
										{
											String uhash=AeSimpleSHA1.SHA1(ua.getUrl());
											int urlid=urldao.GetId(uhash);
											if(urlid>0){
												urldao.AddCol(urlid, colid);
											}else
											{
												if(!"".equals(ua.getUrl())){
													urlid=urldao.puttUrl(ua);
												}
												if(urlid>0){
													urldao.AddCol(urlid, colid);
												}	
											}
										}
									}
								}
							}
						}
						log.debug("col count:"+colCount);
						Integer tmpCount=uidMap.get(chl_id);
						if(tmpCount!=null)
						{
							tmpCount+=colCount;
							uidMap.put(chl_id, tmpCount);
						}
						else
						{
							uidMap.put(chl_id, colCount);
						}
					}
				}
				for(Map.Entry<Integer,Integer> ent:uidMap.entrySet())
				{
					log.debug("uid:"+ent.getKey());
					log.debug("count:"+ent.getValue());
					if(ent.getValue()>0)
					{
						chldao.updateStat(ent.getKey(), "2");
						chldao.resetFailCount(ent.getKey());
					}else{
						//set 9
						chldao.updateFailCount(ent.getKey());
						if(chldao.getFailCount(ent.getKey())>3){
							//错误超过3次，才更新成失败9
							chldao.resetFailCount(ent.getKey());
							chldao.updateStat(ent.getKey(), "9");
						}else{
							chldao.updateStat(ent.getKey(), "0");
						}

					}
				}
				taskdao.updateStatByTaskId(taskId, "2");
			}else{
				//无数据
				taskdao.updateStatByTaskId(taskId, "9");
				taskdao.updateRelationStatByTaskId(taskId, "9");
			}
		}
		catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		} 
		catch (Exception e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		} 
	}
	public void handleCol(Element docEle,int taskId)
	{
		try {
			NodeList resultlist=docEle.getElementsByTagName("Result");
			if(resultlist.getLength()>0)
			{
				Map<Integer,Integer> uidMap=new HashMap<Integer,Integer>();
				//有数据
				for(int iresult=0;iresult<resultlist.getLength();iresult++)
				{
					Element colresult=(Element) resultlist.item(iresult);
					String url=colresult.getAttribute("url");
					String code=colresult.getAttribute("code");
					String parurl=Util.GetUrlDir(url);
					String siteurl=Util.GetUrlSite(url);
					String cmdurl=Util.GetUrlCmd(url);
					int col_id=Integer.parseInt(colresult.getAttribute("uid"));
					log.debug("col id:"+col_id);
					int job_id=coldao.getJobId(col_id);
					log.debug("job id:"+job_id);
					String error=colresult.getAttribute("error");
					if(error!=null&&error.length()>0)
					{
						//Document load error
						if(error.equals("5"))
						{
							coldao.updateStat(col_id, "9");
						}else
						{
							//Document load error
							coldao.updateFailCount(col_id);
							if(coldao.getFailCount(col_id)>3){
								//错误超过3次，才更新成2
								coldao.resetFailCount(col_id);
								coldao.updateStat(col_id, "2");	
							}else{
								coldao.updateStat(col_id, "0");
							}
						}
					}
					else
					{
						//column begin
						int itemCount=0;
						NodeList nl=colresult.getElementsByTagName("Column");
						if(nl.getLength()>0){
							Element col=(Element) nl.item(0);
							//handle the column alias
							String alias=col.getAttribute("alias");
							if(alias != null && alias.length() > 0)
							{
								coldao.SetAlias(col_id, alias);
							}
							//update col name
							String colName = col.getAttribute("name");
							if(colName != null && colName.length() > 0)
							{
								coldao.updateName(col_id, colName);
							}
							NodeList sublist=col.getElementsByTagName("SubItem");
							if(sublist.getLength()>0){
								//set 2
								for(int j=0;j<sublist.getLength();j++)
								{
									Element subitem=(Element) sublist.item(j);
									String urlUrl= Util.strNotNull(subitem.getAttribute("url"));
									//filter the url:delet '#',"javascript",

									urlUrl = Util.BuildUrl(urlUrl, parurl, siteurl,cmdurl,code);
									if(urlUrl.length()==0)
										continue;
									itemCount++;
									String urlName=subitem.getTextContent();
									UrlAtt ua=new UrlAtt();
									ua.setJobId(job_id);
									ua.setName(urlName);
									ua.setUrl(Util.strNotNull(urlUrl));

									if(col_id>0)
									{
										String hash=AeSimpleSHA1.SHA1(ua.getUrl());
										int urlid=urldao.GetId(hash);
										if(urlid>0){
											log.debug("add url col:"+urlid+":"+col_id);
											urldao.AddCol(urlid, col_id);
										}else{
											if(!"".equals(ua.getUrl())){
												urlid=urldao.puttUrl(ua);
											}
											if(urlid>0){
												urldao.AddCol(urlid, col_id);
											}	
										}
									}
								}
							}
							//handle next url
							NodeList nextColList=col.getElementsByTagName("NextCol");
							if(nextColList.getLength() > 0)
							{
								Element nextCol = (Element)nextColList.item(0);
								
								String colUrl = nextCol.getAttribute("nextUrl");
								colUrl = Util.BuildUrl(colUrl, parurl, siteurl,cmdurl,code);
								if(colUrl.length()>0)
								{
									ColAtt cola=new ColAtt();
									cola.setChlId(-1);
									cola.setJobId(job_id);
									cola.setName(null);//应该可以为null,数据库已经处理
									cola.setUrl(Util.strNotNull(colUrl));//不能为null
	
									String hash=AeSimpleSHA1.SHA1(cola.getUrl());
									int colid=coldao.GetId(hash);
	
									if(colid<=0 && !"".equals(cola.getUrl())){
										colid=coldao.puttCol(cola);
									}else{
										//栏目已经存在，更新状态为col_stat=0 
										if(jobdao.needUpdate(job_id))
										{
											log.debug("update col stat!");
											coldao.updateFinStat(colid, "0");
										}
									}
								}
							}
							
						}
						Integer tmpCount=uidMap.get(col_id);
						if(tmpCount!=null)
						{
							tmpCount+=itemCount;
							uidMap.put(col_id, tmpCount);
						}
						else
						{
							uidMap.put(col_id, itemCount);
						}
					}
					//column end
				}
				for(Map.Entry<Integer,Integer> ent:uidMap.entrySet())
				{
					log.debug("uid:"+ent.getKey());
					log.debug("count:"+ent.getValue());
					if(ent.getValue()>0)
					{
						coldao.updateStat(ent.getKey(), "2");
						coldao.resetFailCount(ent.getKey());
					}else{
						//set 9
						coldao.updateFailCount(ent.getKey());
						if(coldao.getFailCount(ent.getKey())>3){
							//错误超过3次，才更新成失败9
							coldao.resetFailCount(ent.getKey());
							coldao.updateStat(ent.getKey(), "9");
						}else{
							coldao.updateStat(ent.getKey(), "0");
						}

					}
				}
				taskdao.updateStatByTaskId(taskId, "2");
			}else{
				//无数据
				taskdao.updateStatByTaskId(taskId, "9");	
				taskdao.updateRelationStatByTaskId(taskId, "9");
			}
		}
		catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		} 
	}
	public void handleUrl(Element docEle,int taskId)
	{
		NodeList resultlist=docEle.getElementsByTagName("Result");
		if(resultlist.getLength()>0){
			Map<Integer,Integer> uidMap=new HashMap<Integer,Integer>();
			//有数据
			ArrayList<IdxAtt> idxList = new ArrayList<IdxAtt>(); 
			for(int iresult=0;iresult<resultlist.getLength();iresult++)
			{
				Element colresult=(Element) resultlist.item(iresult);
				String url=colresult.getAttribute("url");
				int url_id=Integer.parseInt(colresult.getAttribute("uid"));
				UrlAtt att=urldao.getUrl(url_id);
				String error=colresult.getAttribute("error");
				if(error!=null&&error.length()>0)
				{
					//Document load error
					if(error.equals("5"))
					{
						urldao.updateStat(url_id, "9");
					}else
					{
						//Document load error
						urldao.updateFailCount(url_id);
						if(urldao.getFailCount(url_id)>3){
							//错误超过3次，才更新成失败9
							urldao.resetFailCount(url_id);
							urldao.updateStat(url_id, "2");	
						}else{
							urldao.updateStat(url_id, "0");
						}
					}
				}else
				{
					//column begin
					int itemCount=0;

					NodeList nl=colresult.getElementsByTagName("Content");
					if(nl!=null && nl.getLength()>0)
					{
						//有ContentList
						IdxAtt ia=new IdxAtt();
						Element content=(Element) nl.item(0);
						ia.addAtts("#DREREFERENCE ", url);
						ia.setDbTitle(att.getName());
						JobAtt ja=jobdao.getJob(att.getJobId());
						List<Integer> colList=urldao.getColIds(url_id);
						NodeList contatts=content.getElementsByTagName("ContAtts");
						if(contatts!=null && contatts.getLength()>0)
						{

							Element contatt=(Element) nl.item(0);
							NodeList atts=contatt.getElementsByTagName("Att");
							for(int j=0;j<atts.getLength();j++)
							{
								Element attele=(Element)atts.item(j);
								String attName=attele.getAttribute("name");
								String attValue=attele.getTextContent();
								try{
									ia.addAtts(attName, attValue);
								}catch(Exception e){
									log.debug(e.toString());
								}
							}
						}
						
						//Add search news handle here------
						//if column number is bigger than 10, do nothing!!
						log.debug("col size:"+colList.size());
						if(colList!=null&&colList.size()<10)
						{
							for(Integer colId :colList)
							{
								//add column tag
								ColAtt colAtt = coldao.get(colId);
								if(colAtt!=null)
								{
									JobAtt jobAtt=jobdao.getJob(colAtt.getJobId());
									if("NEWS".equals(jobAtt.getDredb()))
									{
										ia.addAtts("#DREFIELD CHANNELNAME=", colAtt.getName());
									}else if("BLOG".equals(jobAtt.getDredb()))
									{
										if("2".equals(jobAtt.getCategory()))
										{
											ia.addAtts("#DREFIELD BLOGALIAS=", colAtt.getName());
											ia.addAtts("#DREFIELD BLOGNAME=", coldao.getAlias(colId));
										}
										else
											ia.addAtts("#DREFIELD BLOGCHANNEL=", colAtt.getName());
									}
								}
							}
						}

						ia.addAtts("#DREFIELD JOBNAME=", ja.getName());

						NodeList contentele=content.getElementsByTagName("Content");
						if(contentele!=null && contentele.getLength()>0)
						{
							//有内容的tag
							Element conele=(Element)contentele.item(0);
							String conStr = Util.strNotNull(conele.getTextContent());

							//判断长度
							if(conStr.length()>0){
								itemCount++;
								ia.setContent(conStr);
								idxList.add(ia);
							}
						}
					}
					Integer tmpCount=uidMap.get(url_id);
					if(tmpCount!=null)
					{
						tmpCount+=itemCount;
						uidMap.put(url_id, tmpCount);
					}
					else
						uidMap.put(url_id, itemCount);
				}
			}
			log.debug("send idx");
			try{
				idxdao.send(idxList);//索引内容POST
			}catch(Exception e){
				log.debug(e.toString());
			}
			for(Map.Entry<Integer,Integer> ent:uidMap.entrySet())
			{
				log.debug("uid:"+ent.getKey());
				log.debug("count:"+ent.getValue());
				if(ent.getValue()>0)
				{
					urldao.updateStat(ent.getKey(), "2");
					urldao.resetFailCount(ent.getKey());
				}else{
					//set 9
					urldao.updateFailCount(ent.getKey());
					if(urldao.getFailCount(ent.getKey())>3){
						//错误超过3次，才更新成失败9
						urldao.resetFailCount(ent.getKey());
						urldao.updateStat(ent.getKey(), "9");
					}else{
						urldao.updateStat(ent.getKey(), "0");
					}

				}
			}
			taskdao.updateStatByTaskId(taskId, "2");
		}else{
			//无数据
			log.debug("9999 begin");
			taskdao.updateStatByTaskId(taskId, "9");
			taskdao.updateRelationStatByTaskId(taskId, "9");
			log.debug("9999 end");
		}
	}
	private  ChlDao chldao;
	private  ColDao coldao;
	private  UrlDao urldao;
	private  JobDao jobdao;
	private  IdxDao idxdao;
	private TaskDao taskdao;

	private static Log log = LogFactory.getLog(CrawlerCtrlImpl.class.getName());
}
