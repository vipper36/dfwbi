package nyapc.crawler.dao;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import nyapc.crawler.Util;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.PreparedStatementSetter;
import org.springframework.jdbc.core.RowCallbackHandler;

import org.springframework.jdbc.core.RowMapper;

import java.security.*;
import java.util.List;
public class CrawlerDaoImp implements CrawlerDao {
	private static Log log = LogFactory.getLog(CrawlerDaoImp.class.getName());	
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
			final String idStr = String.valueOf(id);
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
	public CrawlerAtt get(int id) {
		// TODO Auto-generated method stub
		final CrawlerAtt theCrawlerAtt = new CrawlerAtt();  
		jdbcTemplate.query("select crawler_id,crawler_name,crawler_status,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,agent_id from crawler_list  where crawler_id = ?",  
		                   new Object[] {String.valueOf(id)},  
		                    new RowCallbackHandler() {  
		                         public void processRow(ResultSet rs) throws SQLException {  
		                        	 theCrawlerAtt.setCrawlerId(Util.str2int(rs.getString("crawler_id")));  
		                        	 theCrawlerAtt.setCrawlerName(rs.getString("crawler_name"));  
		                        	 theCrawlerAtt.setCrawlerStatus(rs.getInt("crawler_status"));
		                        	 theCrawlerAtt.setCreateTime(rs.getString("create_time"));
		                        	 theCrawlerAtt.setUpdateTime(rs.getString("update_time"));
		                        	 theCrawlerAtt.setAgentId(rs.getInt("agent_id"));
		                         }  
		                     });
		if(theCrawlerAtt.getCrawlerId()>0){
			return theCrawlerAtt;	
		}else{
			return null;
		}
		
	}

	@Override
	public List list() {
		// TODO Auto-generated method stub
		String sql = "select crawler_id,crawler_name,crawler_status,to_char(create_time,'yyyy-mm-dd hh24:mi:ss') create_time,to_char(update_time,'yyyy-mm-dd hh24:mi:ss') update_time,agent_id from crawler_list";
		try {
			return jdbcTemplate.query(sql,new RowMapper() {
				public Object mapRow(ResultSet rs, int rowNum) throws SQLException  {
					final CrawlerAtt theCrawlerAtt = new CrawlerAtt();   
	               	theCrawlerAtt.setCrawlerId(Util.str2int(rs.getString("crawler_id")));  
	            	theCrawlerAtt.setCrawlerName(rs.getString("crawler_name"));  
	            	theCrawlerAtt.setCrawlerStatus(rs.getInt("crawler_status"));
	            	theCrawlerAtt.setCreateTime(rs.getString("create_time"));
	            	theCrawlerAtt.setUpdateTime(rs.getString("update_time"));
	            	theCrawlerAtt.setAgentId(rs.getInt("agent_id"));
					return theCrawlerAtt;
				}
			} );

		} catch (DataAccessException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
			return null;
		}
	}

	@Override
	public int save(CrawlerAtt crawlerAtt) {
		// TODO Auto-generated method stub
		try {
			final String crawlerName = crawlerAtt.getCrawlerName();
			final int  crawlerStatus = crawlerAtt.getCrawlerStatus();
			final int agentId =  crawlerAtt.getAgentId();
			if(crawlerAtt.getCrawlerId()==0){
				final int crawlerId=jdbcTemplate.queryForInt("select seq_crawler_list.nextval from dual");
				jdbcTemplate.update("insert into crawler_list(crawler_id,crawler_name,crawler_status,create_time,update_time,agent_id) values(?,?,?,sysdate,null,?)",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setLong(i++,crawlerId);
						ps.setString(i++,crawlerName);
						ps.setInt(i++,crawlerStatus);
						ps.setLong(i++,agentId);
					}
				});
				return crawlerId;
			}else{
				final int crawlerId = crawlerAtt.getCrawlerId();
				jdbcTemplate.update("update crawler_list set crawler_name=?,crawler_status=?,update_time=sysdate,agent_id=? where crawler_id=?",new PreparedStatementSetter(){
					public void setValues(PreparedStatement ps) throws SQLException{
						int i = 1;
						ps.setString(i++,crawlerName);
						ps.setInt(i++,crawlerStatus);
						ps.setLong(i++,agentId);
						ps.setLong(i++,crawlerId);
					}
				});
				
				return crawlerId;
			}
			

		} catch (DataAccessException e) {
			log.debug(e.toString());
			return -1;
		}
	}
}


