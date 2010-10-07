package nyapc.crawler.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import nyapc.crawler.Util;
import nyapc.crawler.DbUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.CannotGetJdbcConnectionException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementCreator;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;

import org.springframework.jdbc.core.RowMapper;

import java.security.*;
import java.util.ArrayList;
import java.util.List;

import javax.sql.DataSource;

import org.springframework.jdbc.datasource.DataSourceUtils;

public class TaskDaoImp implements TaskDao {
	private static Log log = LogFactory.getLog(TaskDaoImp.class.getName());
	private JdbcTemplate jdbcTemplate;
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	@Override
	public int del(int id) {
		// TODO Auto-generated method stub
		try {
			//			final String idStr = ""+id;
			//			jdbcTemplate.update("delete from agent_info where agent_id=?",new PreparedStatementSetter(){
			//				public void setValues(PreparedStatement ps) throws SQLException{
			//					ps.setString(1,idStr);
			//				}
			//			});
			jdbcTemplate.update("delete from crawler_list where crawler_id=?", new Object[] { String.valueOf(id) });			
			return -1;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return 1;
		}		
	}

	@Override
	public TaskAtt get(int id) {
		// TODO Auto-generated method stub
		final TaskAtt theTaskAtt = new TaskAtt();  
		jdbcTemplate.query("select task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,task_status from task_list  where task_id = ?",  
				new Object[] {String.valueOf(id)},  
				new RowCallbackHandler() {  
			public void processRow(ResultSet rs) throws SQLException {  
				theTaskAtt.setTaskId(Util.str2int(rs.getString("task_id")));  
				theTaskAtt.setJobId(rs.getInt("job_id"));  
				theTaskAtt.setWrapperId(rs.getInt("wrapper_id"));
				theTaskAtt.setWrapperVersion(rs.getInt("wrapper_version"));
				theTaskAtt.setJobType(rs.getInt("job_type"));
				theTaskAtt.setCrawlerId(rs.getInt("crawler_id"));
				theTaskAtt.setIds(rs.getString("ids"));
				theTaskAtt.setCreateTime(rs.getString("create_time"));
				theTaskAtt.setTaskStatus(rs.getInt("task_status"));
			}  
		});
		if(theTaskAtt.getTaskId()>0){
			return theTaskAtt;	
		}else{
			return null;
		}

	}

	@Override
	public List list() {
		// TODO Auto-generated method stub
		String sql = "select task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,task_status from task_list";
		try {
			return jdbcTemplate.query(sql,new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final TaskAtt theTaskAtt = new TaskAtt();     
					theTaskAtt.setTaskId(Util.str2int(rs.getString("task_id")));  
					theTaskAtt.setJobId(rs.getInt("job_id"));  
					theTaskAtt.setWrapperId(rs.getInt("wrapper_id"));
					theTaskAtt.setWrapperVersion(rs.getInt("wrapper_version"));
					theTaskAtt.setJobType(rs.getInt("job_type"));
					theTaskAtt.setCrawlerId(rs.getInt("crawler_id"));
					theTaskAtt.setIds(rs.getString("ids"));
					theTaskAtt.setCreateTime(rs.getString("create_time"));
					theTaskAtt.setTaskStatus(rs.getInt("task_status"));
					return theTaskAtt;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}

	@Override
	public int save(TaskAtt taskAtt) {
		// TODO Auto-generated method stub
		try {
			final int jobId = taskAtt.getJobId();
			final int wrapperId = taskAtt.getWrapperId();
			final int wrapperVersion = taskAtt.getWrapperVersion();
			final int jobType = taskAtt.getJobType();
			final int crawlerId = taskAtt.getCrawlerId();
			final String ids = taskAtt.getIds();
			final String createTime = taskAtt.getCreateTime();
			final int taskStatus = taskAtt.getTaskStatus();
			if(taskAtt.getTaskId()==0){
				final int taskId=jdbcTemplate.queryForInt("select seq_task_list.nextval from dual");
				jdbcTemplate.update("insert into task_list(task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,create_time,task_status) values(?,?,?,?,?,?,?,?,sysdate,?)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setLong(i++,taskId);
						ps.setLong(i++,jobId);
						ps.setLong(i++,wrapperId);
						ps.setLong(i++,wrapperVersion);
						ps.setInt(i++,jobType);
						ps.setLong(i++,crawlerId);
						ps.setString(i++,ids);
						ps.setInt(i++,taskStatus);
					}
				});
				return crawlerId;
			}else{
				final int taskId = taskAtt.getTaskId();
				jdbcTemplate.update("update task_list set job_id=?,wrapper_id=?,wrapper_version=?,job_type=?,crawler_id=?,ids=?,task_status=? where task_id=?",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setLong(i++,jobId);
						ps.setLong(i++,wrapperId);
						ps.setLong(i++,wrapperVersion);
						ps.setInt(i++,jobType);
						ps.setLong(i++,crawlerId);
						ps.setString(i++,ids);
						ps.setInt(i++,taskStatus);
						ps.setLong(i++,taskId);						
					}
				});

				return crawlerId;
			}


		} catch (DataAccessException e) {
			log.debug(e.toString());
			return -1;
		}
	}

	@Override
	public Task getTaskChannel(int cid, int jid, String type, int num,String from_status,String to_status) {
		// TODO Auto-generated method stub
		String sql = "select w.wrap_version,w.wrap_id,w.wrap_type,c.chl_url,c.job_id,c.chl_id  from chl_list c, wrapper_list w where c.chl_stat=? and c.job_id=? and c.job_id=w.job_id and w.wrap_type=? and w.wrap_stat=?";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);

		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement pstmt0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,from_status);
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"1");
			ps.setString(i++,"0");
			rs = ps.executeQuery();
			boolean hasvalue = false;

			StringBuffer  tmp=new StringBuffer ();
			String ids = "";


			sql = "update chl_list set chl_stat=? where chl_id=?";
			pstmt0 = conn.prepareStatement(sql);			
			//PreparedStatementCreator psc = new MyPreparedStatementCreator(); 			
			while (rs.next()) {
				hasvalue = true;
				jdbcTemplate.update("update chl_list set chl_stat=? where chl_id=?",new Object[] { to_status,Util.strNotNull(rs.getString("chl_id"))});
				//				pstmt0.setString(1, to_status);
				//				pstmt0.setString(2, Util.strNotNull(rs.getString("chl_id")));
				//				pstmt0.executeUpdate();

				tmp.append(Util.strNotNull(rs.getString("chl_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("chl_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));	
				ids +=","+Util.strNotNull(rs.getString("chl_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				final int taskId=jdbcTemplate.queryForInt("select seq_task_list.nextval from dual");
				sql = "insert into task_list(task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,create_time,task_status) values(?,?,?,?,?,?,?,sysdate,?)";
				log.debug(sql);
				final String jobId = String.valueOf(rtn.getJob_id());
				final String wrapId = String.valueOf(rtn.getWrap_id());
				final String wrapVersion = String.valueOf(rtn.getWrap_version());
				final String jobType = String.valueOf(rtn.getType());
				final String f_cid = String.valueOf(cid);
				final String f_ids = ids;
				final String f_to_status = to_status;
				jdbcTemplate.update(sql,new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setLong(i++,taskId);
						ps.setString(i++,jobId);
						ps.setString(i++,wrapId);
						ps.setString(i++,wrapVersion);
						ps.setString(i++,jobType);
						ps.setString(i++,f_cid);
						ps.setString(i++,f_ids);
						ps.setString(i++,f_to_status);
					}
				});
				log.debug("ok");
				rtn.setUrls(tmp.toString());
				rtn.setTaskId(taskId);
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}
			if(pstmt0!=null){
				try {
					pstmt0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){
			}
		}
		return rtn;
	}

	@Override
	public Task getTaskColumn(int cid, int jid, String type, int num,String from_status,String to_status) {
		// TODO Auto-generated method stub
		String sql = "SELECT w.wrap_version, w.wrap_id, w.wrap_type, c.col_url, c.job_id, c.col_id FROM col_list c, wrapper_list w WHERE     c.col_stat = ?       AND c.job_id = ?       AND c.job_id = w.job_id      AND w.wrap_type = ?  and w.wrap_stat=?";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement pstmt0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,from_status);
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"2");
			ps.setString(i++, "0");
			rs = ps.executeQuery();
			boolean hasvalue = false;

			sql = "update col_list set col_stat=? where col_id=?";
			pstmt0 = conn.prepareStatement(sql);			

			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				jdbcTemplate.update("update col_list set col_stat=? where col_id=?",new Object[] { to_status,Util.strNotNull(rs.getString("col_id"))});
				//				pstmt0.setString(1, to_status);
				//				pstmt0.setString(2, Util.strNotNull(rs.getString("col_id")));				
				//				pstmt0.executeUpdate();
				tmp.append(Util.strNotNull(rs.getString("col_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("col_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));
				ids +=","+Util.strNotNull(rs.getString("col_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				final int taskId=jdbcTemplate.queryForInt("select seq_task_list.nextval from dual");
				sql = "insert into task_list(task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,create_time,task_status) values(?,?,?,?,?,?,?,sysdate,?)";
				log.debug(sql);
				final String jobId = String.valueOf(rtn.getJob_id());
				final String wrapId = String.valueOf(rtn.getWrap_id());
				final String wrapVersion = String.valueOf(rtn.getWrap_version());
				final String jobType = String.valueOf(rtn.getType());
				final String f_cid = String.valueOf(cid);
				final String f_ids = ids;
				final String f_to_status = to_status;
				jdbcTemplate.update(sql,new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setLong(i++,taskId);
						ps.setString(i++,jobId);
						ps.setString(i++,wrapId);
						ps.setString(i++,wrapVersion);
						ps.setString(i++,jobType);
						ps.setString(i++,f_cid);
						ps.setString(i++,f_ids);
						ps.setString(i++,f_to_status);
					}
				});
				log.debug("ok");
				rtn.setUrls(tmp.toString());
				rtn.setTaskId(taskId);
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(pstmt0!=null){
				try {
					pstmt0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;	
	}
	@Override
	public Task getTaskUrl(int cid, int jid, String type, int num,String from_status,String to_status) {
		// TODO Auto-generated method stub
		String sql = "SELECT w.wrap_version, w.wrap_id, w.wrap_type, u.url_url, u.job_id, u.url_id FROM url_list u, wrapper_list w WHERE     u.url_stat = ?       AND u.job_id = ?      AND u.job_id = w.job_id       AND w.wrap_type = ?  and w.wrap_stat=?";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement pstmt0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,from_status);
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"3");
			ps.setString(i++,"0");
			rs = ps.executeQuery();
			boolean hasvalue = false;
			sql = "update url_list set url_stat=? where url_id=?";
			pstmt0 = conn.prepareStatement(sql);			
			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				jdbcTemplate.update("update url_list set url_stat=? where url_id=?",new Object[] { to_status,Util.strNotNull(rs.getString("url_id"))});
				//				pstmt0.setString(1, to_status);
				//				pstmt0.setString(2, Util.strNotNull(rs.getString("url_id")));
				//				pstmt0.executeUpdate();

				tmp.append(Util.strNotNull(rs.getString("url_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("url_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));
				ids +=","+Util.strNotNull(rs.getString("url_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				final int taskId=jdbcTemplate.queryForInt("select seq_task_list.nextval from dual");
				sql = "insert into task_list(task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,create_time,task_status) values(?,?,?,?,?,?,?,sysdate,?)";
				log.debug(sql);
				final String jobId = String.valueOf(rtn.getJob_id());
				final String wrapId = String.valueOf(rtn.getWrap_id());
				final String wrapVersion = String.valueOf(rtn.getWrap_version());
				final String jobType = String.valueOf(rtn.getType());
				final String f_cid = String.valueOf(cid);
				final String f_ids = ids;
				final String f_to_status = to_status;
				jdbcTemplate.update(sql,new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setLong(i++,taskId);
						ps.setString(i++,jobId);
						ps.setString(i++,wrapId);
						ps.setString(i++,wrapVersion);
						ps.setString(i++,jobType);
						ps.setString(i++,f_cid);
						ps.setString(i++,f_ids);
						ps.setString(i++,f_to_status);
					}
				});

				//				sql = "insert into task_list(task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,create_time,task_status) " +
				//						"values('"+taskId+"','"+wrapId+"',?,?,?,?,?,sysdate,?)";

				log.debug("ok");
				rtn.setUrls(tmp.toString());
				rtn.setTaskId(taskId);
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(pstmt0!=null){
				try {
					pstmt0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;
	}

	@Override
	public int getJobIdFromTask(int cid,String status) {
		// TODO Auto-generated method stub
		try{
			String sql = "select min(job_id) job_id from task_list where crawler_id=? and task_status=?";
			int jobid=jdbcTemplate.queryForInt(sql,new Object[] {String.valueOf(cid),status});
			return jobid;
		}
		catch (CannotGetJdbcConnectionException e)
		{
			return -2;
		}
		catch (DataAccessException e) {
			return -1;
		}

	}

	@Override
	public int getJobId(String type,String status) {
		log.debug(type+":"+status);
		try{
			String sql = "";
			if(!"9".equals(status)){
				int jobid = 0;
				if("1".equals(type)){
					sql = "select job_id from chl_list where chl_id = (select min(chl_id) from chl_list where chl_stat=?)";
				}else if("2".equals(type)){
					sql = "select job_id from col_list where col_id = (select min(col_id) from col_list where col_stat=?)";
				}else if("3".equals(type)){
					sql = "select job_id from url_list where url_id = (select min(url_id) from url_list where url_stat=?)";
				}
				log.debug(sql);
				if(sql.length()>0)
				{
					jobid = jdbcTemplate.queryForInt(sql,new Object[]{status});
				}
				log.debug("job id:"+jobid);
				return jobid;
			}else{
				//取“错误”的
				int jobid = 0;
				if("1".equals(type)){
					sql = "select job_id from chl_list where chl_id = (select min(chl_id) from chl_list where chl_stat=?)";
					jobid = jdbcTemplate.queryForInt(sql,new Object[]{status});
				}else if("2".equals(type)){
					//sql = "select min(job_id) from (select job_id, count(*) c,sum(decode(col_stat,?,1,0))/count(*) p from (select c.* from col_list c ,wrapper_list w where c.job_id=w.job_id and w.wrap_type=? and  w.wrap_stat=?) where col_stat!=10 group by job_id) where c>=10 and p>=0.5";
					sql = "select job_id from (select sum(case when col_stat = 9 then 1 else 0 end) e, count(*) c,job_id,job_seed_type from (select c.col_id,c.col_name,c.col_url,c.col_stat,c.job_id,j.job_seed_type,rank() over(partition by c.job_id order by c.col_id desc) rank_ from col_list c,job_list j where j.job_id=c.job_id) l where rank_ <= 20 group by job_id,job_seed_type order by sum(case when col_stat = 9 then 1 else 0 end) desc) where (e > 5    and e / c >= 0.9 OR job_seed_type=2 and e>=1) and rownum < 2";
					log.debug(sql); 	
					jobid = jdbcTemplate.queryForInt(sql);
					//,new Object[]{status,"2","0"}
				}else if("3".equals(type)){
					//sql = "select min(job_id) from (select job_id, count(*) c,sum(decode(url_stat,?,1,0))/count(*) p from (select u.* from url_list u ,wrapper_list w where u.job_id=w.job_id and w.wrap_type=? and  w.wrap_stat=?) where url_stat!=10 group by job_id) where c>=10 and p>=0.5";
					sql = "select job_id from ( select sum(case when url_stat = 9 then 1 else 0 end) e,count(*) c,job_id from ( select url_id,url_name, url_url,url_stat, job_id,rank() over (partition by job_id order by url_id desc) rank_ from url_list ) l where rank_ <= 20 group by job_id order by sum(case when url_stat = 9 then 1 else 0 end) desc ) where e>5 and e/c>=0.9 and rownum<2";
					log.debug(sql);
					jobid = jdbcTemplate.queryForInt(sql);
					//,new Object[]{status,"3","0"}
				}
				return jobid;
			}

		} catch (DataAccessException e) {
			log.debug("no task data");
			return -1;
		}

	}


	@Override
	public int getJobIdByWrapInvalid(String type) {
		// TODO Auto-generated method stub
		try{
			String sql = "";
			sql = "select job_id from wrapper_list where wrap_type=? and wrap_stat=?";
			int jobid=jdbcTemplate.queryForInt(sql,new Object[]{type,"-1"});
			return jobid;
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return -1;
		}

	}

	@Override
	public boolean updateStatByTaskId(int id,String stat) {

		try {
			final String taskStatus=stat;
			final int taskId=id;
			jdbcTemplate.update("update task_list set task_status=? where task_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,taskStatus);
					ps.setInt(2,taskId);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}


	@Override
	public boolean updateRelationStatByTaskId(int id,String stat) {

		try {
			final String taskStatus=stat;
			TaskAtt theTaskAtt = get(id); 
			log.debug("dddd"+theTaskAtt);
			String sql = "";
			if("1".equals(String.valueOf(theTaskAtt.getJobType()))){	
				sql = "update chl_list set chl_stat=? where chl_id in ("+theTaskAtt.getIds()+")";
			}else if("2".equals(String.valueOf(theTaskAtt.getJobType()))){	
				sql = "update col_list set col_stat=? where col_id in ("+theTaskAtt.getIds()+")";
			}else if("3".equals(String.valueOf(theTaskAtt.getJobType()))){	
				sql = "update url_list set url_stat=? where url_id in ("+theTaskAtt.getIds()+")";
			}
			log.debug("sql:"+sql);
			if(!"".equals(sql)){
				jdbcTemplate.update(sql,
						new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setString(1,taskStatus);
					}
				});				
			}
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}	

	@Override
	public boolean updateStatByJobId(int id, String type,String stat) {

		try {
			final String taskStatus=stat;
			final String jobType=type;
			final int jobId=id;
			jdbcTemplate.update("update task_list set task_status=? where job_id=? and job_type=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,taskStatus);
					ps.setInt(2,jobId);
					ps.setString(3,jobType);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}

	}
	@Override
	public Task getTask(int cid, int jid, String type, String fromStatus) {
		// TODO Auto-generated method stub
		if("0".equals(type)){
			//如果是0，则不按照type来取
			return getTask(cid, jid, fromStatus);
		}

		Task theTask = new Task();

		Connection conn = null;
		PreparedStatement ps0 = null;
		PreparedStatement ps = null;		
		ResultSet rs = null;
		ResultSet rs0 = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			String sql = "select * from (select * from task_list where crawler_id=? and job_id=? and task_status=? and job_type=? order by job_type ) where rownum<2";
			ps0 = conn.prepareStatement(sql);
			int i =1;
			ps0.setString(i++, String.valueOf(cid));
			ps0.setString(i++, String.valueOf(jid));
			ps0.setString(i++, fromStatus);
			ps0.setString(i++, type);
			rs0 = ps0.executeQuery();
			if(rs0.next()){
				theTask.setWrap_id(Util.str2int(rs0.getString("wrapper_id")));
				theTask.setJob_id(Util.str2int(rs0.getString("job_id")));
				theTask.setWrap_version(Util.str2int(rs0.getString("wrapper_version")));
				theTask.setType(rs0.getString("job_type"));
				theTask.setUrls(rs0.getString("ids"));
				theTask.setTaskId(Util.str2int(rs0.getString("task_id")));				
			}else{
				return null;
			}


			if("1".equals(theTask.getType())){	
				sql = "select chl_id id,chl_url url from chl_list where chl_id in ("+theTask.getUrls()+")";
			}else if("2".equals(theTask.getType())){	
				sql = "select col_id id,col_url url from col_list where col_id in ("+theTask.getUrls()+")";
			}else if("3".equals(theTask.getType())){	
				sql = "select url_id id,url_url url from url_list where url_id in ("+theTask.getUrls()+")";
			}

			ps = conn.prepareStatement(sql);
			rs = ps.executeQuery();
			boolean hasvalue = false;

			StringBuffer  tmp=new StringBuffer ();
			while (rs.next()) {
				hasvalue = true;
				tmp.append(Util.strNotNull(rs.getString("url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("id")));
				tmp.append("[##]");				
			}

			if(!hasvalue){
				theTask = null;
			}else{
				theTask.setUrls(tmp.toString());
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			theTask = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}
			if(rs0!=null){
				try {
					rs0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				ps.close();
			}catch(Exception ee){

			}
			try{
				ps0.close();
			}catch(Exception ee){

			}
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}

		if(theTask.getTaskId()>0){
			return theTask;	
		}else{
			return null;
		}
	}	

	@Override
	public Task getTask(int cid, int jid, String fromStatus) {
		// TODO Auto-generated method stub
		Task theTask = new Task();


		Connection conn = null;
		PreparedStatement ps0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		String sql = "";
		ResultSet rs0 = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			sql = "select * from (select * from task_list where crawler_id=? and job_id=? and task_status=?  order by job_type ) where rownum<2";

			ps0 = conn.prepareStatement(sql);
			int i =1;
			ps0.setString(i++, String.valueOf(cid));
			ps0.setString(i++, String.valueOf(jid));
			ps0.setString(i++, fromStatus);
			rs0 = ps0.executeQuery();
			if(rs0.next()){
				theTask.setWrap_id(Util.str2int(rs0.getString("wrapper_id")));
				theTask.setJob_id(Util.str2int(rs0.getString("job_id")));
				theTask.setWrap_version(Util.str2int(rs0.getString("wrapper_version")));
				theTask.setType(rs0.getString("job_type"));
				theTask.setUrls(rs0.getString("ids"));
				theTask.setTaskId(Util.str2int(rs0.getString("task_id")));				
			}

			if(theTask!=null){
				if("1".equals(theTask.getType())){	
					sql = "select chl_id id,chl_url url from chl_list where chl_id in ("+theTask.getUrls()+")";
				}else if("2".equals(theTask.getType())){	
					sql = "select col_id id,col_url url from col_list where col_id in ("+theTask.getUrls()+")";
				}else if("3".equals(theTask.getType())){	
					sql = "select url_id id,url_url url from url_list where url_id in ("+theTask.getUrls()+")";
				}else{
					return null;
				}
			}


			ps = conn.prepareStatement(sql);
			rs = ps.executeQuery();
			boolean hasvalue = false;

			StringBuffer  tmp=new StringBuffer ();
			while (rs.next()) {

				hasvalue = true;
				tmp.append(Util.strNotNull(rs.getString("url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("id")));
				tmp.append("[##]");				
			}
			rs.close();

			if(!hasvalue){
				theTask = null;
			}else{
				theTask.setUrls(tmp.toString());
			}



		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			log.debug(sql);
			theTask = null;
		} finally {
			if(rs0!=null){
				try {
					rs0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			

			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				ps.close();
			}catch(Exception ee){

			}
			try{
				ps0.close();
			}catch(Exception ee){

			}
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}

		}

		if(theTask!=null&&theTask.getTaskId()>0){
			return theTask;	
		}else{
			return null;
		}
	}
	@Override
	public Task getTaskChannelWrapInvalid(int cid, int jid, String type, int num) {
		// TODO Auto-generated method stub
		String sql = "select w.wrap_version,w.wrap_id,w.wrap_type,c.chl_url,c.job_id,c.chl_id  from chl_list c, wrapper_list w where c.job_id=? and c.job_id=w.job_id and w.wrap_type=? order by c.create_time desc";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"1");
			rs = ps.executeQuery();
			boolean hasvalue = false;

			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				tmp.append(Util.strNotNull(rs.getString("chl_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("chl_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));	
				ids +=","+Util.strNotNull(rs.getString("chl_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				rtn.setUrls(tmp.toString());
				rtn.setTaskId(0); //置成0，实际上对wrap0没有用，
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;
	}
	@Override
	public Task getTaskColumnWrapInvalid(int cid, int jid, String type, int num) {
		// TODO Auto-generated method stub
		String sql = "SELECT w.wrap_version, w.wrap_id, w.wrap_type, c.col_url, c.job_id, c.col_id FROM col_list c, wrapper_list w WHERE     c.job_id = ?       AND c.job_id = w.job_id      AND w.wrap_type = ? order by c.create_time desc";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement  ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"2");
			rs = ps.executeQuery();
			boolean hasvalue = false;

			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				tmp.append(Util.strNotNull(rs.getString("col_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("col_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));
				ids +=","+Util.strNotNull(rs.getString("col_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				rtn.setUrls(tmp.toString());
				rtn.setTaskId(0);//置成0，实际上对wrap0没有用
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;	
	}
	@Override
	public Task getTaskUrlWrapInvalid(int cid, int jid, String type, int num) {
		// TODO Auto-generated method stub
		String sql = "SELECT w.wrap_version, w.wrap_id, w.wrap_type, u.url_url, u.job_id, u.url_id FROM url_list u, wrapper_list w WHERE u.job_id = ?      AND u.job_id = w.job_id       AND w.wrap_type = ? order by u.create_time desc";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"3");
			rs = ps.executeQuery();
			boolean hasvalue = false;

			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				tmp.append(Util.strNotNull(rs.getString("url_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("url_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));
				ids +=","+Util.strNotNull(rs.getString("url_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				rtn.setUrls(tmp.toString());
				rtn.setTaskId(0);//置成0，实际上对wrap0没有用
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;
	}



	@Override
	public Task getTaskQueueChannel(int jid, String type, int num,String from_status,String to_status) {
		// TODO Auto-generated method stub
		String sql = "select w.wrap_version,w.wrap_id,w.wrap_type,c.chl_url,c.job_id,c.chl_id  from chl_list c, wrapper_list w where c.chl_stat=? and c.job_id=? and c.job_id=w.job_id and w.wrap_type=? and w.wrap_stat=?";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement pstmt0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,from_status);
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"1");
			ps.setString(i++,"0");
			rs = ps.executeQuery();
			boolean hasvalue = false;
			sql = "update chl_list set chl_stat=? where chl_id=?";
			pstmt0 = conn.prepareStatement(sql);			
			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				jdbcTemplate.update("update chl_list set chl_stat=? where chl_id=?",new Object[] { to_status,Util.strNotNull(rs.getString("chl_id"))});
				//				pstmt0.setString(1, to_status);
				//				pstmt0.setString(2, Util.strNotNull(rs.getString("chl_id")));
				//			    pstmt0.executeUpdate();		

				tmp.append(Util.strNotNull(rs.getString("chl_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("chl_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));	
				ids +=","+Util.strNotNull(rs.getString("chl_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				rtn.setUrls(tmp.toString());
				rtn.setIds(ids);
				final int taskId = 0;
				rtn.setTaskId(taskId);
			}
			if(from_status=="9"){
				jdbcTemplate.update("update chl_list set chl_stat=? where chl_id in (select c.chl_id  from chl_list c, wrapper_list w where c.chl_stat=? and c.job_id=? and c.job_id=w.job_id and w.wrap_type=? and w.wrap_stat=?)",
						new Object[] { "10",from_status,String.valueOf(jid),"1","0"}
				);
			}			


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(pstmt0!=null){
				try {
					pstmt0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;
	}

	@Override
	public Task getTaskQueueColumn(int jid, String type, int num,String from_status,String to_status) {
		// TODO Auto-generated method stub
		String sql = "SELECT w.wrap_version, w.wrap_id, w.wrap_type, c.col_url, c.job_id, c.col_id FROM col_list c, wrapper_list w WHERE     c.col_stat = ?       AND c.job_id = ?       AND c.job_id = w.job_id      AND w.wrap_type = ?  and w.wrap_stat=?";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement pstmt0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,from_status);
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"2");
			ps.setString(i++, "0");
			rs = ps.executeQuery();
			boolean hasvalue = false;
			sql = "update col_list set col_stat=? where col_id=?";
			pstmt0 = conn.prepareStatement(sql);				
			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				jdbcTemplate.update("update col_list set col_stat=? where col_id=?",new Object[] { to_status,Util.strNotNull(rs.getString("col_id"))});
				//				pstmt0.setString(1, to_status);
				//				pstmt0.setString(2, Util.strNotNull(rs.getString("col_id")));
				//			    pstmt0.executeUpdate();					
				tmp.append(Util.strNotNull(rs.getString("col_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("col_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));
				ids +=","+Util.strNotNull(rs.getString("col_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				rtn.setUrls(tmp.toString());
				rtn.setIds(ids);
				final int taskId = 0;
				rtn.setTaskId(taskId);
			}

			if(from_status=="9"){
				jdbcTemplate.update("update col_list set col_stat=? where col_stat = ? AND job_id = ? and create_time>sysdate-1",
						new Object[] { "10",from_status,String.valueOf(jid)}	
				);
			}


		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(pstmt0!=null){
				try {
					pstmt0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;	
	}
	@Override
	public Task getTaskQueueUrl(int jid, String type, int num,String from_status,String to_status) {
		// TODO Auto-generated method stub
		String sql = "SELECT w.wrap_version, w.wrap_id, w.wrap_type, u.url_url, u.job_id, u.url_id FROM url_list u, wrapper_list w WHERE     u.url_stat = ?       AND u.job_id = ?      AND u.job_id = w.job_id       AND w.wrap_type = ?  and w.wrap_stat=?";
		sql = "select * from ("+sql+") where rownum<="+num;
		log.debug(sql);
		Connection conn = null;
		Task rtn = new Task();
		PreparedStatement pstmt0 = null;
		PreparedStatement ps = null;
		ResultSet rs = null;
		try {
			//conn = dataSource.getConnection();
			conn = DataSourceUtils.getConnection(this.jdbcTemplate.getDataSource());
			ps = conn.prepareStatement(sql);
			int i = 1;
			ps.setString(i++,from_status);
			ps.setString(i++,String.valueOf(jid));
			ps.setString(i++,"3");
			ps.setString(i++,"0");
			rs = ps.executeQuery();
			boolean hasvalue = false;
			sql = "update url_list set url_stat=? where url_id=?";
			pstmt0 = conn.prepareStatement(sql);				
			StringBuffer  tmp=new StringBuffer ();
			String ids = "";
			while (rs.next()) {
				hasvalue = true;
				jdbcTemplate.update("update url_list set url_stat=? where url_id=?",new Object[] { to_status,Util.strNotNull(rs.getString("url_id"))});
				//				pstmt0.setString(1, to_status);
				//				pstmt0.setString(2, Util.strNotNull(rs.getString("url_id")));
				//			    pstmt0.executeUpdate();					
				tmp.append(Util.strNotNull(rs.getString("url_url")));
				tmp.append("[#]");
				tmp.append(Util.strNotNull(rs.getString("url_id")));
				tmp.append("[##]");				
				rtn.setWrap_id(Util.str2int(rs.getString("wrap_id")));
				rtn.setJob_id(Util.str2int(rs.getString("job_id")));
				rtn.setWrap_version(Util.str2int(rs.getString("wrap_version")));
				rtn.setType(Util.strNotNull(rs.getString("wrap_type")));
				ids +=","+Util.strNotNull(rs.getString("url_id"));
			}

			if(ids.length()>0){
				ids=ids.substring(1);
			}
			if(!hasvalue){
				rtn = null;
			}else{
				rtn.setUrls(tmp.toString());
				rtn.setIds(ids);
				final int taskId = 0;
				rtn.setTaskId(taskId);
			}

			if(from_status=="9"){
				jdbcTemplate.update("update url_list set url_stat=? where url_stat = ? AND job_id = ? and create_time>sysdate-1",
						new Object[] { "10",from_status,String.valueOf(jid)}
				);
			}			



		} catch (Exception e) {
			// TODO: handle exception
			log.debug(e.toString());
			rtn = null;
		} finally {
			if(rs!=null){
				try {
					rs.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(ps!=null){
				try {
					ps.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			if(pstmt0!=null){
				try {
					pstmt0.close();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					log.debug(e.toString());
				}
			}			
			try{
				//conn.close();
				DataSourceUtils.releaseConnection(conn, this.jdbcTemplate.getDataSource());
			}catch(Exception ee){

			}
		}
		return rtn;
	}


	@Override
	public Task takeTaskQueue(Task task,int cid,String to_status) {
		Task rtn = task;
		// TODO Auto-generated method stub
		try{
			final int taskId=jdbcTemplate.queryForInt("select seq_task_list.nextval from dual");
			String sql = "insert into task_list(task_id,job_id,wrapper_id,wrapper_version,job_type,crawler_id,ids,create_time,task_status)" +
			" values(?,?,?,?,?,?,?,sysdate,?)";
			log.debug(sql);
			final String jobId = String.valueOf(rtn.getJob_id());
			final String wrapId = String.valueOf(rtn.getWrap_id());
			final String wrapVersion = String.valueOf(rtn.getWrap_version());
			final String jobType = String.valueOf(rtn.getType());
			final String f_cid = String.valueOf(cid);
			final String f_ids = rtn.getIds();
			final String f_to_status = to_status;
			jdbcTemplate.update(sql,new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					int i = 1;
					ps.setLong(i++,taskId);
					ps.setString(i++,jobId);
					ps.setString(i++,wrapId);
					ps.setString(i++,wrapVersion);
					ps.setString(i++,jobType);
					ps.setString(i++,f_cid);
					ps.setString(i++,f_ids);
					ps.setString(i++,f_to_status);
				}
			});

			if("1".equals(rtn.getType())){	
				jdbcTemplate.update("update chl_list set chl_stat=? where chl_id in ("+rtn.getIds()+")",new Object[] { to_status});
			}else if("2".equals(rtn.getType())){	
				jdbcTemplate.update("update col_list set col_stat=? where col_id in ("+rtn.getIds()+")",new Object[] { to_status});
			}else if("3".equals(rtn.getType())){	
				jdbcTemplate.update("update url_list set url_stat=? where url_id in ("+rtn.getIds()+")",new Object[] { to_status});
			}
			rtn.setTaskId(taskId);
		}catch(Exception e){				
			log.debug(e.toString());
		}
		return rtn;
	}
	@Override
	public void restartTomcat() {
		// TODO Auto-generated method stub
		log.debug("ddddddddddddddddddddddddddddd   111");
		try {
			log.debug("ddddddddddddddddddddddddddddd 222");
			jdbcTemplate.update("update url_list set url_stat = ? where url_stat=?", new Object[] { "0","-2" });
			log.debug("ddddddddddddddddddddddddddddd 44");
			jdbcTemplate.update("update url_list set url_stat = ? where url_stat=?", new Object[] { "9","-3" });
			jdbcTemplate.update("update url_list set url_stat = ? where url_stat=?", new Object[] { "9","10" });
			jdbcTemplate.update("update col_list set col_stat = ? where col_stat=?", new Object[] { "0","-2" });			
			jdbcTemplate.update("update col_list set col_stat = ? where col_stat=?", new Object[] { "9","-3" });
			jdbcTemplate.update("update col_list set col_stat = ? where col_stat=?", new Object[] { "9","10" });
			jdbcTemplate.update("update chl_list set chl_stat = ? where chl_stat=?", new Object[] { "0","-2" });			
			jdbcTemplate.update("update chl_list set chl_stat = ? where chl_stat=?", new Object[] { "9","-3" });			
			log.debug("ddddddddddddddddddddddddddddd 333");
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());

		}		
	}


}