package nyapc.crawler.dao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import nyapc.crawler.Util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.support.AbstractLobCreatingPreparedStatementCallback;
import org.springframework.jdbc.support.lob.LobCreator;
import org.springframework.jdbc.support.lob.LobHandler;


public class WrapperDaoImp implements WrapperDao {
	private static Log log = LogFactory.getLog(WrapperDaoImp.class.getName());	
	private JdbcTemplate jdbcTemplate;
	private LobHandler lobHandler;
	public LobHandler getLobHandler() {
		return lobHandler;
	}

	public void setLobHandler(LobHandler lobHandler) {
		this.lobHandler = lobHandler;
	}

	public JdbcTemplate getJdbcTemplate() {
		return jdbcTemplate;
	}

	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	@Override
	public WrapAtt getWrap(int id) {
		try {
			final WrapAtt tmp=new WrapAtt();
			String sql = "select WRAP_ID,WRAP_TYPE,WRAPPER,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,JOB_ID,WRAP_COMMENT,WRAP_VERSION,WRAP_VAR_GEN,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,WRAP_STAT from WRAPPER_LIST where wrap_id=?";
			jdbcTemplate.query(sql, new Object[]{id},
					new RowCallbackHandler() {
				 public void processRow(ResultSet rs) throws SQLException { 

					 tmp.setId(rs.getInt("WRAP_ID"));

					 tmp.setType(rs.getString("WRAP_TYPE"));

					 tmp.setWrapper(lobHandler.getClobAsString(rs, "WRAPPER"));

					 tmp.setJobid(rs.getInt("JOB_ID"));

					 tmp.setComment(rs.getString("WRAP_COMMENT"));

					 tmp.setVersion(rs.getInt("WRAP_VERSION"));
					 
					 tmp.setVargen(rs.getString("WRAP_VAR_GEN"));
					 
					 tmp.setCreateTime(rs.getString("create_time"));
					 tmp.setUpdateTime(rs.getString("update_time"));
					 tmp.setWrapStat(rs.getString("wrap_stat"));
					 
			      }
			    });
			return tmp;
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return null;
		} 
	}
	@Override
	public WrapAtt getStudyWrap(int id) {
		try {
			final WrapAtt tmp=new WrapAtt();
			String sql = "select WRAP_ID,WRAP_TYPE,WRAPPER,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,JOB_ID,WRAP_COMMENT,WRAP_VERSION,WRAP_VAR_GEN,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,WRAP_STAT from WRAPPER_STUDY where wrap_id=?";
			jdbcTemplate.query(sql, new Object[]{id},
					new RowCallbackHandler() {
				 public void processRow(ResultSet rs) throws SQLException { 

					 tmp.setId(rs.getInt("WRAP_ID"));

					 tmp.setType(rs.getString("WRAP_TYPE"));

					 tmp.setWrapper(lobHandler.getClobAsString(rs, "WRAPPER"));

					 tmp.setJobid(rs.getInt("JOB_ID"));

					 tmp.setComment(rs.getString("WRAP_COMMENT"));

					 tmp.setVersion(rs.getInt("WRAP_VERSION"));
					 
					 tmp.setVargen(rs.getString("WRAP_VAR_GEN"));
					 
					 tmp.setCreateTime(rs.getString("create_time"));
					 tmp.setUpdateTime(rs.getString("update_time"));
					 tmp.setWrapStat(rs.getString("wrap_stat"));
					 
			      }
			    });
			return tmp;
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return null;
		} 
	}
	@Override
	public List getWrapsByJob(int jobid,String type) {
		try {
			String sql;
			Object[] params;
			if(type=="A")
			{
				sql= " SELECT wrap_id,wrap_type,wrapper,job_id,wrap_comment,wrap_version,wrap_var_gen,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,WRAP_STAT  from WRAPPER_LIST where job_id=?";
				params =  new  Object[] {jobid};
			}else
			{
				sql= " SELECT wrap_id,wrap_type,wrapper,job_id,wrap_comment,wrap_version,wrap_var_gen,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,WRAP_STAT from WRAPPER_LIST where job_id=? and wrap_type=?";
				params =  new  Object[] {jobid,type};
			}
			return jdbcTemplate.query(sql, params,
					 new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  { 
					final WrapAtt tmp=new WrapAtt();
					 tmp.setId(rs.getInt("WRAP_ID"));
					 tmp.setType(rs.getString("WRAP_TYPE"));
					 tmp.setWrapper(lobHandler.getClobAsString(rs, "WRAPPER"));
					 tmp.setJobid(rs.getInt("JOB_ID"));
					 tmp.setComment(rs.getString("WRAP_COMMENT"));
					 tmp.setVersion(rs.getInt("WRAP_VERSION"));
					 tmp.setVargen(rs.getString("WRAP_VAR_GEN"));
					 tmp.setCreateTime(rs.getString("create_time"));
					 tmp.setUpdateTime(rs.getString("update_time"));
					 tmp.setWrapStat(rs.getString("wrap_stat"));					 
					 return tmp;
			      }
			    });
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return null;
		} 
	}

	@Override
	public int putWrap(WrapAtt wrap) {
		try {
			final String type=wrap.getType();
			final int jobid=wrap.getJobid();
			final String comment=wrap.getComment();
			final String wrapper=wrap.getWrapper();
			final int version=wrap.getVersion();
			final String vargen=wrap.getVargen();
			 final int wrapId=jdbcTemplate.queryForInt("select wrapper_id_sequence.nextval from dual");
			String sql = " INSERT INTO WRAPPER_LIST(wrap_id,wrap_type,wrapper,create_time,job_id,wrap_comment,wrap_version,wrap_var_gen,update_time,wrap_stat)" 
			    + " VALUES(?,?,?,sysdate,?,?,?,?,sysdate,?)"; 
			jdbcTemplate.execute(sql, 
			  new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
			      protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
			                  throws SQLException {
			    	  ps.setInt(1, wrapId); 
			          ps.setString(2, type);   
			          lobCreator.setClobAsString(ps, 3, wrapper);
			          ps.setInt(4, jobid);   
			          ps.setString(5, comment);
			          ps.setInt(6, version);
			          ps.setString(7,vargen);
			          ps.setString(8,"0");//0 有效
			      }
			    });
			return wrapId;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return -1;
		} 

		
	}

	@Override
	public boolean updateWrap(String wrap, int id) {
		try {
			final int wrapid=id;
			final String wrapper=wrap;

			String sql = " UPDATE WRAPPER_LIST set wrapper=?,wrap_version=wrap_version+1,update_time=sysdate where wrap_id=?";
			
			//update state jobid   jobtype   3+1
			
			jdbcTemplate.execute(sql, 
			  new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
			      protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
			                  throws SQLException {  
			          lobCreator.setClobAsString(ps, 1, wrapper);
			          ps.setInt(2, wrapid);   
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
	public boolean updateWrapGen(String wrapgen, int id) {
		try {
			final int wrapid=id;
			final String wrap_gen=wrapgen;

			String sql = " UPDATE WRAPPER_LIST set wrap_var_gen=?,update_time=sysdate,wrap_stat=? where wrap_id=?"; 
			jdbcTemplate.execute(sql, 
			  new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
			      protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
			                  throws SQLException {  
			          lobCreator.setClobAsString(ps, 1, wrap_gen);
			          ps.setString(2, "-1");//-1无效
			          ps.setInt(3, wrapid);
			          
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
	public List listByStat(String stat) {
		// TODO Auto-generated method stub
		String sql = "select WRAP_ID,WRAP_TYPE,WRAPPER,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,JOB_ID,WRAP_COMMENT,WRAP_VERSION,WRAP_VAR_GEN,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,WRAP_STAT from wrapper_list where wrap_stat=? ";
		try {
			return jdbcTemplate.query(sql,new Object[]{stat},new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final WrapAtt tmp=new WrapAtt();     
					 tmp.setId(rs.getInt("WRAP_ID"));

					 tmp.setType(rs.getString("WRAP_TYPE"));

					 tmp.setWrapper(lobHandler.getClobAsString(rs, "WRAPPER"));

					 tmp.setJobid(rs.getInt("JOB_ID"));

					 tmp.setComment(rs.getString("WRAP_COMMENT"));

					 tmp.setVersion(rs.getInt("WRAP_VERSION"));
					 
					 tmp.setVargen(rs.getString("WRAP_VAR_GEN"));
					 
					 tmp.setCreateTime(rs.getString("create_time"));
					 tmp.setUpdateTime(rs.getString("update_time"));
					 tmp.setWrapStat(rs.getString("wrap_stat"));
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
	public boolean updateStatByWrapId(int id,String stat) {

		try {
			final String wrapStatus=stat;
			final int wrapId=id;
			jdbcTemplate.update("update wrapper_list set wrap_stat=?,update_time=sysdate where wrap_id=?",
					new PreparedStatementSetter(){
				public void setValues(PreparedStatement ps) throws SQLException{
					ps.setString(1,wrapStatus);
					ps.setInt(2,wrapId);
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
	public List getWrapId(int jid) {
		String sql = "select wrap_id from wrapper_list where job_id=?";
		 try {
				return jdbcTemplate.query(sql,new Object[]{jid},new RowMapper() {
						public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
							final Integer wrap_id=rs.getInt("WRAP_ID");	        	
				        	return wrap_id;
				        }
				    } );

			} catch (DataAccessException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;
			}
	}

	@Override
	public String getWrapType(int id) {
		try {
			final StringBuffer type=new StringBuffer();
			String sql = "select WRAP_TYPE from WRAPPER_LIST where wrap_id=?";
			jdbcTemplate.query(sql, new Object[]{id},
					new RowCallbackHandler() {
				 public void processRow(ResultSet rs) throws SQLException { 
					 type.append(rs.getString("WRAP_TYPE"));
			      }
			    });
			return type.toString();
		} catch (DataAccessException e) {
			log.debug(e.toString());
			return null;
		} 
	}	
	//把wrapper_list表中学习出错的记录,插入wrapper_study表中
	@Override
	public boolean insertWrapStudyByWrapId(final int id)
	{
		try
		{
			//通过wrap_id从wrapper_list得到一条数据
			final WrapAtt wrap = getWrap(id);
			//把这一条数据插入wrapper_study表中
			final String type=wrap.getType();
			final int jobid=wrap.getJobid();
			final String comment=wrap.getComment();
			final String wrapper=wrap.getWrapper();
			final int version=wrap.getVersion();
			final String vargen=wrap.getVargen();
			boolean flag = true;
			try
			{
				Integer result = (Integer)jdbcTemplate.queryForInt("select wrap_id from WRAPPER_STUDY where wrap_id = " + new Integer(id));
				flag = false;
			}
			catch(org.springframework.dao.EmptyResultDataAccessException e)
			{
				flag = true;
			}
			if(flag)
			{
				String sql = " INSERT INTO WRAPPER_STUDY(wrap_id,wrap_type,wrapper,create_time,job_id,wrap_comment,wrap_version,wrap_var_gen,update_time,wrap_stat)" 
					+ " VALUES(?,?,?,sysdate,?,?,?,?,sysdate,?)"; 
				jdbcTemplate.execute(sql, 
						new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
					protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
					throws SQLException {
						ps.setInt(1, id); 
						ps.setString(2, type);   
						lobCreator.setClobAsString(ps, 3, wrapper);
						ps.setInt(4, jobid);   
						ps.setString(5, comment);
						ps.setInt(6, version);
						ps.setString(7,vargen);
						ps.setString(8,"0");//0 有效
					}
				});
			}
		}
		catch(DataAccessException e)
		{
			log.debug(e.toString());
			return false;
		}
		return true;
	}
	//通过界面修改wrapper_study表中的wrapper
	@Override
	public boolean updateWrapFromWrapStudy(String wrap,int id)
	{
		try {
			final int wrapid=id;
			final String wrapper=wrap;
			log.debug("update wrapper:"+wrapid);
			String sql = " UPDATE WRAPPER_STUDY set wrapper=?,wrap_version=wrap_version+1,update_time=sysdate where wrap_id=?";
			
			//update state jobid   jobtype   3+1
			
			jdbcTemplate.execute(sql, 
			  new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
			      protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
			                  throws SQLException {  
			          lobCreator.setClobAsString(ps, 1, wrapper);
			          ps.setInt(2, wrapid);   
			      }
			    });
			
			
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}
	
	//把正确的wrapper的记录从wrapper_study表中,导入wrapper_list中
	@Override
	public boolean updateWrapListByStudy(String wrap,int id)
	{
		try {
			final int wrapid=id;
			final String wrapper=wrap;

			String sql = " UPDATE WRAPPER_LIST set wrapper=?,wrap_version=wrap_version+1,update_time=sysdate where wrap_id=?";
			
			//update state jobid   jobtype   3+1
			
			jdbcTemplate.execute(sql, 
			  new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
			      protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
			                  throws SQLException {  
			          lobCreator.setClobAsString(ps, 1, wrapper);
			          ps.setInt(2, wrapid);   
			      }
			    });
			
			String delSql = "delete from WRAPPER_STUDY where wrap_id=?";
			
			jdbcTemplate.execute(delSql, 
					  new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
					      protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
					                  throws SQLException {  
					          ps.setInt(1, wrapid);   
					      }
					    });
			return true;
		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return false;
		}
	}
	//删除一条wrapper_study
	public boolean deleteWrapStudy(final int id)
	{
		boolean flag = true;
		try
		{
			Integer result = (Integer)jdbcTemplate.queryForInt("select wrap_id from WRAPPER_STUDY where wrap_id = " + new Integer(id));
			flag = true;
		}
		catch(org.springframework.dao.EmptyResultDataAccessException e)
		{
			flag = false;
		}
		if(flag)
		{
			try
			{
			String sql = "delete from WRAPPER_STUDY where wrap_id=?"; 
			jdbcTemplate.execute(sql, 
					new AbstractLobCreatingPreparedStatementCallback(this.lobHandler) {
				protected void setValues(PreparedStatement ps,LobCreator lobCreator) 
				throws SQLException {
					ps.setInt(1, id); 
				}
			});
			}
			catch(DataAccessException de)
			{
				log.debug(de.toString());
				return false;
			}
		}
		return true;
	}
}
