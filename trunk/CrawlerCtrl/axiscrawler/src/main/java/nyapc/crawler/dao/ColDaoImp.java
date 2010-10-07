package nyapc.crawler.dao;

import java.security.NoSuchAlgorithmException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;
import org.springframework.jdbc.core.RowMapper;



public class ColDaoImp implements ColDao {
	private static Log log = LogFactory.getLog(ColDaoImp.class.getName());	
	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
	private Map<Integer,Calendar> updateFlag=new HashMap<Integer,Calendar>();
	private JdbcTemplate jdbcTemplate;
	@Override
	public boolean SetAlias(int id, String alias) {
		try {

			final String strAl=alias;
			final int colid=id;
			//String sql="insert into col_alias(col_id,col_alias,create_time) values(?,?,sysdate)";
			String sql="update col_list set col_alias=? where col_id = ?";
			jdbcTemplate.update(sql,new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,strAl);
					ps.setInt(2,colid);
				}
			});
			return true;
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return false;
		}
	}

	@Override
	public ColAtt get(int id) {
		// TODO Auto-generated method stub
		try {
			final ColAtt tmp = new ColAtt();  
			jdbcTemplate.query("select * from col_list  where col_id = ?",  
					new Object[] {String.valueOf(id)},  
					new RowCallbackHandler() {  
				public void processRow(ResultSet rs) throws SQLException {  
					tmp.setId(rs.getInt("COL_ID"));
					tmp.setName(rs.getString("COL_NAME"));
					tmp.setUrl(rs.getString("COL_URL"));
					tmp.setChlId(rs.getInt("CHL_ID"));
					tmp.setJobId(rs.getInt("JOB_ID"));
				}  
			});
			if(tmp.getId()>0){
				return tmp;	
			}else{
				return null;
			}
		}
		catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}	
	@Override
	public String getAlias(int id) {
		try {
			String sql = "select col_alias from col_list where col_id=?";
			final StringBuffer strbuf=new StringBuffer();

			jdbcTemplate.query(sql,new Object[]{id},
					new RowCallbackHandler() {

				public void processRow(ResultSet rs) throws SQLException {

					strbuf.append(rs.getString("COL_ALIAS"));

				}
			} );

			return strbuf.toString();
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}


	@Override
	public List getCols(int jid,int num) {
		try {
			String sql = "select * from col_list where job_id=? and rownum<=?";


			return jdbcTemplate.query(sql,new Object[]{String.valueOf(jid),String.valueOf(num)},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final ColAtt tmp=new ColAtt();
					tmp.setId(rs.getInt("COL_ID"));
					tmp.setName(rs.getString("COL_NAME"));
					tmp.setUrl(rs.getString("COL_URL"));
					tmp.setChlId(rs.getInt("CHL_ID"));
					tmp.setJobId(rs.getInt("JOB_ID"));
					return tmp;
				}
			} );


		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}

	@Override
	public int puttCol(ColAtt col) {
		try {
			final String hash=AeSimpleSHA1.SHA1(col.getUrl());
			final String urlstr=col.getUrl();
			final String name=col.getName();
			final int jobid=col.getJobId();
			final int chlid=col.getChlId();
			log.debug(name+urlstr+jobid);
			if(jobid>0)
			{
				final int colId=jdbcTemplate.queryForInt("select col_id_sequence.nextval from dual");
				jdbcTemplate.update("insert into col_list(col_id,col_hash,col_url,col_name,chl_id,create_time,col_stat,job_id) values(?,?,?,?,?,sysdate,'0',?)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setInt(1,colId);
						ps.setString(2,hash);
						ps.setString(3,urlstr);
						ps.setString(4,name);
						ps.setInt(5,chlid);
						ps.setInt(6,jobid);
					}
				});
				return colId;
			}else
			{
				return -1;
			}
		} catch (NoSuchAlgorithmException e) {
			log.debug(e.toString());
			return -1;
		}
	}

	@Override
	public boolean updateStat(int colId, String stat) {
		try {
			final String colstat=stat;
			final int colid=colId;
			jdbcTemplate.update("update col_list set col_stat=?,update_time=sysdate where col_id=?",new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,colstat);
					ps.setInt(2,colid);
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
	public boolean updateStatByJobId(int id, String stat) {
		try {
			final String colstat=stat;
			final int jobId=id;
			jdbcTemplate.update("update col_list set col_stat=?,update_time=sysdate where job_id=?",new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,colstat);
					ps.setInt(2,jobId);
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
	public boolean updateStatByJobIdAndStatus(int id, String pre_status, String stat) {
		try {
			final String colstat=stat;
			final int jobId=id;
			final String preStatus=pre_status;
			String sql="update col_list set col_stat=?,update_time=sysdate where job_id=?  and col_stat=? and create_time>sysdate-2";
			if ("9".equals(stat))
			{
				sql=sql+" and create_time>sysdate-1";
			}
			log.debug("stat:"+stat+" sql:"+sql);
			jdbcTemplate.update(sql,new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,colstat);
					ps.setInt(2,jobId);
					ps.setString(3, preStatus);
				}
			});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}

	public int GetId(String hash){
		try {
			int id=jdbcTemplate.queryForInt("select col_id from col_list where col_hash=?",new Object[]{hash});
			return id;
		} catch (DataAccessException e) {
			return -1;
		}
	}
	public int getJobId(int colId) {
		try{
			int jobid=jdbcTemplate.queryForInt("select job_id from col_list where col_id=?",new Object[]{colId});
			return jobid;
		} catch (DataAccessException e) {
			return -1;
		}
	}

	@Override
	public int getChlId(int colid) {
		try{
			int jobid=jdbcTemplate.queryForInt("select chl_id from col_list where col_id=?",new Object[]{colid});
			return jobid;
		} catch (DataAccessException e) {
			return -1;
		}
	}


	@Override
	public int getFailCount(int colId) {
		// TODO Auto-generated method stub
		try{
			int failCount = jdbcTemplate.queryForInt("select fail_count from col_list where col_id=?",new Object[]{colId});
			return failCount;
		} catch (DataAccessException e) {
			return 0;
		}		
	}
	@Override
	public boolean updateFailCount(int colId) {
		// TODO Auto-generated method stub
		log.debug("update count");
		try {
			final int colid=colId;
			jdbcTemplate.update("update col_list set fail_count=fail_count+1 where col_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,colid);
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
	public boolean resetFailCount(int colId) {

		try {
			final int colid = colId;
			jdbcTemplate.update("update col_list set fail_count=0 where col_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setInt(1,colid);
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
	public boolean updateName(int id,String name) {
		try {
			final String strAl=name;
			final int colid=id;
			String sql="update col_list set col_name=? where col_id = ?";
			jdbcTemplate.update(sql,new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,strAl);
					ps.setInt(2,colid);
				}
			});
			return true;
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return false;
		}
	}
	@Override
	public boolean needUpdate(int colId)
	{
		//all the col of the job has the same create date need to update.
		//all the url of the col has the same create date need to update.
		try {
			Calendar curr = Calendar.getInstance();
			curr.add(Calendar.HOUR, -2);
			Calendar flagCal=updateFlag.get(colId);
			if(flagCal!=null&&flagCal.compareTo(curr)>0)
			{
				return false;
			}else
			{
				String inv1=(String)jdbcTemplate.queryForObject("select max(create_time)-min(create_time) from col_list where job_id =(select job_id from col_list where col_id=?)",new Object[]{colId},java.lang.String.class);
				String inv2=(String)jdbcTemplate.queryForObject("select max(create_time)-min(create_time) from url_att where col_id=?",new Object[]{colId},java.lang.String.class);
				double dinv1=0;
				double dinv2=0;
				if(inv1!=null)
					dinv1=Double.parseDouble(inv1);
				if(inv2!=null)
					dinv2=Double.parseDouble(inv2);
				if(dinv2<1&&dinv1>1)
				{
					Calendar currTmp = Calendar.getInstance();
					updateFlag.put(colId, currTmp);
					return false;
				}
			}
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return false;
		}
		return true;
	}

	@Override
	public boolean updateFinStat(int id, String stat) {
		try {
				final String colstat=stat;
				final int colid=id;
				jdbcTemplate.update("update col_list set col_stat=?,update_time=sysdate where col_id=? and (col_stat=2 or col_stat=9)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						ps.setString(1,colstat);
						ps.setInt(2,colid);
					}
				});
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}



}
